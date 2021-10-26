#include "sniffthread.h"
#include "../MY_LIBS/QTip.h"
#include <QtNetwork>
#include <QTcpSocket>

SniffThread::SniffThread(QTcpSocket * CSocket, QObject *parent)
	: QThread(parent),ClientSocket(CSocket), responce(""), blockSize(0)
{
}
SniffThread::~SniffThread()
{
	qDebug() << "~SniffThread()";
	wait();
}

void SniffThread::readClient()
{
	//odczytanie danych dla filtra
	QDataStream in(ClientSocket);
	in.setVersion(QDataStream::Qt_4_0);
	if (blockSize == 0) {
		if (ClientSocket->bytesAvailable() < (int)sizeof(quint16))
			return;
		in >> blockSize;
	}
	if (ClientSocket->bytesAvailable() < blockSize)
		return;
	in >> (quint8&) Filtr.eth_N >> (quint8&) Filtr.Protocol >> (quint32&) Filtr.pcktLen >> (quint32&) Filtr.pcktLimit >> (quint32&) Filtr.srcIP >> (quint16&) Filtr.srcPort >> (quint32&) Filtr.destIP >> (quint16&) Filtr.destPort >> (quint8&) Filtr.multicast >> (quint8&) Filtr.onlydata;
	SniffPackets();
	ClientSocket->disconnectFromHost();
	qDebug() << "SniffThread::readClient()" << ClientSocket->state();
	while (ClientSocket->state() != QAbstractSocket::UnconnectedState)
		ClientSocket->waitForDisconnected();
	ClientSocket->disconnect(this);
	exit();
}

void SniffThread::run()
{
	qDebug() << "SniffThread::run()";
	connect(ClientSocket, SIGNAL(readyRead()), this, SLOT(readClient()), Qt::DirectConnection);
	//connect(ClientSocket, SIGNAL(disconnected()), parent, SLOT(closeConnection()), Qt::DirectConnection);
	exec();
}

void SniffThread::SniffPackets()
{
	sn = new Sniffer(Filtr);
	QByteArray res;
	if (Filtr.pcktLimit == 0)
		Filtr.pcktLimit = 1;
	for (uint i=0; i < Filtr.pcktLimit; i++)
	{
		res = sn->runme();
		if (res.isEmpty())
			i--;
		else
			sendData(res);
	}
	sendEnd();
	delete sn;
}

void SniffThread::sendData(QByteArray str)
{
	QString temps;
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_3);
	out << (quint16)0;
	out << str;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	ClientSocket->write(block);
	ClientSocket->flush();
}

void SniffThread::sendEnd()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_3);
	out << (quint16) 0xFFFF;
	ClientSocket->write(block);
	ClientSocket->flush();
}
