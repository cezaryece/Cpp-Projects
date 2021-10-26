#include "demonize.h"

#include <fcntl.h>
#include <signal.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


void signal_handler(int sig) {
//    std::cout << "sygnal_handler:"<<sig<<std::endl;
    Sfunc(sig);
//    if (sig==11) exit(1);
}

void Daemonize(std::string daemon_name)
{
        int i,lfp;
        char str[10];
        const char * LOCK_FILE = (daemon_name + ".lock").c_str();
//        const char * PID_FILE =  ("var/run/" + daemon_name + ".lock").c_str();

        if(getppid()==1) return; /* already a daemon */
        i=fork();
        if (i<0) exit(1); /* fork error */
        if (i>0) exit(0); /* parent exits */
        /* child (daemon) continues */
        setsid(); /* obtain a new process group */
        for (i=getdtablesize();i>=0;--i) close(i); /* close all descriptors */
        i=open("/dev/null",O_RDWR); dup(i); dup(i); /* handle standart I/O */
        umask(027); /* set newly created file permissions */
        chdir("/tmp"); /* change running directory */
        lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
        if (lfp<0) exit(1); /* can not open */
        if (lockf(lfp,F_TLOCK,0)<0) exit(0); /* can not lock */
        /* first instance continues */
        sprintf(str,"%d\n",getpid());
        write(lfp,str,strlen(str)); /* record pid to lockfile */
        //rejestracja wszystkich sygnałów do obsługi przez signal_handler
        for (int i=0; i<=31; i++)
            signal(i,signal_handler);
        // definicja numerów sygnałów jest w <bits/signum.h>
}
