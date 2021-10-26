#ifndef IP_H
#define IP_H

#include <string>
#include <stdlib.h>

using namespace std;

class IP
{
public:
    IP();
	void clear();
	string toString(bool zeros = false);
	uint toUInt();
	bool fromString(string str);
	void fromUInt(uint Val);
private:
	unsigned char ipA, ipB, ipC, ipD;
};

uint IPstring2int(string str);
string IPint2string(uint Val);
#endif // IP_H
