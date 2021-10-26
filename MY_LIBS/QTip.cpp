#include "QTip.h"
//#include <cstring>
//#include <stdio.h>
#include <QDebug>

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

QString IP::toString(bool zeros)
{
//	qDebug() << "IP::toString(bool zeros)";
	QString flags;
	if (zeros)
		flags = "%03u";
	else
		flags = "%u";

	char buf[4];

	QString str;

	sprintf(buf,flags.toStdString().c_str(),ipA);
	str.append(buf);
	str.append(".");

	sprintf(buf,flags.toStdString().c_str(),ipB);
	str.append(buf);
	str.append(".");

	sprintf(buf,flags.toStdString().c_str(),ipC);
	str.append(buf);
	str.append(".");

	sprintf(buf,flags.toStdString().c_str(),ipD);
	str.append(buf);
//qDebug() << "IP::toString(bool zeros) OK";
	return str;
}

uint IP::toUInt()
{
	uint Val = 0;
	*((uchar*) &Val) = ipA;
	*((uchar*) &Val + 1) = ipB;
	*((uchar*) &Val + 2) = ipC;
	*((uchar*) &Val + 3) = ipD;
//	qDebug() << "IP::toUInt" << Val;
	return Val;
}

bool IP::fromString(QString string)
{
//	qDebug() << "IP::fromString" << string;
	bool OK = false;
	ipA = string.section('.',0,0).toUShort(&OK);
	ipB = string.section('.',1,1).toUShort(&OK);
	ipC = string.section('.',2,2).toUShort(&OK);
	ipD = string.section('.',3,3).toUShort(&OK);
	if (!OK) clear();
//	qDebug() << "IP::fromString ABCD" << ipA << ipB << ipC << ipD;
	return OK;
}

void IP::fromUInt(uint Val)
{
	ipA = *((uchar*) &Val);
	ipB = *((uchar*) &Val + 1);
	ipC = *((uchar*) &Val + 2);
	ipD = *((uchar*) &Val + 3);
//	qDebug() << "IP::fromUInt ABCD" << ipA << ipB << ipC << ipD;
}

uint IPstring2int(QString str)
{
	if (str.isEmpty()) return 0;
//	qDebug() << "IPstring2int" << str;
	IP address;
	address.fromString(str);
	return address.toUInt();
}

QString IPint2string(uint Val)
{
//	qDebug() << "IPint2string(uint Val)" << Val;
	IP address;
	address.fromUInt(Val);
	return address.toString();
}
