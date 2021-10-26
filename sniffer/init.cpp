#include "init.h"

#include <stdlib.h>     //dla exit
#include <dirent.h>     //dla opendir
#include <sys/stat.h>   //dla mkdir

#include <iostream>
#include <fstream>
#include <time.h>
#include <arpa/inet.h> //zawiera funkcję ntohs
#include "pckt_handler.h" // tutaj jest moja funckja obsługi pakietów

using namespace std;

//##########################################
// definicje klasy Sniffer
//##########################################

//KONSTRUKTOR na bazie parametrów z configu
Sniffer::Sniffer(QSettings * settings) {
    cout << "SNIFFER KONSTRUKTOR  #############" << endl;

    //wczytuje parametry z pliku konfiguracyjnego
    dev = settings->value("dev").toString().toStdString();
    path = settings->value("path").toString().toStdString();  //głowny katalog do zapisu plików dump
    filter = settings->value("filter").toString().toStdString();
    protocol = settings->value("protocol").toString().toStdString();
    setblock = settings->value("setblock").toBool();
    Snazwa = dev + "_"+ protocol;

    cout << "KONFIG " << nazwa() << endl;

    if (filter == "") {
        filter = protocol;
        if (settings->contains("ip_s")) {
            ip_s = settings->value("ip_s").toString().toStdString();
            filter += " src host " + ip_s;
        }
        if (settings->contains("ip_d")) {
            ip_d = settings->value("ip_d").toString().toStdString();
            filter += " dst host " + ip_d;
        }
        if (settings->contains("port_s")) {
            port_s = settings->value("port_s").toUInt();
            filter += " src port " + port_s;
        }
        if (settings->contains("port_d")) {
            port_d = settings->value("port_d").toUInt();
            filter += " dst port " + port_d;
        }
    }
    fp_init(); //inicjalizacja fp

    cout << "filter: " << filter << endl;
    cout << "dev: " << dev << endl;
    cout << "proto: " << protocol << endl;
    cout << "setblock: " << setblock << endl;
    cout << "##########################" << endl;
    cout << endl;
    run(); //od razu uruchamienie sniffera
}

//##########################################
//DESTRUKTOR
Sniffer::~Sniffer() {
    pcap_breakloop(fp);
    pcap_close(fp);
    dumpfile.close();
    cout << "SNIFFER Destructor" << endl;
}

//##########################################
// Sniffer::run
//##########################################
void Sniffer::run() { //uruchomienie procesu zczytywania pakietów
    time_t czas;            // bieżący czas
    struct tm *timeinfo;    //struktura danych czasowych
    char datetime[16];

    //zapis jest do pliku w katalogu "path/nazwa" czyli nazwa grupy ustawień z pliku konfiguracyjnego

    if (opendir(path.c_str()) == NULL) //sprawdzenie istnienia i ewentualne utworzenie katalogu o nazwie tak jak nazwa grupy z pliku konfiguracyjnego
        mkdir(path.c_str(),0777);
    dir = path + Snazwa;
    if ((opendir(dir.c_str())) == NULL) //sprawdzenie istnienia i ewentualne utworzenie katalogu o nazwie tak jak nazwa grupy z pliku konfiguracyjnego
        mkdir(dir.c_str(),0777);

    time(&czas);  //odczytanie bieżącego czasu
    timeinfo = localtime(&czas);

    strftime(datetime,16,"%y%m%d_%H-%M-%S",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"
    filename = dir + "/" + datetime;  //ścieżka do pliku do zapisywania pakietów
    dumpfile.open(filename.c_str(),ios_base::binary | ios_base::out);                        //skierowanie strumienia na file
    if (dumpfile.fail()) cout << "RUN Sniffer DUMPFILE not good" << endl;
}

//##########################################
// Sniffer::fp_init
//##########################################
void Sniffer::fp_init() {
    const uint pcap_data_max = 128; // 65535;   //liczba bajtów przechwytywanych przez PCAP
    const uint pcap_timeout = 1;    //timeout dla czekania na pakiety (ms)

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
    if(pcap_compile(fp,&fcode,(char *) filter.c_str(),0,netmask)<0) {
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
    if ((setblock) && ( pcap_setnonblock(fp,1,errbuf) == -1)) cout << "SETNONBLOCK error: " << errbuf << endl;
 }

//##########################################
// Sniffer:: nazwa
//##########################################
string Sniffer::nazwa() { return Snazwa; }

//##########################################
// Sniffer:: restart
//##########################################

void Sniffer:: restart() {
    time_t czas;            // bieżący czas
    struct tm *timeinfo;    //struktura danych czasowych
    char datetime[16];

    dumpfile.close();

    time(&czas);  //odczytanie bieżącego czasu
    timeinfo = localtime(&czas);
    strftime(datetime,16,"%y%m%d_%H-%M-%S",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"
    filename = dir + "/" + datetime;  //ścieżka do pliku do zapisywania pakietów

    dumpfile.open(filename.c_str(), ios_base::binary | ios_base::out);  //skierowanie strumienia na file
    if (dumpfile.fail()) cout << "RESTART Sniffer DUMPFILE not good" << endl;
}
