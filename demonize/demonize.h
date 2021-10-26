#ifndef DEMONIZE_H
#define DEMONIZE_H

#include <string>

//tablica wskaźników do funkcji obsługujących sygnały
void (*SIG_func[31])(ushort);

static void signal_handler(int sig);
static void Daemonize(std::string);


#endif // DEMONIZE_H
