#include "init.h"

#include <stdlib.h>
#include <string>
#include <pcap.h>  //tutaj mamy plik nagłówkowy biblioteki PCAP
#include <sys/stat.h>
//#include <sys/types.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <glibmm.h>
#include "pckt_handler.h" // tutaj jest moja funckja obsługi pakietów
#include <arpa/inet.h> //zawiera funkcję ntohs
#include "bytewrite.h"

using namespace std;

//##########################################
//funkcja przekazywana do pthread_create uruchamiająca pętlę czytania pakietów
void * sn_loop (void * sniff) {
    ((Sniffer *) sniff)->loop();
    cout << "######### sn_loop END" << endl << endl;
    return(NULL);
}

//##########################################
// definicje klasy Sniffer
//##########################################

//KONSTRUKTOR na bazie parametrów z configu
Sniffer::Sniffer(const Glib::KeyFile* konfig, const string grupa) {
cout << "SNIFFER KONSTRUKTOR  ############# " << grupa << endl;
    const uint pcap_data_max = 512; // 65535;   //liczba bajtów przechwytywanych przez PCAP
    const uint pcap_timeout = 1;    //timeout dla czekania na pakiety (ms)
    thread_running = false;         //wątek jeszcze nie pracuje
    thread_stop = false;
    thread_start = false;
    thread_testcancel = false;
    loops = 0;
    SYGNAL = 0;

    path = "/1T/";  //głowny katalog do zapisu plików dump
    ostringstream sint;  //zmienna potrzebna do konwersji int -> string

    //wczytuje parametry z 'grupy' w pliku konfiguracyjnym
    Snazwa = (char*) grupa.c_str();

    cout << "##########################" << endl;
    cout << "KONFIG " << nazwa() << endl;

    if (konfig->has_key(nazwa(),"proto")) proto = konfig->get_string(nazwa(),"proto");
    else proto = "tcp"; //jesli nie podanego innego protokołu to domyslenie jest to protokół TCP

    if (konfig->has_key(nazwa(),"dev")) dev = konfig->get_string(nazwa(),"dev").c_str();
    else {
        cout << "Błąd pliku konfiguracyjnego - grupa:"<< nazwa() << " nie posiada zdefiniowanego urządzenia sieciowego" << endl;
        exit(1);
    }
    //czy dane maja byc zapisywane w postaci dla człowieka?
    if (konfig->has_key(nazwa(),"human")) human = konfig->get_integer(nazwa(),"human");

    if (konfig->has_key(nazwa(),"filter")) filter = konfig->get_string(nazwa(),"filter");
    if (filter == "") {
        filter = proto;
        if (konfig->has_key(nazwa(),"ip_s")) {
            ip_s = konfig->get_string(nazwa(),"ip_s");
            filter += " src host " + ip_s;
        }
        if (konfig->has_key(nazwa(),"ip_d")) {
            ip_d = konfig->get_string(nazwa(),"ip_d");
            filter += " dst host " + ip_d;
        }
        if (konfig->has_key(nazwa(),"port_s")) {
            port_s = (uint) konfig->get_integer(nazwa(),"port_s");
            sint << port_s;  //konwersja int -> string
            filter += " src port " + sint.str();
        }
        if (konfig->has_key(nazwa(),"port_d")) {
            port_d = (uint) konfig->get_integer(nazwa(),"port_d");
            sint << port_d;  //konwersja int -> string
            filter += " dst port " + sint.str();
        }
    }
    //otwieramy urządenie
    if((fp=pcap_open_live(dev.c_str(),pcap_data_max,1,pcap_timeout,errbuf))==NULL) {
        cout << "*** PCAP Error ***" << endl;
        cout << "Nie można otworzyć urządzenia: " << dev << " error: " << errbuf << endl;
        exit(1);
    }
    if(pcap_lookupnet(dev.c_str(),&ip_addr,&netmask,errbuf)==-1) {
        //printf("Nie można uzyskać maski: %s\n",errbuf);
        ip_addr=0;
        netmask=0;
    }
    //kompilacja filtru
    if(pcap_compile(fp,&fcode,(char *)filter.c_str(),0,netmask)<0) {
        cout << "*** PCAP Error ***" << endl;
        cout << "Składnia filtru jest niepoprawna: " << filter << endl;
        pcap_close(fp);
        exit(1);
    }
    //ustawienie filtra
    if(pcap_setfilter(fp,&fcode)<0) {
        cout << "*** PCAP Error ***" << endl;
        cout << "Błąd podczas ustawiania filtru: " << filter << endl;
        pcap_close(fp);
        exit(1);
    }
//    int res = pcap_setnonblock(fp,1,errbuf);
//    if (res==-1) cout << "SETNONBLOCK error: " << errbuf << endl;

cout << "filter: " << filter << endl;
cout << "dev: " << dev << endl;
cout << "proto: " << proto << endl;
cout << "##########################" << endl;
cout << endl;
run(); //od razu uruchamionie sniffera
}

//##########################################
//DESTRUKTOR zamyka plik związany z daną instancją sniffera i zwalnia pamięć
Sniffer::~Sniffer() {
    stop();
    if (dumpfile.is_open())
        dumpfile.close();
    pcap_close(fp);
    pthread_cancel(loopthread);
    while (thread_running) usleep(500); //oczekiwanie na zamknięcie wątku
    sleep(1);
    cout << "Sniffer::~Sniffer " << nazwa() << _SYGNAL << endl;
}

//##########################################
// Sniffer::loop
//##########################################
//funkcja WĄTKU
void Sniffer::loop() {  // WĄTEK odczytywanie pakietów w pętli
    int res;            //rezultat zczytywania pakietów
    pcap_pkthdr * header;
    const u_char * pkt_data;
    ipheader * iphead;

    loops++;
    thread_running = true;
cout << thread_running << "|" << thread_start << " loops:"<< loops << endl;
while (!thread_start) {usleep(1000);}

cout << "Sniffer::loop " << nazwa() << " START " << thread_running << "|" << thread_start << " loops:"<< loops << "|" << _SYGNAL << endl;

    while ((res = pcap_next_ex(fp, &header, &pkt_data) >= 0) && (_SYGNAL == 0) && (!thread_stop) ) {//odczyt pakietów dopóki nie bedzie sygnału stop lub błędu odczytu
        cout << "Sniffer::loop " << nazwa() << " while START " << _SYGNAL << endl; usleep(5000);
        if(res == 1) {
            iphead=(ipheader *)(pkt_data+14);
            cout << "Sniffer::loop " << nazwa() << " iphead " << _SYGNAL << endl;
//            sleep(1);
            ushort iphlen = iphead->ip_hl;
            cout << "Sniffer::loop " << nazwa() << " iphlen " << iphlen << " " << _SYGNAL << endl;
            //zapis czasu
            if (!human) {
//                cout << "Sniffer::loop pcap_next_ex while human bytewrite " << _SYGNAL << endl;
                bytewrite(dumpfile,header->ts.tv_sec % 3600,2);  //zapis liczby sekund w postaci bajtowej (ushort)
                bytewrite(dumpfile,header->ts.tv_usec);  //zapis liczby mikrosekund w postaci bajtowej (uint)
//                cout << "Sniffer::loop pcap_next_ex while human bytewrite END" << _SYGNAL << endl;
            }
            packethandler(dumpfile, pkt_data, (human == 1));  //funkcja obsługi odczytanych pakietów
        }
//        if (thread_stop || res <0) {
//            cout << "################### BREAK" << endl;
//            pcap_breakloop(fp);
//            SYGNAL = 0;
//            sleep(2);
//            pthread_exit((void*)res);
//        }
        cout << "Sniffer::loop " << nazwa() << " TESTCANCEL begin" << endl;
        thread_testcancel = true;
        thread_running = false;
        pthread_testcancel();
        thread_running = true;
        thread_testcancel = false;
        cout << "Sniffer::loop " << nazwa() << " TESTCANCEL end" << SYGNAL << endl;
        if (SYGNAL == 0) continue;
        else break;
    }
    cout << "Sniffer::lopp WHILE " << nazwa() << " STOP " << _SYGNAL << endl;
    if(res == -1) { //pętlę odczytu przerwał błąd odczytu pakietów
        cout << "BŁĄD odczytu pakietów: " << pcap_geterr(fp) << endl;
    }
    thread_running = false;
    SYGNAL = 0;
    pthread_exit((void*)res);
}

//##########################################
// Sniffer::run
//##########################################
//INICJALIZACJA wątku
void Sniffer::run() { //uruchomienie procesu zczytywania pakietów
    time_t czas;            // bieżący czas
    struct tm *timeinfo;    //struktura danych czasowych
    int res;                //rezultat uruchomienia wątku
    char * dir;             //path/nazwa
    char datetime[16];
//cout << "Sniffer::run() "<< nazwa() << " start " << _SYGNAL << endl;sleep(2);
    //zapis jest do pliku w katalogu "path/nazwa" czyli nazwa grupy ustawień z pliku konfiguracyjnego
    dir = new char [path.size()+sizeof( (char *) nazwa())+1];
    strcpy (dir, (path+nazwa()).c_str());

    if (!Glib::file_test(dir,Glib::FILE_TEST_EXISTS | Glib::FILE_TEST_IS_DIR)) { //sprawdzenie istnienia i ewentualne utworzenie katalogu o nazwie tak jak nazwa grupy z pliku konfiguracyjnego
        if (!Glib::file_test(path.c_str(),Glib::FILE_TEST_EXISTS | Glib::FILE_TEST_IS_DIR))  {mkdir(path.c_str(),ALLPERMS);cout << "mkdir " << path << endl;}
        mkdir(dir,ALLPERMS);
        cout << "mkdir " << dir << endl;
    }
    if (!Glib::file_test(dir,Glib::FILE_TEST_EXISTS | Glib::FILE_TEST_IS_DIR)) {
        cout << "utworzenie katalogu " << dir << " nie powiodło się" << endl;
        exit (0);
    }
    time(&czas);  //odczytanie bieżącego czasu
    timeinfo = localtime(&czas);

    strftime(datetime,16,"%y%m%d_%H-%M-%S",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"
    filename = (string) dir + "/" + (string) datetime;  //ścieżka do pliku do zapisywania pakietów
    delete dir;   // dir już nie jest potrzebne
    dumpfile.open(filename.c_str(), ios::out | ios::app | ios::binary);          //otwarcie pliku do zapisu w trybie binary
//cout << "Sniffer::run() "<< nazwa() << " dumpfile open " << _SYGNAL << endl;sleep(2);

    //uruchomienie wątku loop()
    thread_stop = false;
cout << "Sniffer::run() "<< nazwa() << " pthread_create START " << _SYGNAL << endl;sleep(1);
    res = pthread_create(&loopthread, NULL, sn_loop, this);
//usleep(50);
cout << "Sniffer::run() "<< nazwa() << " pthread_created " << loopthread << "  sig:" << _SYGNAL << " thrun:" << thread_running << endl;sleep(2);
    if (res < 0) cout << "BŁĄD utworzenia wątku " << res << endl;
    else while (!thread_running) {
        while (thread_testcancel) usleep(100);
        cout << "RUN.usleep " << nazwa() << " " << _SYGNAL << endl;
        usleep(500000);
    }//oczekiwanie na uruchomienie wątku
    thread_start=true;
    cout << "Sniffer::run() "<< nazwa() << " end " << _SYGNAL << "|"<< SYGNAL << endl;
}

//##########################################
// Sniffer:: stop
//##########################################
//zatrzymanie watku
void Sniffer::stop() {
//    cout << "Sniffer::stop " << nazwa() << " stop() " <<_SYGNAL << endl;
    // zatrzymanie wątku
    thread_stop = true;
    while (thread_running && !thread_testcancel) {
        usleep(10);  //czekamy na zakończenie wątku
//        cout << "STOP.usleep " << _SYGNAL << endl;
    }
    pcap_breakloop(fp);
//    cout << "Sniffer::stop pcap_breakloop " << nazwa() << " " <<_SYGNAL << endl;
}

char * Sniffer::nazwa() { return Snazwa;}

void Sniffer::sygnal(ushort syg) {SYGNAL = syg;}

void Sniffer:: restart() {
    time_t czas;            // bieżący czas
    struct tm *timeinfo;    //struktura danych czasowych
    char datetime[16];
    char * dir;
    std::ofstream newdumpfile;

    dir = new char [path.size()+sizeof( (char *) nazwa())+1];
    strcpy (dir, (path+nazwa()).c_str());
    time(&czas);  //odczytanie bieżącego czasu
    timeinfo = localtime(&czas);

    strftime(datetime,16,"%y%m%d_%H-%M-%S",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"
    filename = (string) dir + "/" + (string) datetime;  //ścieżka do pliku do zapisywania pakietów
    delete dir;   // dir już nie jest potrzebne

    if (dumpfile.is_open())
        dumpfile.close();
    dumpfile.open(filename.c_str(), ios::out | ios::app | ios::binary);          //otwarcie pliku do zapisu w trybie binary
}
