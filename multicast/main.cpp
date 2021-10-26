#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
#include "glibmm/keyfile.h"
#include "glibmm.h"

#include <iostream>
#include <fstream>
#include <signal.h>

#include "init.h"
#include "demonize.h"
#include <unistd.h>


using namespace std;

bool Demon = true;  //czy ma byc uruchomiony jako demon

//################################
//wczytanie pliku konfiguracyjnego
void read_konfig(const string * kfile,Glib::KeyFile & config) {
    if (access(kfile->c_str(),F_OK) == 0) {
        try {
            if(!config.load_from_file(*kfile))
                std::cout << "Nie można wczytać pliku konfiguracyjnego!" << kfile->c_str() << std::endl;
           else cout << "//wczytanie pliku konfiguracyjnego" << endl;
        }
        catch (Glib::KeyFileError & e) {
            cout << "Caught KeyFileError" << std::endl;
        }
        catch (Glib::FileError & e) {
            cout << "Caught FileError" << std::endl;
        }
        catch (Glib::Error & e) {
            cout << "Caught Glib::Error" << std::endl;
        }

    }
    else {
        cout << "##################################################" << endl;
        cout << "nie ma pliku konfiguracyjnego - USTAWIENIA DMYŚLNE" << endl;
        cout << "##################################################" << endl;
        cout << endl;
        // nie ma pliku konfiguracyjnego... wiec wartości domyślne - eth1 i filtr pakietów ip tylko
        config.set_value("default","dev","eth0");
        config.set_value("default","proto","ip");
    }
}

ushort _SYGNAL = 0;

//funkcja do obsługi sygnałów międzyprocesowych
// ustawia globalną zmienną _SIGNAL na numer sygnału
void Sfunc(ushort sig) { _SYGNAL = sig; }

//###############################################
//        MAIN
//###############################################
// w wywołaniu może byc przekazana ściezka do pliku z konfiguracją (argv[1]), czyli np. "sniffer ~/mojsniffer.conf"
int main(int argc,char* argv[]) {
    string config_file;
    Glib::KeyFile konfig;
    list<string> grupy;
    time_t czas;
    struct tm *stime;
    typedef vector<Sniffer*> Vsn;   //utworzenie tablicy wskaźników do snifferów o wielkości równej ilosci konfigów
    Vsn sn;                         //vactor przechowujący sniffery
    typedef Vsn::iterator Iter;
    Iter it;                        //zmienna do petli for na vectorach

    if (Demon) {
        Daemonize("sniffer");
    }
    //########################
    //przekierowanie cout do pliku /var/log/sniffer.log
    std::streambuf* cout_sbuf = std::cout.rdbuf();; // save original sbuf
    std::ofstream   logfile("/var/log/sniffer.log");
    std::cout.rdbuf(logfile.rdbuf()); // redirect 'cout' to a 'fout'
    //########################
usleep(500000);
    cout << "############      SNIFFER START      #############" << endl;
    cout << endl;

    if(argc > 1)
        config_file = argv[1];
    else
        config_file = "/etc/sniffer/sniffer.conf";

    cout << "Plik konfiguracyjny:" << config_file << endl;

    //wczytanie pliku konfiguracyjnego
    read_konfig(&config_file,konfig);

    //########################
    //dla każdej grupy parametrów z pliku konfiguracyjnego należy uruchomic osobną instancję sniffera
    grupy=konfig.get_groups();      //odczytanie listy grup z pliku konfiguracyjnego

    cout << "##################################################" << endl;
    cout << grupy.size() << " - liczba wątków do uruchomienia" << endl;
    cout << "##################################################" << endl;
    cout << endl;

    cout << "//stworzenie snifferów" << endl;
    for (list<string>::iterator grupa=grupy.begin();grupa != grupy.end();grupa++)
        sn.push_back(new Sniffer(&konfig,(string) *grupa));

    cout << "##################################################" << endl;
    cout << "Wątki zostały uruchomione" << endl;
    cout << "##################################################" << endl;
    cout << endl;

    //ustawienie daty startu procesu
    time(&czas);  //odczytanie bieżącego czasu
    stime = localtime(&czas);
    ushort dzien,n_dzien,godzina,n_godzina;

    dzien = stime->tm_mday;  //dzień uruchomienia snifferów
    godzina = stime->tm_hour;

    bool stop = false;
    while (!stop) { //nieskończona pętla oczekująca na zakończenie programu lub zmianę daty
//cout << "WHILE START " << _SYGNAL << endl;
        //sprawdzenie czy minęła północ i czy trzeba zresetowac wątki do nowych plików
        time(&czas);  //odczytanie bieżącego czasu
        stime = localtime(&czas);
        n_dzien = stime->tm_mday;   //bierzący dzień
//cout << "dzien" << _SYGNAL << endl;
        if (n_dzien != dzien) {     //minęła północ - trzeba zrestartować watki aby zapisywały się do nowych plików
            cout << "######## DZIEŃ " << n_dzien << endl;
            for (ushort i=0; i < sn.size(); i++) {
                sn[i]->restart();
            }
        dzien = n_dzien;
        godzina = stime->tm_hour;  //aby nie robic podwójnego restartu
        }
//cout << "godzina" << _SYGNAL << endl;
        //nowe pliki co godzine
        n_godzina = stime->tm_hour;   //bierząca godzina
        if (n_godzina != godzina) {
            cout << "##### GODZINA " << n_godzina << endl;
            for (ushort i=0; i < sn.size(); i++) {
                sn[i]->restart();
            }
        godzina = n_godzina;
        }
        //sprawdzenie czy nie ma jakiegoś sygnału w _SIGNAL
        if (_SYGNAL > 0) {
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            cout << "otrzymałem sygnał " << _SYGNAL << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            for (it=sn.begin(); it !=sn.end();it++) {
                (*it)->sygnal(_SYGNAL);
            }

            switch(_SYGNAL){
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
                    exit(11);
                    break;
                case SIGUSR1: //sig=10  - sygnał przeczytania jeszcze raz pliku konfiguracyjnego
                    _SYGNAL = 0;

                    read_konfig(&config_file,konfig); //ponowne wczytanie pliku konfiguracyjnego, bo mogły nastąpic jakies zmiany
                    grupy=konfig.get_groups();  //odczytanie listy grup z pliku konfiguracyjnego

                    for (ushort i=0; i < sn.size(); i++) {
                        delete(sn[i]);  //zatrzymanie watków i skasowanie wszystkich obiektów Sniffera
                    }
                    sn.clear(); //wyczyszczenie sn
                    sleep(1);
                    for (list<string>::iterator grupa=grupy.begin();grupa != grupy.end();grupa++) {
                        sn.push_back(new Sniffer(&konfig,(string) *grupa));
                    }

                    cout << "SIGUSR1 END " << _SYGNAL << endl;
                    break;
            }
            if (_SYGNAL !=0) cout << "_SYGNAL END="<< _SYGNAL << endl;
            _SYGNAL = 0; //sygnał obsłużony, czekamy na następny
        }
        sleep(1);
//        cout << "WHILE END" << _SYGNAL << endl;
    } // koniec pętli WHILE

    for (ushort i=0; i < sn.size(); i++) {
        delete(sn[i]);  //skasowanie obiektu Sniffera
    }
    sn.clear(); //wyczyszczenie sn
    cout << "koniec MAIN" << endl;

    // ponowne ustawnienie cout na konsolę
    std::cout.rdbuf(cout_sbuf); // restore the original stream buffer
}
