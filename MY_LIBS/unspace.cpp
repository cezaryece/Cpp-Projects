#include "unspace.h"
#include <string>

use namespace std;

//funkcja usuwa spacje z początku i z końca łancucha s
void unspace(string &s)
{
     while ( s.at(0) == " " ) s.erase(0, 1);
     while ( s.at(s.length()-1) ) == " ") s.erase(s.legth()-1, 1);
}
