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

#include <string.h>
#include <time.h>

using namespace std;

#define ALL_ATTS  (FA_DIREC | FA_ARCH)

extern int errno;

void walker(long long timeline, char* dpath, bool recursive=false) {
    cout << endl << "START worker " << dpath << endl;
    DIR *d;
    struct dirent *sdir;

    struct stat file_stat;
    char filepath[MAXPATHLEN];
    char newpath[MAXPATHLEN];

    d = opendir(dpath);
    if (d == NULL) {
        if( chdir(dpath) != 0 ) {
            cout << endl << "UWAGA, nie mogę otworzyć <" << dpath << ">" << endl;
            sleep(2);
            return;
        }
    }

    while(( sdir = readdir(d) )) {
        if (strcmp(sdir->d_name, ".") == 0) continue;   /* current dir */
        if (strcmp(sdir->d_name, "..") == 0) continue;  /* parent dir  */

        strcpy(filepath, dpath);
        strcat(filepath, "/");
        strcat(filepath, sdir->d_name);
        if ((sdir->d_type == DT_DIR) && recursive) {
            strcpy(newpath, dpath);
            strcat(newpath, "/");
            strcat(newpath, sdir->d_name);
            walker(timeline,newpath,recursive);
            chdir("..");
        }
        else {
            stat(filepath, &file_stat);
            if (file_stat.st_mtim.tv_sec < timeline) {
                if (remove(filepath) == 0)
                    cout << "DEL " << sdir->d_name << endl;
                else cout << "FAILED DEL " << filepath << endl;
            }
//            else cout << "NODEL " << sdir->d_name << endl;
        }
    }
//    cout << endl << "END worker " << spath << endl;
    closedir(d);
    return;
}



void usage() {
    cout << "Usage:" << endl;
    cout << "OldDel -{n=0..9}{[d|w|m|y]n} [dir]" << endl;
    cout << "-options" << endl;
//    cout << " R - recursive" << endl;
    cout << " d-days, w-weeks, m-months, y-years" << endl;
}

int main(int argc, char *argv[]) {
    string options;

    if (argc < 2) {
    //podano za mało argumentów
//        cout << "Za mało argumentów" << endl;
//        usage();
//        exit(1);
        options.assign("-2w");
    }
    else options.assign(argv[1]);
    if (options.at(0) != '-') {
        cout << "Opcje muszą się zacząć od znaku -" << endl;
        usage();
        exit(1);
    }

    bool recursive = false;
    int pos=1;
    if (options.at(pos)=='R') {
        recursive=true;
        pos++;
    }

    int num = atoi(&options.at(pos));
    cout << "num: " << num << endl;
    if (num <= 0) {
        cout << "Ilość okresów czasu musi być większa od 0" << endl;
        usage();
        exit(1);
    }
    pos++;
    long long timeline;
    switch (options.at(pos)) {
        case 'd': timeline = num * 24; break;
        case 'w': timeline = num * 7 * 24; break;
        case 'm': timeline = num * 30 * 24;break;
        case 'y': timeline = num * 365 * 24; break;
        default: cout << "Nierozpoznany okres czasu"<< endl;exit(1);break;
    }
    cout << "timeline: " << timeline << endl;
    time_t now;
    time(&now);
    timeline = now - (timeline *3600);

    char dir[MAXPATHLEN];
    if ((argc >2) && (!strcmp(argv[2],""))) {
        strcpy(dir, argv[2]);
    }
    else {
        getcwd(dir, MAXPATHLEN);
    }

    //rekurencyjne kasowanie plików
    walker(timeline, dir, recursive);
    exit(0);
}
