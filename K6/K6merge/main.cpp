#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>
#include <QProcess>

QStringList walk(QString dirName)
{
	QStringList mp4List;
	QDir srcDir = QDir (dirName);
	qDebug() << srcDir.dirName();
	srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	QFileInfoList listOfFiles = srcDir.entryInfoList();
	if (listOfFiles.isEmpty())
	{
		qDebug() << "PUSTY KATALOG" << srcDir.absolutePath() << listOfFiles.count();
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
				mp4List.append(walk(newSubDir));
			}
		}
	}
	return mp4List;
}

int main(int argc, char *argv[])
{
	QString temp = QDir::temp().absolutePath();
	QDir currDir = QDir::current();
	QStringList mp4Files = walk(QDir::currentPath());
	QString concat = "concat:";
	int i = 1;
	foreach( QString fileName, mp4Files)
	{
		QFileInfo fInfo = QFileInfo(fileName);
		QString command = QString("ffmpeg -i \"%1\" -vcodec copy -f mpegts \"%2.ts\" -acodec copy -y").arg(fInfo.absoluteFilePath(), temp + "/" + QString::number(i));
		qDebug() << command;
		QProcess::execute(command);
		concat.append(temp + "/" + QString::number(i)+".ts|");
		i++;
	}
	concat.left(concat.length()-1);
	QProcess::execute(QString("ffmpeg -i \"%1\" -vcodec copy -acodec copy \"%2.mpeg\" -y").arg(concat, currDir.absolutePath() + "/" + currDir.dirName()));
}
