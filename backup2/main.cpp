#include <QCoreApplication>
#include <QDebug>
#include <QTextCodec>
#include "config.h"
#include <clocale>
#include "mydatabase.h"
#include "tools.h"
#include "walker.h"

Config * configuration;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");
	QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	
	QString configFileName = QDir::homePath() + "/backup.conf";
	if (argc > 1)  {
		//podano plik konfiguracyjny
		configFileName = argv[1];
	}
	ConfigSet config(configFileName);
	qDebug() << "BAKUP config=" << configFileName;
	foreach(Config cfg, config.configsList())
	{
		configuration = &cfg;
		if (configuration->mDB != NULL)
			delete configuration->mDB;
		qDebug() << configuration->name;
		configuration->mDB = new MyDataBase(configuration->name);
		deleteFiles();
		if (configuration->debug)
			sleep(3);
		Walker w;
		w.walk();
	}
	qDebug() << "END OF APPLICATION";
}
