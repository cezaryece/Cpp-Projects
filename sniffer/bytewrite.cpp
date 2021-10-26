#include "bytewrite.h"
#include <QTextStream>

//funkcja zapisuje do strumienia znakowego liczby w postaci bajt po bajcie
void bytewrite (QTextStream &file,const uint dane, const ushort ile) {
    char temp[4]; //tablica znakowa do bajtowego zapisu liczb do strumienia
    memcpy(temp,&dane,4);
    for (ushort i=0; i < ile; i++)
        file << temp[i];
}
