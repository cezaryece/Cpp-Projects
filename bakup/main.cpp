#include <cstdio>
//#include <stdlib.h>
#include <cstdlib>
#include <dirent.h>
#include <cerrno>

#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string.h>
#include "byteblock.h"
#include "../MY_LIBS/str_replace.h"

using namespace std;

#define ALL_ATTS  (FA_DIREC | FA_ARCH)

char Sdir[MAXPATHLEN], Ddir[MAXPATHLEN];
string EMail, User, Host;
long long GB = 1024*1024*1024; //bajtów w 1 GB
long long FreeMin;
bool Print = false, Verbose = false, logRENAME = false, Debug = false, Halt = false;

extern int errno;
string rootmsg = "";
char t[MAXPATHLEN];

string itoa(int i) {
	string tmp; // brzydkie rozwiązanie
	sprintf((char*)tmp.c_str(), "%d", i);
	return tmp.c_str();
}

void SendMail(const string email, const string msg, const string Host) {
	FILE *mailer = popen(("/usr/bin/mail -a 'FROM:BAKAP_at_" + Host + "' -s 'BAKAP info at " + Host + "' -a 'Content-Type: text/plain; charset=utf-8' -a 'Content-Transfer-Encoding: quoted-printable' " + email).c_str(), "w");
	if (mailer == NULL) {
		cout << "BLAD OTWARCIA POTOKU mailer" << endl;
		exit(66);
	}
	fprintf(mailer, msg.c_str(), "root");
	pclose(mailer);
}
char * valid(char* s) {
	strcpy(t,s);
	char token[3];
	strcpy(token,"\\"); strcat(token,"$"); str_replace("$",token,t);
	strcpy(token,"\\");	strcat(token,"~"); str_replace("~",token,t);
	strcpy(token,"\\");	strcat(token,"`"); str_replace("`",token,t);
//	str_replace("'","\'",t);
//	str_replace("?","\?",t);
//	str_replace("!","\!",t);
//	str_replace("@","\@",t);
//	str_replace("#","\#",t);
//	str_replace("%","\%",t);
//	str_replace("^","\^",t);
//	str_replace("&","\&",t);
//	str_replace(":","\:",t);
	if (Debug) cout << "valid " << t << endl;
	return t;
}

struct disk {
	unsigned long long int size,free,used;
};

int DiskStats(char *path, disk *dsk) {
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
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
int CheckFreeSpace(char *path, unsigned long long min, bool print = false) {
	disk d;
	DiskStats(path,&d);
	if (print) cout << (string) path << "  " << d.free/GB << "GB free" << endl;
	if (d.free < min) {
		rootmsg += "Mało miejsca na dysku " + (string) path + "\n" + "Wolne: " + itoa(d.free/GB).c_str() + "GB\n";
		return 0;
	}
	return 1;
}

int walker(const char *spath,const char *dpath) {
	if (Debug) cout << endl << "START worker " << spath << endl;
	
	DIR *d,*s;
	struct dirent *sdir;
	
	struct stat sdb_stat,sdc_stat;
	unsigned int  res;
	char temp_name[MAXPATHLEN];
	char sdb_name[MAXPATHLEN];
	char sdc_name[MAXPATHLEN];
	char newspath[MAXPATHLEN];
	char newdpath[MAXPATHLEN];
	char newname[MAXPATHLEN];
	char str[30+MAXPATHLEN*2];
	
	d = opendir(dpath);
	if (d == NULL) {
		if( chdir(dpath) != 0 ) {
			rootmsg += "UWAGA, nie mogę otworzyć dpath <" + (string) dpath + ">\n";
			if (!Verbose) {
				cout << endl << "UWAGA, nie mogę otworzyć dpath <" << dpath << ">" << endl;
				sleep(2);
			}
			return 1;
		}
	}
	else closedir(d);
	
	s = opendir(spath);
	if (s == NULL) {
		if (!Verbose) {
			cout << endl << "OPENDIR Error: " << strerror(errno) << endl;
			cout << "UWAGA, nie mogę otworzyć: " << spath << endl;
			sleep(2);
		}
		rootmsg += "OPENDIR Error: " + (string) strerror(errno) + "\n";
		rootmsg += "UWAGA, nie mogę otworzyć: " + (string) spath + "\n";
		return 1;
	}
	
	while(( sdir = readdir(s) )) {
		if (Debug) cout << "SDIR: " << sdir->d_name << endl;
		if (strcmp(sdir->d_name, ".") == 0) continue;   /* current dir */
		if (strcmp(sdir->d_name, "..") == 0) continue;  /* parent dir  */
		
		strcpy(temp_name, spath);
		strcat(temp_name, "/");
		strcat(temp_name, sdir->d_name);
		strcpy(sdb_name,temp_name);
		if (Debug) cout << "valid sdb_name: " << sdb_name << endl;

		strcpy(temp_name, dpath);
		strcat(temp_name, "/");
		strcat(temp_name, sdir->d_name);
		strcpy(sdc_name,temp_name);
		
		//        cout << sdb_name << "  " << sdc_name << endl;
		//        cout << "stat" << endl;
		stat(sdb_name,&sdb_stat);
		//        cout << "stat OK" << endl;
		
		//        cout << ".";
		if (sdir->d_type == DT_DIR || chdir(sdb_name) == 0) {
			if (Debug) cout << "***DIR " << sdir->d_name << endl;
			if( chdir(sdc_name) != 0 )  { //jesli nie ma takiego katalogu na /mnt/sdc
				//utworzenie nowego katalogu
				if (!Verbose) cout << " mkdir " << sdir->d_name << endl;
				if ((res = mkdir(sdc_name, 0777)) != 0) {
					//w przypadku błędu mail do roota
					rootmsg += "Error mkdir [" + (string)sdc_name + "]" + " " + strerror(res) +"\n";
					if (!Verbose) {
						cout << endl;
						cout << " ERROR!!!" << endl;
					}
					continue;
				}
				else {
					sprintf(str,"chown %u:%u \"%s\"",sdb_stat.st_uid,sdb_stat.st_gid, sdc_name);
					res = system(str);
					sprintf(str,"chmod a+w \"%s\"", sdc_name);
					res = system(str);
				}
			}
			strcpy(temp_name, spath);
			strcat(temp_name, "/");
			strcat(temp_name, sdir->d_name);
			strcpy(newspath,temp_name);
			strcpy(temp_name, dpath);
			strcat(temp_name, "/");
			strcat(temp_name, sdir->d_name);
			strcpy(newdpath,temp_name);
			//            chdir(sdir->d_name);
			int result = walker(newspath,newdpath);
			if ( result < 0) return result;
			//            chdir("..");
		}
		else {
			if (Debug) cout << "To jest plik: " << sdir->d_name << endl;
			//            if (strcmp(sdir->d_name,"sizefree")) continue; //pomijamy pliki z wielkością i wolnym miejscem na dyskach tworzone w cronie
			//znaleziono plik
			//czy taki plik jest na /mnt/sdc ?
			if (((stat(sdc_name, &sdc_stat) != 0) && (stat(sdc_name, &sdc_stat) != 0)) || (sdb_stat.st_size != sdc_stat.st_size) || (sdb_stat.st_mtim.tv_sec > sdb_stat.st_mtim.tv_sec)) {
				if (CheckFreeSpace(Ddir,sdb_stat.st_size)) {
					sprintf(str,"cp -pPf \"%s\" \"%s\"", sdb_name, sdc_name);
					if (!Verbose) cout << "COPY " << str << endl;
					res = system(str);
					if (res != 0) {
						if (!Verbose) {
							cout << endl << "BLAD KOPIOWANIA " << res << " " << str << endl;
							cout << sdir->d_type << "DT_REG - " << DT_REG << endl;
						}
						rootmsg += "BŁĄD KOPIOWANIA " + (string) str +"\n";
						exit(1);
						continue;
					}
					sprintf(str,"chmod a+w \"%s\"", sdc_name);
					res = system(str);
				}
				else {
					if (!Verbose) cout << " brak miejsca ERROR!!!" << endl;
					rootmsg += (string)"ERROR brak miejsca !!!" + "\n";
					closedir(s);
					return -1;
				}
			}
		}
	}
	if (Debug) cout << endl << "END worker " << spath << endl;
	closedir(s);
	return 0;
}

int main(int argc, char *argv[]) {
	string config_file;
	ifstream kfile;
	
	if (argc > 1)  {
		//podano plik konfiguracyjny
		config_file = argv[1];
	}
	else {
		//standardowy plik plik konfiguracyjny
		//etc/bakup/bakup.conf
		config_file = "/etc/bakup/default.conf";
	}
	cout << "BAKUP config="<<config_file<<endl;
	
	kfile.open(config_file.c_str());
	if (kfile.fail()) {
		if (!Verbose) cout << config_file.c_str() << " nie istnieje" << endl;
		exit(4);
	}
	string kline;
	char chline[256];
	string key, value;
	size_t pos;
	
	strcpy(Sdir,"");
	strcpy(Ddir,"");
	system("/root/diskfree");
	
	while (!kfile.eof()) {
		kfile.getline(chline,256);
		kline.assign(chline);
		if (kline.length()<1) continue;
		pos = kline.find_first_of("=");
		if (pos != string::npos) {
			key = kline.substr(0,pos);
			value = string_replace("\"","",kline.substr(pos+1).c_str());
			if (key == "Sdir") strcpy(Sdir,value.c_str());
			if (key == "Ddir") strcpy(Ddir,value.c_str());
			if (key == "EMail") EMail = value;
			if (key == "User") User = value;
			if (key == "Host") Host = value;
			if (key == "FreeGB") FreeMin = atoi(value.c_str()) * GB;
			if (key == "Print") {
				if (value == "1") Print = true;
			}
			if (key == "Verbose") {
				if (value == "1") Verbose = true;
			}
			if (key == "logRENAME") {
				if (value == "1") logRENAME = true;
			}
			if (key == "Debug") {
				if (value == "1") Debug = true;
			}
			if (key == "Halt") {
				if (value == "1") Halt = true;
			}
			
		}
		else {
			if (strcmp(Sdir,"") && strcmp(Ddir,"")) {
				if (!Verbose)
					cout << Sdir<<" -> "<<Ddir<<endl;
				//sprawdzenie wolnego miejsca na dyskach
				if (FreeMin == 0) FreeMin = 10 * GB;
				if (Debug) Verbose = false;
				CheckFreeSpace(Sdir,FreeMin,Print);
				CheckFreeSpace(Ddir,FreeMin,Print);
				//rekurencyjne kopiowanie plików
				if (EMail == "") EMail = "janusz@sml.pl";
				if (User == "") User = "root";
				int res = walker(Sdir,Ddir);
				if (res != 0) rootmsg += (string) "\nUWAGA!!!" + "\n" + "Wystąpiły błędy bakapu" + Sdir + " do "+ Ddir + "\n\n";
				strcpy(Sdir,"");
				strcpy(Ddir,"");
			}
		}
	}
	if (!Verbose)
		cout << endl << "KONIEC" << endl;
	if (rootmsg != "") SendMail(User, "BAKUP " + Host + "\n\n" +rootmsg, Host);
	system("/root/diskfree");
	if (Halt)
		system("halt");
	exit(0);
}
