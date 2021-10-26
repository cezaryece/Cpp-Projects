#ifndef WALKER_H
#define WALKER_H

#include <QStringList>
#include <QDir>
#include "mainwindow.h"

class Walker
{
public:
	Walker(QString subdir="");
	QStringList walk();
private:
	QDir srcDir;
	QStringList mp4List;
};

#endif // WALKER_H
