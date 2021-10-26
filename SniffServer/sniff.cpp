#include "sniff.h"
#include <arpa/inet.h>
#include "structs.h"
#include "../MY_LIBS/QTip.h"
#include <QDebug>

using namespace std;

//##########################################
// definicje klasy Sniffer
//##########################################

//KONSTRUKTOR na bazie parametrów z configu
Sniffer::Sniffer(filterconfig Filtr) {
    //wczytuje parametry z pliku konfiguracyjnego
	dev.setNum(Filtr.eth_N);
	dev.prepend("eth");
	setblock = true;
	multicast = false;
	onlydata = false;
	pcktLen = Filtr.pcktLen;
	if (pcktLen == 0) pcktLen = 20;

	if (Filtr.Protocol >= 0) {
		protocol.setNum(Filtr.Protocol);
		if (!filter.isEmpty()) filter.append(" and ");
		filter += "ip proto " + protocol;
	}
	if (Filtr.srcIP > 0) {
		ip_s = IPint2string(Filtr.srcIP);
		if (!filter.isEmpty()) filter.append(" and ");
		filter += " src host " + ip_s;
	}
	if (Filtr.destIP > 0) {
		ip_d = IPint2string(Filtr.destIP);
		if (!filter.isEmpty()) filter.append(" and ");
		filter += " dst host " + ip_d;
	}
	if (Filtr.srcPort > 0) {
		port_s.setNum(Filtr.srcPort);
		if (!filter.isEmpty()) filter.append(" and ");
		filter += " src port " + port_s;
	}
	if (Filtr.destPort) {
		port_d.setNum(Filtr.destPort);
		if (!filter.isEmpty()) filter.append(" and ");
		filter += " dst port " + port_d;
	}
	if (Filtr.multicast) {
		multicast = true;
		if (!filter.isEmpty()) filter.append(" and ");
		filter.append("ip multicast");
	}
	if (Filtr.onlydata) {
		onlydata = true;
	}
//	qDebug() << "filter: " << filter;
//	qDebug() << "dev: " << dev;
//	qDebug() << "proto: " << protocol;
//	qDebug() << "setblock: " << setblock;
//	qDebug() << "multicast: " << multicast;
//	qDebug() << "packet Len" << pcktLen;
//	qDebug() << "##########################";

	fp_init(); //inicjalizacja fp
}

//##########################################
//DESTRUKTOR
Sniffer::~Sniffer() {
	pcap_breakloop(fp);
	pcap_close(fp);
}

//##########################################
// Sniffer::run
//##########################################
QByteArray Sniffer::runme() //uruchomienie procesu zczytywania pakietów
{
	pcap_pkthdr * header;
	const uchar * pkt_data;
	int res = 0;
	QByteArray resBA;
	while (res == 0)
		res = pcap_next_ex(fp, &header, &pkt_data);
	if (res == 1)
		resBA = packethandler(pkt_data);  //funkcja obsługi odczytanych pakietów
	return resBA;
}

//##########################################
// Sniffer::fp_init
//##########################################
void Sniffer::fp_init()
{
	const uint pcap_data_max = 128 + pcktLen; // 65535;   //liczba bajtów przechwytywanych przez PCAP
	const uint pcap_timeout = 10;    //timeout dla czekania na pakiety (ms)

    //otwieramy urządenie
	if((fp=pcap_open_live(dev.toStdString().c_str(),pcap_data_max,1,pcap_timeout,errbuf))==NULL) {
		qDebug() << "*** PCAP Error ***";
		qDebug() << "Nie można otworzyć urządzenia: " << dev << " error: " << errbuf;
        exit(1);
    }
	if(pcap_lookupnet(dev.toStdString().c_str(),&ip_addr,&netmask,errbuf)==-1) {
        //printf("Nie można uzyskać maski: %s\n",errbuf);
        ip_addr=0;
        netmask=0;
    }
    //kompilacja filtru
	if (!filter.isEmpty())
	{
		if(pcap_compile(fp,&fcode,(char *) filter.toStdString().c_str(),0,netmask)<0) {
			qDebug() << "*** PCAP Error ***" << endl;
			qDebug() << "Składnia filtru jest niepoprawna: " << filter;
			pcap_close(fp);
			exit(1);
		}
		//ustawienie filtra
		if(pcap_setfilter(fp,&fcode)<0) {
			qDebug() << "*** PCAP Error ***" << endl;
			qDebug() << "Błąd podczas ustawiania filtru: " << filter;
			pcap_close(fp);
			exit(1);
		}
	}
	if ((setblock) && ( pcap_setnonblock(fp,1,errbuf) == -1))
		qDebug() << "SETNONBLOCK error: " << errbuf;
}

QByteArray Sniffer::packethandler(const u_char * pkt_data)
{
	ipheader* ih;
	tcpheader* th;
	udpheader* uh;
	icmpheader* ich;
//	ushort ic_len;
	const ushort dane_max = pcktLen;
	uint len;
	ushort th_len;
	const ushort eth_len = 14;  //wielkość nagłówka Ethernet
	const ushort uh_len = 8;    // wielkośc nagłówka UDP
	const ushort ich_len = 8;   //wielkość nagłówka ICMP

	QString temps;
	QByteArray str;

	ih=(struct ipheader*)(pkt_data+eth_len); //pomijamy 14 bajtów zarezerwowane dla nagłówka ethernet

	char * dane = (char*)(pkt_data + eth_len + (ih->ip_hl *4));  //dane zawierają dane pakietu IP, czyli pakiety TCP,UDP i inne z nagłówkiem

	QString sourceIP = IPint2string(ih->ip_src);
	QString destIP = IPint2string(ih->ip_dst);

	if (!onlydata)
	{
		str = str.number(ih->ip_p);
		str += "|";
	}

	switch (ih->ip_p)
	{
		case 6: //TCP
			th=(struct tcpheader*) (dane);
			th_len = th->tcp_hlen * 4;
			len = ih->ip_len - th_len; //długość danych pakietu
			dane = dane + th_len;
			if (onlydata) break;
			str +=  sourceIP + ":" + temps.number(ntohs(th->tcp_sp)) + "|";
			str += destIP + ":" + temps.number(ntohs(th->tcp_dp));
			str += "|" + temps.number(ih->ip_len)  + "|";
		break;
		case 17: //UDP
			uh=(struct udpheader*) (dane);
			len = uh->udp_len - uh_len; //długość danych pakietu
			dane = dane + uh_len;
			if (onlydata) break;
			str += sourceIP + ":" + temps.number(ntohs(uh->udp_sp));
			str += "|" + destIP + ":" + temps.number(ntohs(uh->udp_dp));
			str += "|" + temps.number(uh->udp_len) + "|" + temps.number(len) + "|";
		break;
		case 1: //ICMP
			ich=(struct icmpheader*) (dane);
			len = ih->ip_len - ich_len;
			dane = dane + ich_len;
			if (onlydata) break;
			str += sourceIP + "|" + destIP + "|" + temps.number(ich->icmp_typ);
			str += ":" + temps.number(ich->icmp_code) + "|";
		break;
		default:
			len = ih->ip_len; //długość danych pakietu
			if (onlydata) break;
			str += sourceIP + ":" + destIP + "|" + temps.number(len) + "|";
			break;
	}
	if (len > dane_max) len = dane_max; //ograniczenie dlugosci wyprowadzanych danych
	QByteArray daneBA;
	daneBA = QByteArray::fromRawData(dane,(int) len);

	if (!onlydata)
		daneBA .prepend(str);
	return daneBA;
}
