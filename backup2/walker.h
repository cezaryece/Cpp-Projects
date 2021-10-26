#ifndef WALKER_H
#define WALKER_H

#include <QDate>
#include <QDir>
#include <QString>

class Walker
{
public:
	Walker(QString subdir="");
	void walk();
private:
	QDir srcDir, dstDir;
	void manageDeletedFiles();
};

#endif // WALKER_H
