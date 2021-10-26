#include "tools.h"
#include "config.h"
#include "mydatabase.h"
#include <sys/statvfs.h>

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QTime>

extern "C" Config * configuration;

void DiskStats(QString path, disk *dsk)
{
	struct statvfs st;
	unsigned long long int blksize, blocks, freeblks;
	if (statvfs (path.toStdString().c_str(), &st) == 0) {
		blksize = st.f_bsize;
		blocks = st.f_blocks;
		freeblks = st.f_bfree;
		dsk->size = blocks * blksize;
		dsk->free = freeblks * blksize;
		dsk->used = dsk->size - dsk->free;
	}
	else {
		qDebug() << "\nFATAL - statvfs error";
		perror ("statvfs");
		exit(6);
	}
}

int CheckFreeSpace(QString path, unsigned long long min, bool print)
{
	disk d;
	DiskStats(path,&d);
	if (print)
		qDebug() << path << "  " << d.free/GB << "GB free";
	if (d.free < min) {
		qDebug() << "\n ERROR - Mało miejsca na dysku " + path + "\n" + "Wolne: " + QString::number(d.free/GB) + "GB\n";
		return 0;
	}
	return 1;
}

int deleteFiles()
{
	QStringList files2Deletion = configuration->mDB->getFiles2DeleteList(configuration->keepDays);
	if (!configuration->verbose)
	{
		qDebug() << "   !!!!!!  KASOWANIE PLIKÓW - " << files2Deletion.count() <<"plików do skasowania";
		if (files2Deletion.count() > 0 && configuration->debug)
				sleep(3);
	}
	foreach (QString filePath, files2Deletion)
	{
		if (!configuration->verbose)
			qDebug() << "DEL" << filePath;
		QFileInfo entry = QFileInfo(filePath);
		if (entry.isDir())
			deleteDirTree(filePath);
		else
			QFile::remove(filePath);
	}
	configuration->mDB->deleteEntries(files2Deletion);
	if (!configuration->verbose)
		qDebug() <<"deleteFiles" << files2Deletion.size();
	return files2Deletion.size();
}

bool deleteDirTree(QString subDirPath)
{
	if (!configuration->verbose)
		qDebug() << "deleteDirTree" << subDirPath;

	QDir delDir = QDir(subDirPath);
	delDir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Writable);
	QFileInfoList listOfEntries = delDir.entryInfoList();
	foreach (QFileInfo fileInf, listOfEntries)
	{
		if (fileInf.isDir())
		{
			if (!deleteDirTree(fileInf.filePath()))
			{
				qDebug() << "Nieudane kasowanie katalogu" << fileInf.filePath();
				if (!configuration->debug)
					sleep(3);
				return false;
			}
		}
		else
			if (!QFile(fileInf.filePath()).remove())
			{
				qDebug() << "Nieudane kasowanie pliku" << fileInf.filePath();
				if (configuration->debug)
					sleep(3);
				return false;
			}
	}
	delDir.cdUp();
	delDir.rmpath(subDirPath);
	return !QDir(subDirPath).exists();
}

void sleep(int sec)
{
	QTime dieTime= QTime::currentTime().addSecs(sec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);  
}
