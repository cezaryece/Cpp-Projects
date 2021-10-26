#ifndef QTIP_H
#define QTIP_H

#include <QString>

class IP
{
public:
    IP();
	void clear();
	QString toString(bool zeros = false);
	uint toUInt();
	bool fromString(QString string);
	void fromUInt(uint Val);
private:
	unsigned char ipA, ipB, ipC, ipD;
};

uint IPstring2int(QString str);
QString IPint2string(uint Val);
#endif // QTIP_H
