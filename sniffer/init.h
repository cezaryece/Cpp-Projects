#ifndef INIT_H
#define INIT_H

#include <pcap.h>  //tutaj mamy plik nagłówkowy biblioteki
#include <string>
#include <QSettings>
#include <fstream>

extern ushort _SYGNAL;

class Sniffer {
    std::string Snazwa;     //nazwa grupy parametrów w configu = katalog z plikami zrzutu pakietów
    std::string path;       //ścieżka do głównego katalogu z katalogami do zrzutu pakietów ("/1T")
    std::string dir;        //path + Snazwa
    std::string dev;        //urządzenie sieciowe
    std::string filter;     //string z całym filterm
    std::string ip_s,ip_d;  //IP źródłowe i docelowe
    uint port_s,port_d;     //porty źródłowy i docelowy
    std::string protocol;   //typ protokołu IP (domyślnie będzie to protokół TCP, czyli 6)
    bool setblock;

    char errbuf[PCAP_ERRBUF_SIZE]; //jeżeli będziemy chcieli obsługiwać błędy
    uint netmask,ip_addr;  //wewnętrzne zmienne potrzebne pcap
    struct bpf_program fcode;//wewnętrzna structura pcap

    public:
        std::string filename;   //nazwa pliku do którego nastepuje zrzut pakietów = czas otwarcia pliku
        pcap_t * fp;            //wewnętrzna structura pcap
        std::ofstream dumpfile; //plik do zapisu pakietów
        std::string nazwa();

        Sniffer(QSettings * settings);   // konstruktor wczytuje parametry z pliku 'config' i grupy 'grupa'
        ~Sniffer();  //destruktor

        void run(); //uruchomienie procesu
        void stop();  //zapis pakietów do nowego pliku
        void loop(); //pętla przechwytująca pakiety uruchamiana jako wątek ze Sniffer::run()
        void fp_init();
        void sygnal(ushort);
        void restart();

    private:
        Sniffer (const Sniffer&);  //konstruktor kopiujący
};
#endif // INIT_H
