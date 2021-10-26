#include <iostream>
#include <fstream>
#include <unistd.h>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QDateTime>

using namespace std;

int main(int argc,char* argv[])
{
	if (argc < 2)
	{
		cout << "Brak IP" << endl;
		exit(1);
	}
	//przekierowanie cout do pliku /var/log/sniffer.log
	streambuf* cout_sbuf = std::cout.rdbuf();; // save original sbuf
	QString logName = "/var/log/ping_monitor.log";
	if (argc > 3)
		logName = argv[3];
	ofstream logfile(logName.toStdString().c_str(), ios_base::app);
	cout.rdbuf(logfile.rdbuf()); // redirect 'cout' to a 'fout'
	
	QTcpSocket messenger;
	char * dest = argv[1];
	int port = 0;
	if (argc > 2)
		port = QString(argv[2]).toInt();
	if (port <= 0)
		port = 22789;
	
	cout << dest << ':' << port << endl;
	cout << "Start at " << QDateTime().currentDateTime().toString().toStdString() << endl << endl;
	int consecutiveTimeOuts = 0;
	do
	{
		messenger.connectToHost(dest, port, QIODevice::ReadOnly);
		if(!messenger.waitForConnected(1000))
		{
			if (consecutiveTimeOuts < 5)
				cout << dest << QDateTime().currentDateTime().toString().toStdString() << endl;
			consecutiveTimeOuts++;
			sleep(consecutiveTimeOuts/10);
		}
		else
		{
			if (consecutiveTimeOuts >=5)
				cout << consecutiveTimeOuts << " razy" << endl;
			consecutiveTimeOuts = 0;
			messenger.close();
		}
		sleep(1);
	} while (true);
	
	cout.rdbuf(cout_sbuf); // restore the original stream buffer
}

