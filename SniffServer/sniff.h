#ifndef SNIFF_H
#define SNIFF_H

#include <pcap.h>  //tutaj mamy plik nagłówkowy biblioteki
#include <QString>
#include <fstream>
#include "structs.h"

class Sniffer {
    public:
		bool Stop;
		Sniffer(filterconfig Filtr);   // konstruktor wczytuje parametry z pliku 'config' i grupy 'grupa'
		~Sniffer();  //destruktor
		QByteArray runme(); //uruchomienie procesu

	private:
        pcap_t * fp;            //wewnętrzna structura pcap
		QString dev;        //urządzenie sieciowe
		QString filter;     //string z całym filterm
		QString ip_s,ip_d;  //IP źródłowe i docelowe
		QString port_s,port_d;     //porty źródłowy i docelowy
		QString protocol;   //typ protokołu IP (domyślnie będzie to protokół TCP, czyli 6)
		bool multicast;
		bool setblock;
		uint pcktLen;
		bool onlydata;

		char errbuf[PCAP_ERRBUF_SIZE]; //jeżeli będziemy chcieli obsługiwać błędy
		uint netmask,ip_addr;  //wewnętrzne zmienne potrzebne pcap
		struct bpf_program fcode;//wewnętrzna structura pcap

        void fp_init();

		QByteArray packethandler(const u_char * pkt_data);
};
#endif // SNIFF_H
