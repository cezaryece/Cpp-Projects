#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <pcap.h>  //tutaj mamy plik nagłówkowy biblioteki
#include "pcap_handler.h"
#include "str_replace/str_replace.h"
#inlcude "unspace.h"
#include <vector>
#include <sys/stat.h>

using namespace std;

bool file_exist(const char *filename ) {
  struct stat buffer ;
  if ( stat( filename, &buffer ) ) return true ;
  return false ;
}
bool dir_exist(const char *dirname ) {
  if ( chdir(dirname) ==0 ) return true ;
  return false ;
}
struct konfig {
    string nazwa;
    string dev;
    ushort protocol;
    uint ip_src;
    uint ip_dst;
    ushort port_src;
    ushort port_dest;
} config;

void read_konfig(string * kfilename, konfig &config) {
    ifstream konfigfile(kfilename->c_str());
    konfigfile.open(kfilename->c_str());
    string linia;
    string key,value;
    string separator = "=";
    vector<string> key_value;

    while (getline(konfigfile, linia)) {
        unspace(linia);
        if (linia.compare(0,1,"#")!=0)
            str_explode(linia,"=",key_value);
    }
    for (ushort i=0;i<key_value)        //rozbić linie na key = value
            //przypisać do odpowiednich pól struktury konfig
            switch(key) {
                case "nazwa":   config.nazwa = value;break;
                case "dev":     config.dev = value;break;
                case "protocol":config.protocol = value;break;
                case "ip_src":  config.ip_src = value;break;
                case "ip_dst":  config.ip_dst = value;break;
                case "port_src": config.port_src = value;break;
                case "port_dst": config.port_dst = value;break;
            }
        }

    }
    konfigfile.close();
}


int main(int argc,char* argv[])
{
if(argc<3)
{
printf(" Uzycie: %s <urzadzenie> <filtr>.\n",argv[0]);
exit(1);
}
char* dev=argv[1]; //nazwa urzadzenia
pcap_t* fp;
char errbuf[PCAP_ERRBUF_SIZE]; //jeżeli będziemy chcieli obsługiwać błędy

u_int netmask,ip_addr;
struct bpf_program fcode;
char* packet_filter=argv[2];

if(pcap_lookupnet(dev,&ip_addr,&netmask,errbuf)==-1)
{
printf("Nie można uzyskać maski: %s\n",errbuf);
ip_addr=0;
netmask=0;
}
//otwieramy urządenie
if((fp=pcap_open_live(dev,65536,1,1000,errbuf))==NULL)
{
printf("Nie można otworzyć urządzenia: %s\n",errbuf);
exit(1);
}
//kompilacja filtra
if(pcap_compile(fp,&fcode,packet_filter,0,netmask)<0)
{
printf("Składnia filtru jest niepoprawna.\n");
pcap_close(fp);
exit(1);
}
//ustawienie filtra
if(pcap_setfilter(fp,&fcode)<0)
{
printf("Blad podczas ustawiania filtru.\n");
pcap_close(fp);
exit(1);
}

int res = pcap_setnonblock(fp,1,errbuf);
if (res==-1) cout << "SETNONBLOCK error: " << errbuf << endl;


printf("\n\nNasłuchiwanie na %s.\n\n",dev);
//pcap_loop(fp,0,packethandler,NULL); //i to jest funkcja przechwytująca pakiety
// i wysyłająca je do procedury packet_handler
//zakończy się gdy wciśniemy Ctrl+C
string path = "/1T/";  //głowny katalog do zapisu plików dump
if (!dir_exist(path.c_str()))
    mkdir(path.c_str(),ALLPERMS);

time_t czas;            // bieżący czas
struct tm *timeinfo;    //struktura danych czasowych
char * dir;             //path/nazwa
char datetime[16];

dir = new char [path.size()+sizeof( (char *) nazwa())+1];
strcpy (dir, (path+nazwa()).c_str());
if (!dir_exist(dir)) //sprawdzenie istnienia i ewentualne utworzenie katalogu o nazwie tak jak nazwa grupy z pliku konfiguracyjnego
    mkdir(dir,ALLPERMS);

time(&czas);  //odczytanie bieżącego czasu
timeinfo = localtime(&czas);

strftime(datetime,16,"%y%m%d_%H-%M-%S",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"
filename = (string) dir + "/" + (string) datetime;  //ścieżka do pliku do zapisywania pakietów
delete dir;   // dir już nie jest potrzebne
dumpfile.open(filename.c_str(), ios::out | ios::app | ios::binary);          //otwarcie pliku do zapisu w trybie binary

bool stop = false;
while (!stop) { //nieskończona pętla oczekująca na zakończenie programu lub zmianę daty
    //nowe pliki co godzine
    n_godzina = stime->tm_hour;   //bierząca godzina
    if (n_godzina != godzina) {
        cout << "##### GODZINA " << n_godzina << endl;
        for (ushort i=0; i < sn.size(); i++) {
            sn[i]->restart();
        }
        godzina = n_godzina;
    }
    //sprawdzenie czy nie ma jakiegoś sygnału w _SIGNAL
    if (_SYGNAL > 0) {
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        cout << "otrzymałem sygnał " << _SYGNAL << endl;
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

        switch(_SYGNAL){
            case SIGHUP:
            case SIGINT:
            case SIGQUIT:
            case SIGABRT:
            case SIGKILL:
            case SIGTERM:
                stop = true;
                break;
            case SIGSEGV:
                cout << "SIGSEGV" << endl;
                stop = true;
                exit(11);
                break;
            case SIGUSR1: //sig=10  - sygnał przeczytania jeszcze raz pliku konfiguracyjnego
                _SYGNAL = 0;
                read_konfig(&config_file,konfig); //ponowne wczytanie pliku konfiguracyjnego, bo mogły nastąpic jakies zmiany
                grupy=konfig.get_groups();  //odczytanie listy grup z pliku konfiguracyjnego
                for (ushort i=0; i < sn.size(); i++)
                    delete(sn[i]);  //zatrzymanie watków i skasowanie wszystkich obiektów Sniffera
                sn.clear(); //wyczyszczenie sn
                for (list<string>::iterator grupa=grupy.begin();grupa != grupy.end();grupa++)
                    sn.push_back(new Sniffer(&konfig,(string) *grupa));
                cout << "SIGUSR1 END " << _SYGNAL << endl;
                break;
        }
        if (_SYGNAL !=0) cout << "_SYGNAL END="<< _SYGNAL << endl;
        _SYGNAL = 0; //sygnał obsłużony, czekamy na następny
    }
    sleep(1);
    cout << "WHILE END" << _SYGNAL << endl;
} // koniec pętli WHILE

pcap_close(fp);
return 0;
}
