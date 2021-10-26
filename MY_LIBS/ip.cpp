#include "ip.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

IP::IP() : ipA(0), ipB(0), ipC(0), ipD(0)
{
}
void IP::clear()
{
	ipA = 0;
	ipB = 0;
	ipC = 0;
	ipD = 0;
}

string IP::toString(bool zeros)
{
	string flags;
	if (zeros)
		flags = "%03u";
	else
		flags = "%u";

	char buf[4];

	string str;

	sprintf(buf,flags.c_str(),ipA);
	str.append(buf);
	str.append(".");

	sprintf(buf,flags.c_str(),ipB);
	str.append(buf);
	str.append(".");

	sprintf(buf,flags.c_str(),ipC);
	str.append(buf);
	str.append(".");

	sprintf(buf,flags.c_str(),ipD);
	str.append(buf);
	return str;
}

uint IP::toUInt()
{
	uint Val = 0;
	*((unsigned char*) &Val) = ipA;
	*((unsigned char*) &Val + 1) = ipB;
	*((unsigned char*) &Val + 2) = ipC;
	*((unsigned char*) &Val + 3) = ipD;
	return Val;
}

bool IP::fromString(string str)
{
	bool OK = false;
	size_t pos1 = 0;
	size_t pos2 = str.find('.');
	string temp = str.substr(pos1,pos2-1);
	OK = (sscanf(temp.c_str(),"%c",&ipA) == temp.length());

	pos1 = pos2 + 1;
	pos2 = str.find('.',pos1);
	temp = str.substr(pos1,pos2-1);
	OK = (sscanf(temp.c_str(),"%c",&ipB) == temp.length());

	pos1 = pos2 + 1;
	pos2 = str.find('.',pos1);
	temp = str.substr(pos1,pos2-1);
	OK = (sscanf(temp.c_str(),"%c",&ipC) == temp.length());

	pos1 = pos2 + 1;
	pos2 = str.length();
	temp = str.substr(pos1,pos2-1);
	OK = (sscanf(temp.c_str(),"%c",&ipD) == temp.length());

	if (!OK) clear();
	return OK;
}

void IP::fromUInt(uint Val)
{
	ipA = *((unsigned char*) &Val);
	ipB = *((unsigned char*) &Val + 1);
	ipC = *((unsigned char*) &Val + 2);
	ipD = *((unsigned char*) &Val + 3);
}

uint IPstring2int(string str)
{
	if (str.empty()) return 0;
	IP address;
	address.fromString(str);
	return address.toUInt();
}

string IPint2string(uint Val)
{
	IP address;
	address.fromUInt(Val);
	return address.toString();
}
