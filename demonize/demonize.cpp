#include "demonize.h"

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <syslog.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//wywołanie funkcji z tablicy wskaźników SIG_func
static void signal_handler(int sig) {
    (*SIG_func[sig])(sig);
}


static void Daemonize(std::string daemon_name)
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

//        signal(SIGCHLD,SIG_IGN); /* ignore child */
//        signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
//        signal(SIGTTOU,SIG_IGN);
//        signal(SIGTTIN,SIG_IGN);
//        signal(SIGHUP, signal_handler); /* catch hangup signal */
//        signal(SIGTERM, signal_handler); /* catch kill signal */
//        signal(SIGINT, signal_handler);
//        signal(SIGQUIT, signal_handler);

}
