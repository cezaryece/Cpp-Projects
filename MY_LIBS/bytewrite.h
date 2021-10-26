#ifndef BYTEWRITE_H
#define BYTEWRITE_H

#include <ostream>

//funkcja zapisuje do strumienia znakowego liczby w postaci bajt po bajcie
void bytewrite (std::ofstream&,const int,const ushort=4);

#endif // BYTEWRITE_H
