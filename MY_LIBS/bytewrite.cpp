#include "bytewrite.h"
#include <fstream>

//funkcja zapisuje do strumienia znakowego liczby w postaci bajt po bajcie
void bytewrite (std::ofstream &file,const int dane, const ushort ile) {
    char temp[4]; //tablica znakowa do bajtowego zapisu liczb do strumienia
    memcpy(temp,&dane,4);
    for (int i=0; i < ile; i++)
        file << temp[i];
}
