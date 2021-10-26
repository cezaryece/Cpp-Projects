#include "walker.h"
#include <QDir>
#include <QDebug>

Walker::Walker(QString subdir)
{
	srcDir = QDir(subdir);
	if (!srcDir.isReadable())
	{
		qDebug() << "KATALOG NIE DAJE SIĘ CZYTAĆ" << srcDir.absolutePath();
	}
	if (!srcDir.exists())
	{
		qDebug() << "\nFATAL - Katalog źródłowy " << srcDir.path() << " nie istnieje";
		exit(1);
	}
}

QStringList Walker::walk()
{
	srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Readable);
	QFileInfoList listOfFiles = srcDir.entryInfoList();
	QStringList listOfEntries = 	srcDir.entryList();
	if (listOfFiles.isEmpty() && listOfEntries.isEmpty())
	{
		qDebug() << "PUSTY KATALOG" << srcDir.absolutePath() << listOfFiles.count() << listOfEntries.count();;
	}
	else
	{
		foreach(QFileInfo srcInf, listOfFiles)
		{
			if (srcInf.isFile())
			{
				QFile srcFile(srcInf.absoluteFilePath());
				QFileInfo srcInfo = QFileInfo(srcFile);
				if (srcInfo.suffix().toLower() == "mp4")
				{
					mp4List.append(srcInfo.absoluteFilePath());
				}
			}
			else if (srcInf.isDir())
			{
				QString newSubDir = srcInf.absoluteFilePath();
				Walker newWalk(newSubDir);
				mp4List.append(newWalk.walk());
			}
		}
	}
	return mp4List;
}
