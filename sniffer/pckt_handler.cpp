#include <arpa/inet.h>
#include "pckt_handler.h"
#include <cstring>     //dla memset, memcpy
#include <iostream>

using namespace std;

//zmienne i stałe globalne dla funkcji packet_handler
//etheader* eth;
ipheader* ih;
tcpheader* th;
udpheader* uh;
icmpheader* ich;
ushort ic_len;
const ushort head_max = 15;
const ushort dane_max = 96;
char * dump = new char[head_max];  //zapisujemy tylko nagłówki
uint len;
ushort th_len;
const ushort eth_len = 14;  //wielkość nagłówka Ethernet
const ushort uh_len = 8;    // wielkośc nagłówka UDP
const ushort ich_len = 8;   //wielkość nagłówka ICMP

char sourceIP[16],destIP[16];
sockaddr_in source_addr,dest_addr;


void packethandler(std::ofstream &file, const u_char * pkt_data, ushort sec, bool human) { //jako trzeci parametr otrzymujemy cały pakiet
	memset(dump, 0, head_max); //wyzerowanie danych
	
	ih=(struct ipheader*)(pkt_data+eth_len); //pomijamy 14 bajtów zarezerwowane dla nagłówka ethernet
	//if ((ih->ip_src == UINT_MAX) || (ih->ip_dst == UINT_MAX)) return; //odrzucenie pakietów rozgłoszeniowych
	
	char * dane = (char*)(pkt_data + eth_len + (ih->ip_hl *4));  //dane zawierają dane pakietu IP, czyli pakiety TCP,UDP i inne z nagłówkiem
	
	if (human) {
		source_addr.sin_addr.s_addr=ih->ip_src;
		dest_addr.sin_addr.s_addr=ih->ip_dst;
		strncpy(sourceIP,inet_ntoa(source_addr.sin_addr),16);
		strncpy(destIP,inet_ntoa(dest_addr.sin_addr),16);
		file << "|" << (ushort) ih->ip_p << "|";
	}
	else {
		memcpy(dump,&sec,2);        //zapis liczby sekund w pełnej godzinie
		memcpy(dump + 2,&ih->ip_p,1);   //zapis protokołu
	}
	
	switch (ih->ip_p) {
	case 6: //TCP
		th=(struct tcpheader*) (dane);
		if (!human) {
			memcpy(dump + 3,&ih->ip_src,4);
			memcpy(dump + 7,&th->tcp_sp,2);
			memcpy(dump + 9,&ih->ip_dst,4);
			memcpy(dump + 13,&th->tcp_dp,2);
			//                memcpy(dump + 15,&ih->ip_len,2);
			
		}
		else {
			th_len = th->tcp_hlen * 4;
			len = ih->ip_len - th_len; //długość danych pakietu
			dane = dane + th_len;
			
			file << sourceIP << ":" << ntohs(th->tcp_sp) << "|" << destIP << ":" << ntohs(th->tcp_dp) <<"|" << (ushort) ih->ip_len << "|";
		}
		break;
	case 17: //UDP
		uh=(struct udpheader*) (dane);
		//            if (uh->udp_dp == 53 || uh->udp_sp == 53) return; //pomijamy pakiety do DNS
		if (!human) {
			memcpy(dump + 3,&ih->ip_src,4);
			memcpy(dump + 7,&uh->udp_sp,2);
			memcpy(dump + 9,&ih->ip_dst,4);
			memcpy(dump + 13,&uh->udp_dp,2);
			//                memcpy(dump + 15,&uh->udp_len,2);
		}
		else {
			len = uh->udp_len - uh_len; //długość danych pakietu
			dane = dane + uh_len;
			file << sourceIP << ":" << ntohs(uh->udp_sp) << "|" << destIP << ":" << ntohs(uh->udp_dp) << "|" << (ushort) uh->udp_len << "|";
		}
		break;
	case 1: //ICMP
		ich=(struct icmpheader*) (dane);
		if (!human) {
			memcpy(dump + 3,&ih->ip_src,4);
			memcpy(dump + 7,&ich->icmp_typ,1);
			memcpy(dump + 8,&ich->icmp_code,1);
			memcpy(dump + 9,&ih->ip_dst,4);
			memcpy(dump + 13,&ich->icmp_check,2);
			//                memcpy(dump + 15,&ic_len,2);
		}
		else {
			len = ih->ip_len - ich_len;
			dane = dane + ich_len;
			file << sourceIP << "|" << destIP << "|" << (ushort) ich->icmp_typ << ":" << (ushort) ich->icmp_code << "|";
		}
		break;
	default:
		if (!human) {
			memcpy(dump + 3,&ih->ip_src,4);
			memcpy(dump + 9,&ih->ip_dst,4);
			//                memcpy(dump + 15,&ih->ip_len,2);
		}
		else {
			len = ih->ip_len; //długość danych pakietu
			file << sourceIP << ":" << destIP << "|" << (ushort) ih->ip_len << "|";
		}
		break;
	}
	if (human) {
		if (len > dane_max) len = dane_max; //ograniczenie dlugosci wyprowadzanych danych
		file.write(dane,len);
		file << endl;
	}
	else {
		//memcpy(dump + head_max, dane, len);
		//file.write(dump,head_max + dane_max);
		file.write(dump,head_max);
	}
	return;
}
