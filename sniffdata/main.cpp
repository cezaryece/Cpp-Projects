#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdlib.h>
#include <dirent.h> //do obsługi katalogów na dysku
#include <time.h> //do obsługi funkcji czasowych
#include "str_replace.h"
#include <cstdio> //rename
#include <errno.h>

#include <arpa/inet.h>
#include <cstring>

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

const unsigned long long GB = 1024*1024;
const uint minFree = 6;
const string email = "czarek@tvkslupsk.pl";

struct __attribute__ ((__packed__)) dumppacket {
	unsigned short int  sekunda;
	unsigned char       proto;
	unsigned int        ip_s;
	unsigned short int  port_s;
	unsigned int        ip_d;
	unsigned short int  port_d;
};
struct __attribute__ ((__packed__)) datapacket {
	unsigned char       godzina;
	unsigned char       minuta;
	unsigned char       sekunda;
	unsigned char       proto;
	unsigned int        ip_s;
	unsigned short int  port_s;
	unsigned int        ip_d;
	unsigned short int  port_d;
};

//funkcja sortująca dla struktury dumppacket
bool d_sort (dumppacket a, dumppacket b) {
	if (a.proto < b.proto) return true;
	else if (a.proto == b.proto) {
		if (a.ip_s < b.ip_s) return true;
		else if (a.ip_s == b.ip_s) {
			if (a.ip_d < b.ip_d) return true;
			else if (a.ip_d == b.ip_d) {
				if (a.port_s < b.port_s) return true;
				else if (a.port_s == b.port_s)
					return (a.port_d < b.port_d);
			}
		}
	}
	return false;
}

//funkcja porównująca dla struktury dumppacket
bool d_uniq (dumppacket a, dumppacket b) {
	if (a.proto != b.proto) return false;
	else {
		if (a.ip_s != b.ip_s) return false;
		else {
			if (a.ip_d != b.ip_d) return false;
			else {
				if (a.port_s != b.port_s) return false;
				else
					return (a.port_d == b.port_d);
			}
		}
	}
}

void SendMail(const string email, const string msg) {
	FILE *mailer = popen(("/usr/bin/mail -a 'FROM:RUCH2_tvkslupsk.pl' -s 'UWAGA konczy sie miejsce na pakiety' -a 'Content-Type: text/plain; charset=utf-8' -a 'Content-Transfer-Encoding: quoted-printable' " + email).c_str(), "w");
	if (mailer == NULL)
	{
		cout << "BLAD OTWARCIA POTOKU mailer" << endl;
		exit(66);
	}
	fprintf(mailer, msg.c_str(), 'root');
	cout << "SendMail: " << msg << endl;
	pclose(mailer);
}

string int2str(long long i) {
	stringstream ss;
	string temp;
	ss << i;
	ss >> temp;
	return temp;
}

struct disk {
	unsigned long long int size,free,used;
};

int DiskStats(const char *path, disk *dsk) {
	struct statvfs st;
	unsigned long long int blksize, blocks, freeblks;
	if (statvfs (path, &st) == 0) {
		blksize = st.f_bsize;
		blocks = st.f_blocks;
		freeblks = st.f_bfree;
		dsk->size = blocks * blksize;
		dsk->free = freeblks * blksize;
		dsk->used = dsk->size - dsk->free;
	}
	else {
		/* Błąd */
		cout << "statvfs error" << endl;
		perror ("statvfs");
		exit(6);
	}
	return EXIT_SUCCESS;
}

unsigned long long dir_size(const char *path)
{
	DIR *d;
	struct dirent *de;
	struct stat buf;
	int exists;
	unsigned long long total_size =0;
	
	d = opendir(path);
	if (d == NULL) {
		perror("prsize");
		exit(1);
	}
	
	for (de = readdir(d); de != NULL; de = readdir(d)) {
		char sd_name[MAXPATHLEN];
		strcpy(sd_name, path);
		strcat(sd_name, "/");
		strcat(sd_name, de->d_name);
		exists = stat(sd_name, &buf);
		if (exists < 0) {
			cout << "Couldn't stat %s" << de->d_name << endl;
		} else {
			total_size += buf.st_size;
		}
	}
	closedir(d);
	return total_size;
}


void dump2data (ifstream * dumpfile, ostream * datafile, unsigned char godzina) {
	
	dumppacket * dp = new dumppacket;
	list<dumppacket> dplista; //lista zawierająca wczytane pakiety
	
	unsigned short int cursec;
	dumpfile->read((char*) &cursec,2); //odczytanie pierwszej sekundy pliku do zmiennej cursec
	dumpfile->seekg(0, ios::beg);
	
	datapacket * op = new datapacket;
	unsigned char proto;
	while (!(dumpfile->eof() | dumpfile->fail())) {
		dumpfile->read((char*)dp,15);
		
		if (dumpfile->gcount() == 0) { dumpfile->close(); break; };
		if (dumpfile->gcount() != 15) { cout << "plik ma dziwne zakończenie" << endl; dumpfile->close(); break; }
		
		//skopiowanie wczytanych danych do struktury dumppacket
		if (dp->sekunda != cursec) {
			//tu się odbywa obróbka danych wczytanej wczesniej sekundy i zapis do pliku dobowego
			dplista.sort(d_sort);  // sortowanie listy
			dplista.unique(d_uniq);//wyrzucenie duplikatów
			for (list<dumppacket>::iterator it=dplista.begin(); it!=dplista.end(); ++it) {
				op->godzina = godzina; //godziny
				op->minuta = ((dumppacket)*it).sekunda / 60; //minuty
				op->sekunda = ((dumppacket)*it).sekunda % 60; //sekundy
				proto = ((dumppacket)*it).proto;
				memcpy(&op->proto,&proto,13);
				datafile->write((char*)op,16);
			}
			cursec = dp->sekunda;
			dplista.clear();
		}
		dplista.push_back(*dp);
	}
	delete dp; delete op;
}

unsigned long long checkFree(string path)
{
	//ile zajmuja pliki z pakietami?
	unsigned long long dataLen = dir_size(path.c_str());
	//ile jest wolnego miejsca?
	disk d;
	string dsc = "/1T";
	DiskStats(dsc.c_str(),&d);
    if (d.free < 3*dataLen)
	{
		string msg = "Zaczyna brakowac miejsca na dysku z pakietami.\nZostalo " + int2str(d.free/(1024*1024*1024)) + "GB wolnego miejsca, co starczy na okolo " + int2str(d.free/dataLen) + " dni!";
		SendMail(email, msg);
	}
	return d.free;
}

//string checkFreeBacknet(string backnet1, string backnet2, unsigned long long &freeDirN)
//{
//	//sprawdzenie miejsca na dyskach sieciowych
//	DIR * dp0;
//	struct dirent * dir0;
//	struct stat f_stat;
	
//	string backnet = backnet1;
//	unsigned long long size = 0, fullsize = 0;
	
//	string filename, line;
//	ifstream file;
//	char chline[256];
	
//	cout << "checkFreeBacknet" << endl;
//	do 
//	{
//		size = 0;
//		filename = backnet + "sizefree";
//		file.open(filename.c_str());
//		if (file.is_open())
//		{
//			file.getline(chline,256);
//			file.close();
//			line.assign(chline);
//			int pos = line.find_first_of(" ");
//			fullsize = atoll(line.substr(0,pos).c_str());
//		}
//		else
//		{
//			SendMail(email,"Nie ma pliku sizefree na dysku sieciowym archiwum pakietów\n" + backnet1);
//			exit(1);
//		}
//		cout << backnet << endl << " fullsize " << fullsize << endl;
//		dp0 = opendir(backnet.c_str());
//		while ((dir0 = readdir(dp0)) != NULL) {
//			if (( (string) dir0->d_name != ".") && ( (string) dir0->d_name != "..") && (dir0->d_type != DT_DIR))
//			{
//				string f0name = backnet1 + dir0->d_name;
//				stat(f0name.c_str(),&f_stat);
//				size += (f_stat.st_size/1024);
//			}
//		}
//		freeDirN = fullsize - size;
//		cout << " size " << size << endl;
//		cout << " freeDirN " << freeDirN << endl;
//		if ( (uint) (freeDirN/GB) >=  minFree )
//		{
//			cout << "free: " << freeDirN << " = " << fullsize << "-" << size << ">" << minFree << endl;
//			cout << "backnet = " << backnet << endl;
//			return backnet;
//		}
//		else if (backnet == backnet2)
//		{
//			freeDirN = 0;
//			backnet = "";
//		}
//		else
//			backnet = backnet2;
//	} while (freeDirN > 0);
	
//	if (freeDirN == 0)
//		SendMail(email,"Nie ma miejsca na dyskach sieciowych archiwum pakietów");
//	return backnet;
//}

void remove_old(string datetime, string dir) {
	//kasowanie starych obrobionych już plików dziennych
	DIR * dp;
	struct dirent * dirp;
	cout << "REMOVE files with data: " << datetime << " in dir " << dir << endl;
	dp = opendir(dir.c_str());
	while ((dirp = readdir(dp)) != NULL) {
		if (string(dirp->d_name).substr(0,6) != datetime) continue;
		remove((dir + "/" + string(dirp->d_name)).c_str());
		cout << "removing:" << dir.c_str() << "/" << dirp->d_name << endl;
	}
}

void backupfiles(string datadir, string back, string backnet1, string backnet2)
{
	cout << "\nBACKUP ************************" << endl;
	cout << datadir << " " << back << " " << backnet1 << " " << backnet2 << endl;
	DIR * dp0;
	DIR * dpB;
	struct dirent * dir0;
	struct dirent * dirB;
	disk d;
	ifstream file;
	string filename, filename0;//, backnet = backnet1;
	unsigned long long freeDirB;//, freeDirN;
	
	//sprawdzenie miejsca na dyskach sieciowych
	//backnet = checkFreeBacknet(backnet1, backnet2, freeDirN);
	//cout << "backnet = " << backnet << endl;
	//skopiuj brakujące pliki z datadir do back i backnet
	//przy tym sprawdz miejsce na back i ewentualnie skasuj najstarszy plik
	cout << "datadir = " << datadir << endl;
	dp0 = opendir(datadir.c_str());
	if (dp0 == NULL)
	{
		cout << "opendir ERROR " << strerror(errno) << endl;
		exit(1);
	}
	
	list<string> pliki0;
	while ((dir0 = readdir(dp0)) != NULL) {
		if (( (string) dir0->d_name != ".") && ( (string) dir0->d_name != "..") && (dir0->d_type != DT_DIR))
			pliki0.push_back(dir0->d_name);
	}
	closedir(dp0);
	pliki0.sort();
	list<string>::iterator it;
	for (it=pliki0.begin(); it!=pliki0.end(); ++it) {
		filename0 = *it;
		cout << "plik: " << filename0 << endl;
		
		struct stat f_stat;
		string f0name = datadir + filename0;
		stat(f0name.c_str(),&f_stat);
		//sprawdzenie czy plik jest na back
		filename = back + filename0;
		file.open(filename.c_str());
		if (!file.is_open())
		{
			cout << " -> " << back << endl;
			//backup na back
			//sprawdzenie miejsca w archium lokalnym
			DiskStats(back.c_str(), &d);
			freeDirB = d.free;
			if ( (uint) (freeDirB/GB) <= minFree || freeDirB <= f_stat.st_size)
			{
				cout << "malo miejsca na back" << endl;
				//znajdz najstarszy plik i go skasuj
				dpB = opendir(back.c_str());
				list<string> pliki1;
				while ((dirB = readdir(dpB)) != NULL) {
					if (( (string) dirB->d_name != ".") && ( (string) dirB->d_name != "..") && (dirB->d_type != DT_DIR))
						pliki1.push_back(dirB->d_name);
				}
				closedir(dpB);
				pliki1.sort();
				string oldest = *pliki1.begin();
				cout << endl << "brak miejsca na back - kasownie pliku " << oldest << endl;
				//sprawdz czy najstarszy plik z back jest na backnet1 lub backnet2
				//				string fBname = backnet1 + oldest;
				//				file.open(fBname.c_str());
				//				if (!file.is_open())
				//				{
				//					fBname = backnet2 + oldest;
				//					file.open(fBname.c_str());
				//					if (!file.is_open())
				//					{
				//						//nie ma to go skopiuj
				//						fBname = backnet + oldest;
				//						ofstream(fBname.c_str()) << ifstream(filename.c_str()).rdbuf();
				//						file.open(fBname.c_str());
				//						if (!file.is_open())
				//						{
				//							SendMail("admin@tvkslupsk.pl","Blad kopiowania pliku " + oldest + " do archiwum sieciowego " + backnet);
				//							exit(1);
				//						}
				//						struct stat oldest_stat;
				//						stat(fBname.c_str(),&oldest_stat);
				//						freeDirN -= oldest_stat.st_size;
				//					}
				//				}
				//jest to skasuj go z back
				//				fBname = back + oldest;
				//remove(fBname.c_str());
//				cout << "remove oldest file" << fBname << endl;
			}
			//kopiuj plik na back
			ofstream(filename.c_str()) << ifstream(f0name.c_str()).rdbuf();
			file.open(filename.c_str());
			if (!file.is_open())
			{
				SendMail(email,"Blad kopiowania pliku " + (string) dir0->d_name + " do archiwum lokalnego " + back);
				exit(1);
			}
		}
		file.close();
		//		//sprawdzenie czy plik jest na backnet
		//		filename = backnet1 + filename0;
		//		file.open(filename.c_str());
		//		if (!file.is_open())
		//		{
		//			filename = backnet2 + filename0;
		//			file.open(filename.c_str());
		//			if (!file.is_open())
		//			{
		//				cout << " -> " << backnet << endl;
		//				//backup na backnet
		//				//sprawdzenie miejsca w archium sieciowym
		////				if ( (f_stat.st_size/1024) > freeDirN )
		////				{
		////					backnet = checkFreeBacknet(backnet1, backnet2, freeDirN);
		////					filename = backnet + filename0;
		////					file.open(filename.c_str());
		////					if (file.is_open())
		////					{
		////						file.close();
		////						continue;
		////					}
		////				}
		//				ofstream(filename.c_str()) << ifstream(f0name.c_str()).rdbuf();
		//				file.open(filename.c_str());
		//				if (!file.is_open())
		//				{
		//					SendMail(email,"Blad kopiowania pliku " + filename0 + " do archiwum sieciowego " + backnet);
		//					exit(1);
		//				}
		//				freeDirN -= f_stat.st_size/1024;
		//			}
		//		}
		//		file.close();
	}
}

int main(int argc, char *argv[]) {
	//odczytanie konfiguracji
	ifstream kfile;
	
	string config_file = "/etc/sniffer/default.conf";
	kfile.open(config_file.c_str());
	if (kfile.fail()) {
		cout << config_file.c_str() << " nie istnieje" << endl;
		exit(1);
	}
	string kline;
	char chline[256];
	string key, value, dev, protocol, path, backup, backupnet1, backupnet2;
	size_t pos;
	
	while (!kfile.eof()) {
		kfile.getline(chline,256);
		kline.assign(chline);
		if (kline.length()<3) continue;
		pos = kline.find_first_of("=");
		key = kline.substr(0,pos);
		value = string_replace("\"","",kline.substr(pos+1).c_str());
		if (key == "dev") dev = value;
		if (key == "protocol") protocol = value;
		if (key == "path") path = value;
		if (key == "backup") backup = value;
		if (key == "backupnet1") backupnet1 = value;
		if (key == "backupnet2") backupnet2 = value;
	}
	string dir = path + dev + "_"+ protocol;
	
	//najpierw sprawdzam czy juz jest zrobiony plik z poprzedniego dnia
	string datafilename, datadir;
	datadir = path + "dane/";
	
	char datetime[16],olddatetime[16];
	
	//jako paramter może byc podana data dla której robimy plik
	if (argc > 1)
	{
		strcpy(olddatetime,argv[1]);
		strcpy(datetime, argv[2]);
		cout << "data: " << olddatetime << " " << datetime << endl;
	}
	else
	{
		time_t czas;            // bieżący czas
		struct tm *timeinfo;    //struktura danych czasowych
		time(&czas);  //odczytanie bieżącego czasu
		czas = czas - (24*3600); //cofnięcie o jeden dzień
		timeinfo = localtime(&czas);
		strftime(datetime,11,"%Y-%m-%d",timeinfo);   //skopiowanie do zmienej datetime stringu z czasem "YYMMDD_hh-mm-ss"
		strftime(olddatetime,7,"%y%m%d",timeinfo);
	}
	
	datafilename = path + "dane/" + datetime;
	ifstream olddatafile;
	olddatafile.open((datafilename + ".END").c_str(),ios::in | ios::binary);
	if (olddatafile.is_open()) {
		olddatafile.close();
		checkFree(dir);
		//dane juz są przerobione, kasujemy ewentulanie pozostałe pliki danych
		//i robimy backup
		remove_old(string(olddatetime),dir);
		backupfiles(datadir, backup, backupnet1, backupnet2);
		exit(0);
	}
	ofstream datafile;
	datafile.open(datafilename.c_str(), ios::out | ios::binary | ios::trunc);
	if (datafile.fail()) { cout << "nie można otworzyć pliku wyjściowego "<< datafilename.c_str() << endl; exit(1); }
	
	DIR * dp;
	struct dirent * dirp;
	
	if((dp = opendir(dir.c_str())) == NULL) { cout << "Error opening " << dir << endl; exit(1); }
	ifstream dumpfile;
	string dumpfilename;
	unsigned char hour;
	list<string> pliki;
	list<string>::iterator it;
	
	while ((dirp = readdir(dp)) != NULL) {
		if (( (string) dirp->d_name != ".") && ( (string) dirp->d_name != ".."))
			pliki.push_back(dirp->d_name);
	}
	closedir(dp);
	
	pliki.sort();
	
	for (it=pliki.begin(); it!=pliki.end(); ++it) {
		dumpfilename = *it;
		if (dumpfilename.substr(0,6) != string(olddatetime)) continue;
		hour = (unsigned char) atoi(dumpfilename.substr(7,2).c_str());
		cout << dumpfilename.c_str() << " " << (short) hour << "|"<< endl;
		dumpfile.open((dir + "/" + dumpfilename).c_str(),ios_base::binary | ios_base::in);
		if (dumpfile.fail()) { cout << "nie można otworzyć pliku wejściowego "<< dumpfilename.c_str() << endl; exit(1); }
		dump2data(&dumpfile, &datafile, hour);
		dumpfile.close();
	}
	datafile.close();
	rename(datafilename.c_str(),(datafilename + ".END").c_str());
	checkFree(dir);
	remove_old(string(olddatetime), dir);
}
