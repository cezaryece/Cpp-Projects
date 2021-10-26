#include "dialog.h"
#include <QScrollBar>
#include "itoa.h"
#include <QSemaphore>
#include <QTextStream>
#include <iostream>

const int BufferSize = 255;
uchar * Buffer = new uchar[BufferSize];
QString Result;
QSemaphore printedIN, printedOUT;
pcap_pkthdr * header;
const uchar * pkt_data;
bool isBuffer, stop;
char log[100],logIN[100],logOUT[100];

Dialog::Dialog(QWidget *parent) :
    QDialog(parent){

    connect(this,SIGNAL(PcktLimitReached()),this,SLOT(on_MainWindow_PcktLimitReached()));
    isBuffer = false;
    PacketCount = 0;

    ui.setupUi(this);
    ui.Interface->addItem("eth0");
    ui.Interface->addItem("eth1");

    ui.StartButton->setEnabled(true);
    ui.StopButton->setDisabled(true);
    ui.console->clear();
}

void Dialog::on_MainWindow_PcktLimitReached()
{
qDebug("max packets");
    stop = true;
    pInput->wait();pOutput->wait();
    pInput->exit();pOutput->exit();
    delete pInput;
    delete pOutput;
    qDebug("Treads killed");
    delete Buffer;
    qDebug("Buffer deleted");
    ui.StopButton->setDisabled(true);
    ui.StartButton->setEnabled(true);
}

void Dialog::on_StartButton_clicked()
{
    Filtr.pcktLimit = (unsigned short) ui.PcktLimit->value();
    if (ui.Protocol->text() != "") Filtr.Protocol = ui.Protocol->text().toUShort();
    else Filtr.Protocol = -1;
    Filtr.srcIP = ui.SrcIP->text();
    if (ui.SrcPort->text() != "") Filtr.srcPort = ui.SrcPort->text().toUInt();
    else Filtr.srcPort = 0;
    Filtr.destIP = ui.DestIP->text();
    if (ui.DestPort->text() != "") Filtr.destPort = ui.DestPort->text().toUInt();
    else Filtr.destPort = 0;
    Filtr.interface = ui.Interface->currentText();

    PacketCount = 0;
    stop = false;
    isBuffer = false;
    Buffer = new uchar[BufferSize];
    qDebug("Buffer created");
    pInput = new Pckt_In(Filtr.interface);
    pOutput = new Pckt_Out;
    connect(pOutput,SIGNAL(isResult()),this,SLOT(on_Result()));

    pOutput->setFiltr(&Filtr);
    pInput->start();
    pOutput->start();
    ui.StartButton->setDisabled(true);
    ui.StopButton->setEnabled(true);
}

void Dialog::on_StopButton_clicked()
{
    qDebug("stop clicked");
    stop = true;
    pInput->wait();
    pOutput->wait();
    pInput->exit();
    pOutput->exit();
    delete pInput;
    delete pOutput;
    qDebug("Treads killed");
    delete Buffer;
    qDebug("Buffer deleted");
    ui.StopButton->setDisabled(true);
    ui.StartButton->setEnabled(true);
}
void Dialog::on_ClearButton_clicked()
{
    ui.console->clear();
}
void Dialog::on_Result()
{
qDebug("onResult");
    ui.console->insertPlainText(Result);
    ui.console->insertPlainText("\n");
    QScrollBar *sb = ui.console->verticalScrollBar();
    sb->setValue(sb->maximum());
    if (Filtr.pcktLimit > 0)
    {
        PacketCount++;
        qDebug(itoa(PacketCount));
        if (PacketCount >= Filtr.pcktLimit)
        {
             emit PcktLimitReached();
             return;
        }
    }
    isBuffer = false;
    printedIN.release();printedOUT.release();
    qDebug("on_Result printed");
}

Pckt_In::Pckt_In(QString interface, QObject *parent) : QThread(parent),
pcap_data_max(BufferSize), // 65535;   //liczba bajtów przechwytywanych przez PCAP
pcap_timeout(1),    //timeout dla czekania na pakiety (ms)
dev(interface.toStdString())
{
    stop = false;
    fp = fp_init();
    isBuffer = false;
    qDebug("Pckt_In constructor");
}
Pckt_In::~Pckt_In()
{
    pcap_close(fp);
    qDebug("Pckt_In destructor");
}

pcap_t* Pckt_In::fp_init()
{
    //otwieramy urządenie
    if((fp=pcap_open_live(dev.c_str(),pcap_data_max,1,pcap_timeout,errbuf)) == NULL) {
        std::cout << "*** PCAP Error ***" << std::endl;
        std::cout << "Nie można otworzyć urządzenia: " << dev << " error: " << errbuf << std::endl;
        exit(1);
    }
    if(pcap_lookupnet(dev.c_str(),&ip_addr,&netmask,errbuf) == -1 ) {
        //printf("Nie można uzyskać maski: %s\n",errbuf);
        ip_addr=0;
        netmask=0;
    }
    //kompilacja filtru
    if(pcap_compile(fp,&fcode,filter.c_str(),0,netmask) < 0 ) {
        std::cout << "*** PCAP Error ***" << std::endl;
        std::cout << "Składnia filtru jest niepoprawna: " << filter << std::endl;
        pcap_close(fp);
        exit(1);
    }
    //ustawienie filtra
    if(pcap_setfilter(fp,&fcode) < 0) {
        std::cout << "*** PCAP Error ***" << std::endl;
        std::cout << "Błąd podczas ustawiania filtru: " << filter << std::endl;
        pcap_close(fp);
        exit(1);
    }
    if (pcap_setnonblock(fp,1,errbuf) == -1) std::cout << "SETNONBLOCK error: " << errbuf << std::endl;
    return fp;
}

void Pckt_In::run()
{
    int res;
    ipheader* ih;

    forever
    {
        qDebug("Pckt_In czeka na !isBuffer lub stop");
        while (!stop && isBuffer) { usleep(100); }
        if (stop)
        {
            qDebug("Pckt_In stopping");
            return;
        }

        if (!isBuffer)
        {
            res = pcap_next_ex(fp, &header, &pkt_data);
            if (res == 1)
            {
                ih=(struct ipheader*)(pkt_data+14);
                memcpy(Buffer,pkt_data,BufferSize);
                isBuffer = true;
                qDebug("isBuffer = TRUE / Pckt_In czeka na printed");
                while (!printedIN.tryAcquire() && !stop) { usleep(100); }
                if (stop)
                {
                    qDebug("Pckt_In stopping");
                    return;
                }
                else qDebug("Pckt_In printed");
            }
        }
        else
        {
            qDebug("Pckt_In ma zajęty Buffer");
            usleep(100);
            if (stop)
            {
                qDebug("Pckt_In stopping");
                return;
            }
        }
    }
}

Pckt_Out::Pckt_Out(QObject *parent) : QThread(parent), head_max(15), dane_max(BufferSize), eth_len(14), uh_len(8), ich_len(8)
{
    stop = false;
    dump = new char[head_max];
    qDebug("Pckt_Out constructor");
}

Pckt_Out::~Pckt_Out()
{
    delete dump;
    qDebug("Pckt_Out destructor");
}

void Pckt_Out::setFiltr(pckt_filter *filter) {
    Filtr = filter;
}

QString Pckt_Out::packethandler(const u_char * pkt_data) {
qDebug("\n PACKET HANDLER START\n");
    str = "";
    QTextStream output(&str);

    ih = (struct ipheader*)(pkt_data+eth_len); //pomijamy 14 bajtów zarezerwowane dla nagłówka ethernet
    if (Filtr->Protocol >= 0)
    {
        qDebug("Filtr.Protocol >=0");
        if (Filtr->Protocol != (short) ih->ip_p)
        {
            isBuffer = false;
            printedIN.release();
            return "";
        }
//        else qDebug(itoa(ih->ip_p));
    }

    QString dane = (char*) (pkt_data + eth_len + (ih->ip_hl * 4));  //dane zawierają dane pakietu IP, czyli pakiety TCP,UDP i inne z nagłówkiem

    source_addr.sin_addr.s_addr = ih->ip_src;
    strncpy(sourceIP, inet_ntoa(source_addr.sin_addr), 16);

//if ((Filtr->srcIP != "") && (Filtr->srcIP != QString(sourceIP))) return "";
//    if ((Filtr->srcPort != "") && (Filtr->srcPort != QString(ntohs(th->tcp_sp)))) return "";

    dest_addr.sin_addr.s_addr=ih->ip_dst;
    strncpy(destIP,inet_ntoa(dest_addr.sin_addr),16);
//    if ((Filtr->destIP != "") && (Filtr->destIP != destIP)) return "";
//    if ((Filtr->srcPort != "") && (Filtr->srcPort != QString(ntohs(th->tcp_dp)))) return "";

    output << "|" << (ushort) ih->ip_p << "|";

    switch (ih->ip_p) {
        case 6: //TCP
            th=(struct tcpheader*) (dane.toStdString().c_str());
            th_len = th->tcp_hlen * 4;
            len = ih->ip_len - th_len; //długość danych pakietu
            dane = dane + th_len;
            output << sourceIP << ":" << ntohs(th->tcp_sp) << "|" << destIP << ":" << ntohs(th->tcp_dp) <<"|" << (ushort) ih->ip_len << "|";
        break;
        case 17: //UDP
            uh=(struct udpheader*) (dane.toStdString().c_str());
            len = uh->udp_len - uh_len; //długość danych pakietu
            dane = dane + uh_len;
            output << sourceIP << ":" << ntohs(uh->udp_sp) << "|" << destIP << ":" << ntohs(uh->udp_dp) << "|" << (ushort) uh->udp_len << "|";
        break;
        case 1: //ICMP
            ich=(struct icmpheader*) (dane.toStdString().c_str());
            len = ih->ip_len - ich_len;
            dane = dane + ich_len;
            output << sourceIP << "|" << destIP << "|" << (ushort) ich->icmp_typ << ":" << (ushort) ich->icmp_code << "|";
        break;
        default:
        len = ih->ip_len; //długość danych pakietu
        output << sourceIP << ":" << destIP << "|" << (ushort) ih->ip_len << "|";
        break;
    }
    if (len > dane_max) len = dane_max; //ograniczenie dlugosci wyprowadzanych danych
    dane.truncate(len);
//    qDebug(output.string()->toStdString().c_str());
    return output.string()->append(dane);
}

void Pckt_Out::run()
{
    qDebug("Pckt_Out RUN");
    forever
    {
        qDebug("Pckt_Out czeka na isBuffer lub stop");
        while (!stop && !isBuffer) { usleep(100); }
//        strcpy(logOUT, "Pckt_Out ");
//        qDebug(strncat(logOUT,itoa(stop),99));
        if (stop)
        {
            qDebug("Pckt_Out stopping");
            return;
        }
        if (isBuffer)
        {
            qDebug("isBuffer OUT");
            Result = packethandler(Buffer);
            if (Result != "")
            {
//                qDebug("REsult:");
//                qDebug(Result.toStdString().c_str());
                qDebug(" +++++++++++++++++++++ ");
                emit isResult();
                qDebug("Pckt_Out czeka na printed");
                while (!printedOUT.tryAcquire() && !stop) { usleep(100); }
                if (stop) return;
                qDebug("Pckt_Out printed");
            }
            else
            {
                qDebug("Pusty RESULT");
                usleep(100);
                if (stop) return;
            }
        }
        else
        {
            qDebug("Buffer pusty");
            usleep(100);
        }
        if (stop) return;
    }
}
