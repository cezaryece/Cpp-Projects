#include "config.h"
#include "tools.h"
#include "walker.h"
#include "mydatabase.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>

extern "C" Config * configuration;

Walker::Walker(QString sub)
{
	if (!configuration->verbose)
		qDebug() << "@@@ Walker sub" << sub;
	srcDir = QDir(configuration->sourceDir + sub + QDir::separator());
	if (!srcDir.isReadable())
	{
		if (!configuration->verbose)
		{
			qDebug() << "KATALOG NIE DAJE SIĘ CZYTAĆ" << srcDir.absolutePath();
			if (configuration->debug)
				sleep(3);
		}
	}
	if (!srcDir.exists())
	{
		qDebug() << "\nFATAL - Katalog źródłowy " << srcDir.path() << " nie istnieje";
		exit(1);
	}
	
	dstDir = QDir(configuration->destinationDir + sub + QDir::separator());
	if (!dstDir.exists())
	{
		if (!configuration->verbose)
			qDebug() << "Katalog docelowy " << dstDir.path() << " nie istnieje";
		QString newDirPath = configuration->destinationDir + sub + QDir::separator();
		bool res = dstDir.mkdir(newDirPath);
		if (!res)
		{
			qDebug() << "\nERROR - Nie mogę utworzyc katalogu " << newDirPath;
			if (configuration->debug)
				sleep(3);
		}
	}
	else
		manageDeletedFiles();
}

void Walker::walk()
{
	if (!configuration->verbose)
		qDebug() << "START walk " << srcDir.path() << dstDir.path();
	srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Readable);
	QFileInfoList listOfFiles = srcDir.entryInfoList();
	QStringList listOfEntries = 	srcDir.entryList();
	if (listOfFiles.isEmpty() && listOfEntries.isEmpty())
	{
		if (!configuration->verbose)
		{
			qDebug() << "PUSTY KATALOG" << srcDir.absolutePath() << listOfFiles.count() << listOfEntries.count();;
			if (configuration->debug)
				sleep(3);
		}
	}
	else
	{
		bool isSpace = CheckFreeSpace(configuration->destinationDir, configuration->minFreeDiskSpace, configuration->print);
		
		foreach(QFileInfo srcInf, listOfFiles)
		{
			if (srcInf.isFile() && isSpace)
			{
				QFile srcFile(srcInf.absoluteFilePath());
				QFile dstFile(dstDir.path()+ QDir::separator() + srcInf.fileName());
				bool doCopy = false;
				if (!dstFile.exists())
					doCopy = true;
				else
				{
					if (srcFile.size() != dstFile.size())
						doCopy = true;
					else
					{
						QFileInfo srcInfo = QFileInfo(srcFile);
						QFileInfo dstInfo = QFileInfo(dstFile);
						if (srcInfo.lastModified() != dstInfo.lastModified())
							doCopy = true;
					}
				}
				if (doCopy)
				{
					QString copyStrCommand = QString("cp -pPf \"%1\" \"%2\"").arg(srcDir.path() + QDir::separator() + srcInf.fileName(), dstDir.path() + QDir::separator() + srcInf.fileName());
					if (!configuration->verbose)
						qDebug() << copyStrCommand;
					bool res = system(copyStrCommand.toStdString().c_str());
					if (res)
					{
						qDebug() << "\nERROR - BŁĄD KOPIOWANIA";
						qDebug() << QString(srcDir.path() + QDir::separator() + srcInf.fileName());
						if (configuration->debug)
							sleep(5);
					}
				}
			}
			else if (srcInf.isDir())
			{
				QString dirPath = srcInf.absoluteFilePath();
				QString newSub = dirPath.remove(0,configuration->sourceDir.length());
				if (newSub.isEmpty())
					continue;
				Walker newWalk(newSub);
				newWalk.walk();
			}
		}
	}
}

void Walker::manageDeletedFiles()
{
	dstDir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Writable);
	QFileInfoList listOfFiles = dstDir.entryInfoList();
	if (!configuration->verbose)
		qDebug() << "Sprawdzam pliki do skasowania z" << dstDir.absolutePath() << " DEADLINE:" << QDate::currentDate().addDays(-configuration->keepDays).toString() << listOfFiles.count();
	if (!listOfFiles.isEmpty())
	{
		foreach (QFileInfo fileInf, listOfFiles)
		{
			QString fileName = fileInf.fileName();
			if (!configuration->verbose)
				qDebug() << "manageDeletedFiles" << fileName;
			if (! QFileInfo(srcDir.path() + QDir::separator() + fileName).exists())
			{
				if (!configuration->verbose)
					qDebug() << "Brak" << srcDir.path() + QDir::separator() + fileName << fileInf.filePath();
				int res = configuration->mDB->checkFile(fileInf.filePath(), configuration->keepDays);
				if (!configuration->verbose)
				{
					switch (res)
					{
						case FILE_2DELETE:
							qDebug() << fileName << "do kasacji";
						break;
						case FILE_ADDED:
							qDebug() << fileName << "dodany do bazy";
						break;
						case FILE_NOCHANGE:
							qDebug() << fileName << "czeka na kasację";
						break;
						default:
							qDebug() << "\nERROR - Plik " << fileName << "Nieprawidłowy resultat z mDB->checkFile: " << res;
							if (configuration->debug)
								sleep(3);
							
					}
				}
			}
		}
	}
}
