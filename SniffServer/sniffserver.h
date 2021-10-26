#ifndef SNIFFSERVER_H
#define SNIFFSERVER_H

#include <QObject>
#include <QTcpServer>
//#include <QNetworkSession>
//#include <QTcpSocket>
//#include <structs.h>

class SniffServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit SniffServer(QObject *parent = 0);
	~SniffServer();

protected slots:
    void incomingConnection(int socketDescriptor);
	void closeConnection();

private:
	QTcpSocket * ClientSocket;
signals:

};

#endif // SNIFFSERVER_H
