#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialog.h"
#include <QThread>
#include <arpa/inet.h>
#include "pcap.h"
#include "pckt_handler.h"

class Pckt_In : public QThread
{
    Q_OBJECT
public:
    Pckt_In(QString interface, QObject *parent = 0);
    ~Pckt_In();
protected:
    void run();
private:
    pcap_t * fp_init();
    pcap_t * fp;
    const uint pcap_data_max; //liczba bajtów przechwytywanych przez PCAP
    const uint pcap_timeout;  //timeout dla czekania na pakiety (ms)
    const std::string dev;
    char errbuf[PCAP_ERRBUF_SIZE]; //jeżeli będziemy chcieli obsługiwać błędy
    uint netmask,ip_addr;          //wewnętrzne zmienne potrzebne pcap
    struct bpf_program fcode;      //wewnętrzna structura pcap
    std::string filter;
};

class Pckt_Out : public QThread
{
    Q_OBJECT
public:
    Pckt_Out(QObject *parent = 0);
    ~Pckt_Out();
    void setFiltr(pckt_filter * filter);
protected:
    void run();
signals:
    void isResult();
private:
    etheader* eth;
    ipheader* ih;
    tcpheader* th;
    udpheader* uh;
    icmpheader* ich;
    ushort ic_len;
    const ushort head_max;
    const ushort dane_max;
    char * dump;  //zapisujemy tylko nagłówki
    uint len;
    ushort th_len;
    const ushort eth_len;  //wielkość nagłówka Ethernet
    const ushort uh_len;    // wielkośc nagłówka UDP
    const ushort ich_len;   //wielkość nagłówka ICMP

    char sourceIP[16],destIP[16];
    sockaddr_in source_addr,dest_addr;
    pckt_filter * Filtr;
    QString str;
    QString packethandler(const unsigned char * pkt_data);
};
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

private:
    Ui::Dialog ui;
    unsigned short int PacketLimit, PacketCount;
    Pckt_In * pInput;
    Pckt_Out * pOutput;
    pckt_filter Filtr;

signals:
    void PcktLimitReached();

private slots:
    void on_ClearButton_clicked();
    void on_StartButton_clicked();
    void on_StopButton_clicked();
    void on_MainWindow_PcktLimitReached();
    void on_Result();
};
#endif // DIALOG_H
