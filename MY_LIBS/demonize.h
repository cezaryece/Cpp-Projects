#ifndef DEMONIZE_H
#define DEMONIZE_H
#endif // DEMONIZE_H

#include <string>

//funckja obsługujaca sygnały wywoływana przez signal _handler
void Sfunc(ushort sig);  //definicja funkcji jest w main

void signal_handler(int sig);
void Daemonize(std::string);
