#include <stdlib.h>     //dla exit
#include <string>
#include <QSettings>
#include <QFile>

#include <iostream>
#include <fstream>
#include <signal.h>

#include "init.h"
#include "demonize.h"
#include "pckt_handler.h"

using namespace std;

bool Demon = true;  //czy ma byc uruchomiony jako demon
unsigned short _SYGNAL = 0;
unsigned short minuta;

//################################
//wczytanie pliku konfiguracyjnego
QSettings * read_konfig(const QString kfilename) {
	QFile kfile;
	QSettings * psettings;
	if (kfile.exists(kfilename)) {
		cout << kfilename.toStdString().c_str() << " istnieje" << endl;
		psettings = new QSettings (kfilename,QSettings::IniFormat);
	}
	else {
		cout << kfilename.toStdString().c_str() << " NIE istnieje" << endl;
		psettings = new QSettings;
		psettings->setValue("dev","eth0");
		psettings->setValue("protocol","ip");
		psettings->setValue("path","/1T/");
		psettings->setValue("human",1);
	}
	return psettings;
}

void * timer(void*) {  //wątek kontrolujący czas
	time_t czas;
	struct tm *stime;
	
	//ustawienie daty startu procesu
	time(&czas);  //odczytanie bieżącego czasu
	stime = localtime(&czas);
	
	//    ushort godzina,n_godzina;
	//    godzina = stime->tm_hour;
	//    godzina = stime->tm_min;
	while (1) { //nieskończona pętla oczekująca na zakończenie programu lub zmianę daty
		//nowe pliki co godzine
		time(&czas);  //odczytanie bieżącego czasu
		stime = localtime(&czas);
		//        n_godzina = stime->tm_hour;   //bierząca godzina
		//        n_godzina = stime->tm_min;   //bierząca godzina
		if ((stime->tm_min == 59) && (stime->tm_sec == 59)) //minuta 59 sekund 59
			minuta = 59;
		//        if (n_godzina != godzina) {
		//            _SYGNAL = 12;
		//            godzina = n_godzina;
		//            cout << "##### GODZINA " << godzina << endl;
		//        }
		pthread_testcancel();
		sleep(1);
	}
}

//funkcja do obsługi sygnałów międzyprocesowych
// ustawia globalną zmienną _SIGNAL na numer sygnału
void Sfunc(ushort sig) { _SYGNAL = sig; }

//###############################################
//        MAIN
//###############################################
// w wywołaniu może byc przekazana ściezka do pliku z konfiguracją (argv[1]), czyli np. "sniffer ~/mojsniffer.conf"
int main(int argc,char* argv[]) {
	pcap_pkthdr * header = NULL;
	const uchar * pkt_data = NULL;
	QSettings * settings = NULL;
	QString config_file;
	pthread_t timerthread;   //wątek zczytujacy pakiety
	int res;
	Sniffer * sn = NULL;
	if (Demon) {
		Daemonize("sniffer");
	}
	//########################
	//przekierowanie cout do pliku /var/log/sniffer.log
	streambuf* cout_sbuf = std::cout.rdbuf();; // save original sbuf
	ofstream   logfile("/var/log/sniffer.log");
	cout.rdbuf(logfile.rdbuf()); // redirect 'cout' to a 'fout'
	//########################
	
	cout << endl;
	cout << "############      SNIFFER START      #############" << endl;
	cout << endl;
	
	if(argc > 1) config_file = argv[1];
	else config_file = "/etc/sniffer/default.conf";
	
	cout << "Plik konfiguracyjny:" << config_file.toStdString() << endl;
	settings = read_konfig(config_file);
	//stworzenie sniffera
	sn = new Sniffer(settings);
	res = pthread_create(&timerthread, NULL, timer,NULL);
	if (res < 0) cout << "BŁĄD utworzenia wątku timera " << res << endl;
	else cout << " TIMER START " << endl;
	
	bool stop = false;
	bool human = settings->value("human").toBool();
	
	ulong old_ts;
	ushort old_sum;
	
	while ((res = pcap_next_ex(sn->fp, &header, &pkt_data) >= 0) && !stop) {
		
		// zmiana godziny... jeszcze minuta=59, ale juz sekunda=0 z kolejnej minuty
		if ((minuta == 59) && ((header->ts.tv_sec % 3600) < 3599)) {
			sn->restart();
			minuta = 0;
		}
		//zapisanie pakietu
		if(res == 1)
		{
			ipheader* ih=(struct ipheader*)(pkt_data+14);
			if ((ih->ip_sum == old_sum) && (old_ts == (ulong) header->ts.tv_usec))
				continue;
			old_sum = ih->ip_sum;
			old_ts = (ulong) header->ts.tv_usec;
			packethandler(sn->dumpfile, pkt_data, header->ts.tv_sec % 3600, human);  //funkcja obsługi odczytanych pakietów
		}
		else {
			cout << "RES = " << res << endl;
			stop = true;
			break;
		}
		if (stop) {
			cout << "WHILE break" << endl;
			break;
		}
		//sprawdzenie czy nie ma jakiegoś sygnału w _SIGNAL
		if (_SYGNAL > 0) {
			cout << "## otrzymałem sygnał " << _SYGNAL << endl;
			
			switch(_SYGNAL) {
			case SIGHUP:
			case SIGINT:
			case SIGQUIT:
			case SIGABRT:
			case SIGKILL:
			case SIGTERM:
				stop = true;
				break;
			case SIGSEGV:
				cout << "SIGSEGV" << endl;
				stop = true;
				pthread_cancel(timerthread);
				delete sn;
				exit(11);
				break;
			case SIGUSR1: //sig=10  - sygnał przeczytania jeszcze raz pliku konfiguracyjnego
				delete settings;
				settings = read_konfig(config_file); //ponowne wczytanie pliku konfiguracyjnego, bo mogły nastąpic jakies zmiany
				delete sn;  //skasowanie obiektu Sniffera
				sn = new Sniffer(settings);
				cout << "SIGUSR1 END " << _SYGNAL << endl;
				break;
			case SIGUSR2: //sig=12 RESTART
				sn->restart();
				break;
			}
			_SYGNAL = 0; //sygnał obsłużony, czekamy na następny
		}
		//        cout << "WHILE END " << endl;
	} // koniec pętli WHILE
	pthread_cancel(timerthread);
	delete sn;  //skasowanie obiektu Sniffera
	cout << "koniec MAIN" << endl;
	
	// ponowne ustawnienie cout na konsolę
	cout.rdbuf(cout_sbuf); // restore the original stream buffer
	delete settings;
}
