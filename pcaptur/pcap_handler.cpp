#include <fstream>
#include <iostream>
#include <arpa/inet.h>
#include "pcap_handler.h"
#include "bytewrite/bytewrite.h"

using namespace std;

const void packethandler(ofstream &file, const u_char * pkt_data, bool human) { //jako trzeci parametr otrzymujemy cały pakiet
    //etheader* eth;
    ipheader* ih;
    tcpheader* th;
    udpheader* uh;
    icmpheader* ich;
    ushort eth_len;
    ushort ic_len;

    eth_len = 14;

    char sourceIP[16],destIP[16];
    sockaddr_in source_addr,dest_addr;

    ih=(struct ipheader*)(pkt_data+eth_len); //pomijamy 14 bajtów zarezerwowane dla nagłówka ethernet
    //if ((ih->ip_src == UINT_MAX) || (ih->ip_dst == UINT_MAX)) return; //odrzucenie pakietów rozgłoszeniowych

    unsigned short header_len = ih->ip_hl *4; //długość headera IP
    //unsigned char ip_flags = ih->ip_off >> 13;
    //unsigned short 	ip_offset = (ih->ip_off & 0x1fff) << 3;
    //unsigned short 	ip_offset = ih->ip_off & 0x1fff;

    char* dane = (char*)(pkt_data + eth_len + header_len);  //dane zawierają dane pakietu IP, czyli pakiety TCP,UDP i inne z nagłówkiem i własciwymi danymi
    string dane_str = "";
    unsigned int len;
    unsigned short int th_len,uh_len,ich_len;

    if (human) {
        source_addr.sin_addr.s_addr=ih->ip_src;
        dest_addr.sin_addr.s_addr=ih->ip_dst;
        strncpy(sourceIP,inet_ntoa(source_addr.sin_addr),16);
        strncpy(destIP,inet_ntoa(dest_addr.sin_addr),16);
        file << "|" << (short) ih->ip_p << "|";
    }
    else file << ih->ip_p;

    switch (ih->ip_p) {
        case 6: //TCP
            th=(struct tcpheader*) (dane);
            th_len = th->tcp_hlen * 4;

            len = ih->ip_len - th_len; //długość danych pakietu
            if (len > 96) len = 96; //ograniczenie dlugosci wyprowadzanych danych
            dane_str.assign(dane+th_len,len);
            if (!human) {
                bytewrite(file,ih->ip_src);
                bytewrite(file,th->tcp_sp,2);
                bytewrite(file,ih->ip_dst);
                bytewrite(file,th->tcp_dp,2);
                bytewrite(file,ih->ip_len,2);
            }
            else file << sourceIP << ":" << ntohs(th->tcp_sp) << "|" << destIP << ":" << ntohs(th->tcp_dp) <<"|" << (ushort) ih->ip_len << "|";
        break;
        case 17: //UDP
            uh=(struct udpheader*) (dane);
            if (uh->udp_dp == 53 || uh->udp_sp == 53) return; //pomijamy pakiety do DNS

            uh_len = 8; // wielkośc nagłówka UDP
            len = uh->udp_len - uh_len; //długość danych pakietu
            if (len > 96) len = 96; //ograniczenie dlugosci wyprowadzanych danych
            dane_str.assign(dane+uh_len,len);
            if (!human) {
                bytewrite(file,ih->ip_src);
                bytewrite(file,uh->udp_sp,2);
                bytewrite(file,ih->ip_dst);
                bytewrite(file,uh->udp_dp,2);
                bytewrite(file,uh->udp_len,2);
            }
            else file << sourceIP << ":" << ntohs(uh->udp_sp) << "|" << destIP << ":" << ntohs(uh->udp_dp) << "|" << (ushort) uh->udp_len << "|";
        break;
        case 1: //ICMP
            ich=(struct icmpheader*) (dane);
            ich_len = 8;
            ic_len = ih->ip_len - ich_len;
            len = ic_len; //długość danych pakietu
            if (len > 32) len = 32; //ograniczenie dlugosci wyprowadzanych danych
            dane_str.assign(dane+ich_len,len);
            if (!human) {
                bytewrite(file,ih->ip_src);
                bytewrite(file,ih->ip_dst);
                bytewrite(file,ic_len,2);
            }
            else file << sourceIP << "|" << destIP << "|" << (ushort) ich->icmp_typ << ":" << (ushort) ich->icmp_code << "|";
            file << ich->icmp_typ << ich->icmp_code;
        break;
        default:
            len = ih->ip_len; //długość danych pakietu
            if (len > 128) len = 128; //ograniczenie dlugosci wyprowadzanych danych
            dane_str.assign(dane);
            dane_str.substr(0,len);
            if (!human) {
                bytewrite(file,ih->ip_src);
                bytewrite(file,ih->ip_dst);
                bytewrite(file,ih->ip_len,2);
            }
            else file << sourceIP << ":" << destIP << "|" << (ushort) ih->ip_len << "|";
            break;
    }
    file << dane_str << "\n";
}
