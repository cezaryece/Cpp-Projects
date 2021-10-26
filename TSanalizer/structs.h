#ifndef PCKT_HANDLER_H
#define PCKT_HANDLER_H

#include "QString"

struct etheader
{
	unsigned char edst[6]; 	/* Ethernet Destination Address */
	unsigned char esrc[6]; 	/* Ethernet Source Address */
	unsigned short etype;	/* Ethernet Protocol Type */
};
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
struct tcpheader
{
	unsigned short int tcp_sp, tcp_dp;
	unsigned int tcp_seq, tcp_accpt;
	unsigned char tcp_off:4,tcp_hlen:4;
	unsigned char tcp_flags;
	unsigned short int tcp_wind, tcp_csum, tcp_prio;
};
struct udpheader
{
	unsigned short udp_sp;
	unsigned short udp_dp;
	unsigned short udp_len;
	unsigned short udp_check;
};
struct icmpheader
{
	unsigned char icmp_typ, icmp_code;
	unsigned short icmp_check, icmp_id, icmp_seq;
};
struct pckt_filter
{
	unsigned short pcktLimit;
	short Protocol;
	QString srcIP, destIP, interface;
	unsigned int srcPort, destPort;
};
//struktura danych wysyłanych do serwera z konfiguracją filtra
struct __attribute__ ((__packed__)) filterconfig
{
	unsigned char		eth_N;	// nr karty sieciowej ethX
	char				Protocol;	// protokół
	unsigned int		pcktLen;// długość zwracanego pakietu (0 - cały pakiet)
	unsigned int		pcktLimit;// ilość zwracanych pakietów
	unsigned int		srcIP;	// IP źródła
	unsigned short int	srcPort;	// port źródła
	unsigned int        destIP;	// IP celu
	unsigned short int  destPort;	// port celu
	bool				multicast;
	bool				onlydata; //zwróć tylko dane pakietu
};

#endif // PCKT_HANDLER_H
