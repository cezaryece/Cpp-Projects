#include <QCoreApplication>
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QFile>
#include <QTextCodec>

void sleep(int sec)
{
	QTime dieTime= QTime::currentTime().addSecs(sec);
	while( QTime::currentTime() < dieTime )
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);  
}


void walk(QString srcDirName)
{
	qDebug() << "\nKATALOG" << srcDirName;
	QDir srcDir = QDir(srcDirName);
	
	if (!srcDir.isReadable())
	{
		qDebug() << "KATALOG NIE DAJE SIĘ CZYTAĆ" << srcDir.absolutePath();
		sleep(3);
	}
	if (!srcDir.exists())
	{
		qDebug() << "KATALOG NIE ISTNIEJE" << srcDir.absolutePath();
		sleep(3);
	}
	
	srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::Readable);
	QFileInfoList listOfFiles = srcDir.entryInfoList();
	if (!listOfFiles.isEmpty())
	{
		foreach(QFileInfo srcInfo, listOfFiles)
		{
			if (srcInfo.isFile())
			{
				QFile srcFile(srcInfo.absoluteFilePath());
				if (srcInfo.suffix().toLower() == "avi")
				{
                    QString aviBaseName = srcInfo.completeBaseName();
					QString aviFilePath = srcInfo.absoluteFilePath();
					QString aviAbsolutePath = srcInfo.absolutePath();
					QProcess::execute(QString("ffmpeg -i \"%1\" -vcodec msmpeg4v2 -acodec libmp3lame -b:v 10000k -ac 2 -b:a 256k -qmin 1 -vf scale=720:-1 \"%2.avi\" -y").arg(aviFilePath, aviAbsolutePath + "/" + aviBaseName + "_"));
					if (QFile::remove(aviFilePath))
					{
						QFile(aviAbsolutePath + "/" + aviBaseName + "_.avi").rename(aviAbsolutePath + "/" + aviBaseName + ".avi");
					}
					else
					{
						qDebug() << "NIE MOGĘ SKASOWAĆ PLIKU" << aviFilePath;
					}
				}
			}
			else if (srcInfo.isDir())
				walk(srcInfo.absoluteFilePath());
		}
	}
}


int main(int argc, char *argv[])
{
	if (argc != 2)  {
		qDebug() << "Jaki katalog???";
		exit(0);
	}
	
	setlocale(LC_ALL,"");
	QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	
	walk(argv[1]);
	qDebug() << "END OF APPLICATION";
}
