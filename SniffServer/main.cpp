#include <QtCore>
#include <QCoreApplication>
#include <QtNetwork>
#include <sniffserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	SniffServer server;
	if (!server.listen(QHostAddress::Any, 6789)) {
		qDebug() << "Unable to start the server: " << server.errorString();
		exit(1);
	}
	qDebug() << "The server is running on IP: " <<  server.serverAddress() << " nport: " << server.serverPort();
    return a.exec();
}
