#ifndef SNIFFTHREAD_H
#define SNIFFTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <structs.h>
#include "sniff.h"

class SniffThread : public QThread
{
   Q_OBJECT
public:
	explicit SniffThread(QTcpSocket * ClientSocket, QObject *parent = 0);
	~SniffThread();
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
private slots:
	void readClient();

private:
	void SniffPackets();
	void sendData(QByteArray str);
	void sendEnd();

	QTcpSocket * ClientSocket;
	filterconfig Filtr;
	pckt_filter filter;
    QByteArray packet;
	QString responce;
	quint16 blockSize;

	QByteArray res;
	Sniffer * sn;
};

#endif // SNIFFTHREAD_H
