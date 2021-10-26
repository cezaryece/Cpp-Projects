#ifndef PCKT_HANDLER_H
#define PCKT_HANDLER_H

#include <fstream>

extern unsigned short _SYGNAL;

//nagłówek Ethernet
struct etheader
{
unsigned char edst[6]; 	/* Ethernet Destination Address */
unsigned char esrc[6]; 	/* Ethernet Source Address */
unsigned short etype;	/* Ethernet Protocol Type */
};

// nagłówek IP
struct ipheader
{
unsigned char ip_hl:4,ip_v:4;
unsigned char ip_ds;
unsigned short int ip_len;
unsigned short int ip_id;
unsigned short int ip_off;
unsigned char ip_ttl;
unsigned char ip_p;
unsigned short int ip_sum;
unsigned int ip_src;
unsigned int ip_dst;
};

//nagłówek TCP
struct tcpheader
{
unsigned short int tcp_sp, tcp_dp;
unsigned int tcp_seq, tcp_accpt;
unsigned char tcp_off:4,tcp_hlen:4;
unsigned char tcp_flags;
unsigned short int tcp_wind, tcp_csum, tcp_prio;
};

//nagłówek UDP
struct udpheader
{
unsigned short udp_sp;
unsigned short udp_dp;
unsigned short udp_len;
unsigned short udp_check;
};

//nagłówek ICMP
struct icmpheader
{
unsigned char icmp_typ, icmp_code;
unsigned short icmp_check, icmp_id, icmp_seq;
};

//funkcja wywoływana dla każdego pakietu
void packethandler(std::ofstream &file, const unsigned char * pkt_data, unsigned short sec, bool human = false);

#endif // PCKT_HANDLER_H
