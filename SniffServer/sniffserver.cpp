#include "sniffserver.h"
#include "sniffthread.h"

SniffServer::SniffServer(QObject *parent)
	: QTcpServer(parent)
{
	//	connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection(socketDescriptor())));
	ClientSocket = NULL;
}

SniffServer::~SniffServer()
{
	if (ClientSocket != NULL)
	{
		delete ClientSocket;
		ClientSocket = NULL;
	}
}

void SniffServer::incomingConnection(int socketDescriptor)
{
	if (ClientSocket != NULL)
	{
		return;
	}
	ClientSocket = new QTcpSocket();
	if (ClientSocket->setSocketDescriptor(socketDescriptor))
	{
		SniffThread *thread = new SniffThread(ClientSocket, this);
		connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()), Qt::DirectConnection);
		thread->start();
	}
	else
	{
		delete ClientSocket;
		ClientSocket = NULL;
	}
}

void SniffServer::closeConnection()
{
	if (ClientSocket != NULL)
	{
		delete ClientSocket;
		ClientSocket = NULL;
	}
}
