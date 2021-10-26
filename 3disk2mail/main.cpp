#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/param.h>
//#include <sys/stat.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <vector>
using namespace std;
using namespace boost;

string mailmsg;

string int2str(long long i) {
    stringstream ss;
    string temp;
    ss << i;
    ss >> temp;
    return temp;
}

void SendMail(const string email, const string msg) {
    FILE *mailer = popen(("/usr/bin/mail -a 'FROM:3disk2mail_at_BD24' -s '3DISK info at BD24' -a 'Content-Type: text/plain; charset=utf-8' -a 'Content-Transfer-Encoding: quoted-printable' " + email).c_str(), "w");
    if (mailer == NULL) {
	cout << "BLAD OTWARCIA POTOKU mailer" << endl;
	exit(66);
	}
    fprintf(mailer, msg.c_str(), 'root');
    pclose(mailer);
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

int CheckFreeSpace(const string dsc, const bool print = false) {
    disk d;
	int GB = 1024*1024*1024;
    DiskStats(dsc.c_str(),&d);
    mailmsg += "Dysk " + dsc + " rozmiar: " + int2str(d.size/GB) + "GB, zajęte: " + int2str(d.used/GB) + "GB, wolne:" + int2str(d.free/GB) + "GB\n";
    if (print) cout << dsc << "  " << d.free/GB << "GB wolnego" << endl;
    return 1;
}


int main(int argc, char *argv[]) {
    ifstream procfile;
    string procline, disk, mountpoint,fs;
    vector<string> proclist;

    proclist.clear();
    procfile.open("/proc/mounts");
    char chline[1024];
    while (1) {
        procfile.getline(chline,1024);
        procline.assign(chline);
        if (procline == "") break;
        split(proclist, procline, is_space(), token_compress_on);
        disk = proclist[0];
        mountpoint = proclist[1];
        fs = proclist[2];
        if ((fs == "ext3") || (fs == "xfs") || (fs == "ext4") || (fs == "ext2") || (fs == "nfs")) {
            cout << chline << endl;
            CheckFreeSpace(mountpoint,true);
        }
        proclist.clear();
    }

    cout << "KONIEC" << endl;
    if (mailmsg != "") SendMail("cezary.grabski@tvkslupsk.pl",mailmsg);
    exit(0);
}
