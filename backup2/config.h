#ifndef CONFIG_H
#define CONFIG_H

#include <QDate>
#include <QFile>
#include <QString>

#include "mydatabase.h"

class Config
{
public:
	Config(QString configName = QString());
	~Config()
		{ if (mDB != NULL) delete mDB; }

	QString name;
	QString sourceDir, destinationDir, eMail, user, host;
	long long minFreeDiskSpace;
	bool print, verbose, logRename, debug, halt;
	int keepDays;
	MyDataBase * mDB;
	void clear();
};

class ConfigSet
{
public:
	ConfigSet(QString cfgFilePath);
	
	QList<Config> configsList();
	
private:
	QString configFilePath;
	void checkCfgFile();
};

const long long GB = 1024*1024*1024; //bajtów w 1 GB

struct disk {
	unsigned long long int size,free,used;
};

#endif // CONFIG_H
