#ifndef INIT_H
#define INIT_H

#endif // INIT_H

#include <pcap.h>  //tutaj mamy plik nagłówkowy biblioteki
#include <string>
#include <glibmm/keyfile.h>
#include <iostream>
#include <fstream>

//extern "C" void loop (void*);
//static void * sn_loop (void * sn);

extern ushort _SYGNAL;

class Sniffer {
    char * Snazwa;          //nazwa grupy parametrów w configu = katalog z plikami zrzutu pakietów
    std::string path;       //ścieżka do głównego katalogu z katalogami do zrzutu pakietów ("/1T")
    std::string filename;   //nazwa pliku do którego nastepuje zrzut pakietów = czas otwarcia pliku
    std::ofstream dumpfile; //plik do zapisu pakietów

    std::string dev;        //urządzenie sieciowe
    std::string filter;     //string z całym filterm
    std::string ip_s,ip_d;  //IP źródłowe i docelowe
    uint port_s,port_d;     //porty źródłowy i docelowy
    std::string proto;      //typ protokołu IP (domyślnie będzie to protokół TCP, czyli 6)
    pcap_t * fp;            //wewnętrzna structura pcap
    ushort SYGNAL;
    ushort loops;

    
    char errbuf[PCAP_ERRBUF_SIZE]; //jeżeli będziemy chcieli obsługiwać błędy
    uint netmask,ip_addr;  //wewnętrzne zmienne potrzebne pcap
    struct bpf_program fcode;//wewnętrzna structura pcap

    pthread_t loopthread;   //wątek zczytujacy pakiety
    bool thread_stop;       // sygnał dla watku, że ma zakończyć pracę
    bool thread_running;    //świadczy o tym, że wątek już pracuje
    bool thread_testcancel;
    bool thread_start;
    bool human;             //czy dane mają być zapisane w postaci dla człowieka czy binarnej (deafult jest binarnie)

    public:
        Sniffer();
        Sniffer(const Glib::KeyFile*,const std::string);   // konstruktor wczytuje parametry z pliku 'config' i grupy 'grupa'
        Sniffer (const Sniffer&);  //konstruktor kopiujący
        ~Sniffer();  //destruktor

        void run(); //uruchomienie procesu
        void stop();  //zapis pakietów do nowego pliku
        void loop(); //pętla przechwytująca pakiety uruchamiana jako wątek ze Sniffer::run()
        char * nazwa();
        void sygnal(ushort);
        void restart();
};
