#ifndef DEMONIZE_H
#define DEMONIZE_H

#include <string>

//funckja obsługujaca sygnały wywoływana przez signal _handler
void Sfunc(unsigned short sig);  //definicja funkcji jest w main

void signal_handler(int sig);
void Daemonize(std::string);

#endif // DEMONIZE_H
