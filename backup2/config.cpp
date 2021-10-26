#include "config.h"

#include <QDebug>
#include <QDir>
#include <QFile>

Config::Config(QString configName) : name(configName), minFreeDiskSpace(0), keepDays(0), mDB(0)
{
	clear();
}

void Config::clear()
{
	debug = false;
	destinationDir.clear();
	eMail = "admin@tvkslupsk.pl";
	halt = false;
	host.clear();
	keepDays = 14;
	logRename = false;
	mDB = NULL;
	minFreeDiskSpace = 1 * GB;
	print = false;
	sourceDir.clear();
	user = "root";
	verbose = true;
}


ConfigSet::ConfigSet(QString cfgFile) : configFilePath(cfgFile)
{
	checkCfgFile();
}

QList<Config> ConfigSet::configsList()
{
	QList<Config> resultList;
	Config currConfig;
	QFile configFile(configFilePath);
	if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "\nFATAL - Nie moge otworzyc pliku konfiguracyjnego" << configFilePath;
		exit(1);
	}
	while (!configFile.atEnd())
	{
		QString line = configFile.readLine().trimmed();
		if (line.isEmpty() || line.startsWith('#'))
			continue;
		
		if (line.startsWith('['))
		{
			if (!currConfig.name.isEmpty())
				resultList.append(currConfig);
			currConfig.clear();
			currConfig.name = line.mid(1,line.length() -2);
			continue;
		}
		
		int eqPos = line.indexOf("=");
		if (eqPos <= 0)
		{
			qDebug() << "\nERROR - Nierozpoznane ustawienie w pliku konfiguracyjnym";
			qDebug() << "Linia: " << line;
			continue;
		}
		QString key = line.left(eqPos).trimmed();
		if (key.isEmpty())
		{
			qDebug() << "\nERROR - Pusty klucz w linii " << line;
			continue;
		}
		QString value = line.right(line.length() - (eqPos +1)).trimmed();
		if (value.isEmpty())
		{
			qDebug() << "\nERROR - Pusta wartość w linii " << line;
			continue;
		}
		if (key == "Sdir") 
			currConfig.sourceDir = value;
		else if (key == "Ddir")
			currConfig.destinationDir = value;
		else if (key == "EMail")
			currConfig.eMail = value;
		else if (key == "User")
			currConfig.user = value;
		else if (key == "Host")
			currConfig.host = value;
		else if (key == "FreeGB")
			currConfig.minFreeDiskSpace = value.toInt() * GB;
		else if (key == "Keep")
			currConfig.keepDays = value.toInt();
		else if (key == "Print") {
			if (value == "1")
				currConfig.print = true;
			else currConfig.print = false;
		}
		else if (key == "Verbose") {
			if (value == "1")
				currConfig.verbose = true;
			else currConfig.verbose = false;
		}
		else if (key == "logRENAME") {
			if (value == "1")
				currConfig.logRename = true;
			else currConfig.logRename = false;
		}
		else if (key == "Debug") {
			if (value == "1")
				currConfig.debug = true;
			else currConfig.debug = false;
		}
		else if (key == "Halt") {
			if (value == "1")
				currConfig.halt = true;
			else currConfig.halt = false;
		}
		else
		{
			qDebug() << "\nERROR - Nierozpoznana opcja " << line;
			continue;
		}
	}
	
	if (!currConfig.name.isEmpty())
		resultList.append(currConfig);
	
	return resultList;
}

void ConfigSet::checkCfgFile()
{
	if (configFilePath.isEmpty())
	{
		configFilePath = QDir::currentPath() + "backup.conf";
		//		qDebug() << "Nazwa pliku konfiguracyjnego jest pusta";
		//		exit(1);
	}
	
	QFile configFile(configFilePath);
	if (!configFile.exists())
	{
		qDebug() << "\nFATAL - Plik konfiguracyjny " << configFilePath << " nie istnieje!";
		exit(1);
	}
	
	if (!configFile.open(QFile::ReadOnly))
	{
		qDebug() << "\nFATAL - Nie mozna otworzyć pliku konfiguracyjnego" << configFilePath;
		exit(1);
	}
}
