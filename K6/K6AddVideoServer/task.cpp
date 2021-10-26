#include "task.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QtNetwork>
#include <QProcess>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

Task::Task(QObject *parent) :
	QObject(parent)
{
}

void Task::connectDB()
{
	//connection to database
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	
	db.setHostName("kanal6.pl");
	db.setDatabaseName("tks");
	db.setUserName("K6Admin");
	db.setPassword("k2n21b");
	
	if (!db.open())
	{
		qDebug() << "Błąd połączenia z bazą danych";
		exit(0);
	}
	connect(this,SIGNAL(checkUploadFinished()), this, SLOT(uploadFinished()));
}

QMap<int,QString> Task::getConvertMap()
{
	QMap<int,QString> convMap;
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT id, avipath FROM K6_archiwum WHERE film=0 AND avipath!=''"))
	{
		while (myQuery.next())
			convMap.insert(myQuery.value(0).toInt(),myQuery.value(1).toString());
	}
	else
		qDebug() << "Błąd odczytu bazy danych" << myQuery.lastError().text() << myQuery.lastQuery();
	
	return convMap;
	
}

bool Task::convertVideo(QString fileName, int id)
{
	QString fname = QString::number(id);
	
	QString cmdLine;
	QProcess qp;
	QString fpath = QDir::currentPath() + QDir::separator() + "temp" + QDir::separator() + fname;
	cmdLine = "ffmpeg -i \"" + fileName +"\" -vcodec libx264 -preset slower -threads 4 -deinterlace -b:v 350k -bufsize 1835k -s 400x226 -aspect 16:9 -acodec libvo_aacenc -b:a 64k -y -f mp4 -r 16 \""+ fpath + ".mp4\"";
	qDebug() << "mp4";
	qp.start( cmdLine );
	qp.waitForFinished(-1);
	if (!QFileInfo(fpath+".mp4").exists())
	{
		qDebug() << "Error mp4";
		return false;
	}
	cmdLine = "ffmpeg2theora -v 7 -a 2 -o \"" + fpath +".ogv\" \"" + fpath + ".mp4\"";
	qDebug() << "ogv";
	qp.start( cmdLine );
	qp.waitForFinished(-1);
	if (!QFileInfo(fpath+".ogv").exists())
	{
		qDebug() << "Error ogv";
		return false;
	}
	cmdLine = "ffmpeg -i \"" + fpath + ".mp4\" -vcodec libvpx -preset slow -threads 4 -bufsize 1835k -b:v 350k -acodec libvorbis -y \""+ fpath + ".webm\"";
	qDebug() << "webm";
	qp.start( cmdLine );
	qp.waitForFinished(-1);
	if (!QFileInfo(fpath+".webm").exists())
	{
		qDebug() << "Error webm";
		return false;
	}
	
	return true;
}

void Task::upload(int id)
{
	QString saveName = QString::number(id);
	qDebug() << "WYSYLANIE" << id;
	QFtp *ftp = new QFtp ();
	ftp->connectToHost("176.97.80.125");
	ftp->login("kanal6", "k2n21b");
	ftp->cd("video/newsy");
	ftp->mkdir(saveName);
	while (ftp->hasPendingCommands())
		qApp->processEvents(QEventLoop::WaitForMoreEvents);
	ftp->close();
	while (ftp->hasPendingCommands())
		qApp->processEvents(QEventLoop::WaitForMoreEvents);
	
	QString file = QDir::currentPath() + QDir::separator() + "temp" + QDir::separator() + saveName;
	mp4OK = ogvOK = webmOK = false;
	Uploader * ump4 = new Uploader();
	connect(ump4, SIGNAL(uploadFinish(int)), this, SLOT(mp4Finished(int)) );
	ump4->start(file + ".mp4",QString::number(id) + ".mp4", "ftp://oferuje.pl/video/newsy/"+QString::number(id)+"/");
	Uploader * uogv = new Uploader();
	connect(uogv, SIGNAL(uploadFinish(int)), this, SLOT(ogvFinished(int)) );
	uogv->start(file + ".ogv",QString::number(id) + ".ogv", "ftp://oferuje.pl/video/newsy/"+QString::number(id)+"/");
	Uploader * uwebm = new Uploader();
	connect(uwebm, SIGNAL(uploadFinish(int)), this, SLOT(webmFinished(int)) );
	uwebm->start(file + ".webm",QString::number(id) + ".webm", "ftp://oferuje.pl/video/newsy/"+QString::number(id)+"/");
}

void Task::mp4Finished(int res)
{
	if (res==0)
	{
		mp4OK = true;
		emit checkUploadFinished();
	}
	else
	{
		qDebug() << "Błąd wysyłania mp4";
		emit finished();
	}
}

void Task::ogvFinished(int res)
{
	if (res==0)
	{
		ogvOK = true;
		emit checkUploadFinished();
	}
	else
	{
		qDebug() << "Błąd wysyłania ogv";
		emit finished();
	}
}

void Task::webmFinished(int res)
{
	if (res==0)
	{
		webmOK = true;
		emit checkUploadFinished();
	}
	else
	{
		qDebug() << "Błąd wysyłania webm";
		emit finished();
	}
}

void Task::run()
{
	connectDB();
	
	QMap<int,QString> convertMap = getConvertMap();
	if (convertMap.count() > 0)
	{
		foreach(currID, convertMap.keys())
		{
			qDebug() << currID;
			QString path = "/home/kanal6" + QDir::toNativeSeparators(convertMap.value(currID));
			if (!QFileInfo(path).exists())
			{
				qDebug() << "Błędna sciezka do pliku" << path;
				continue;
			}
			if (convertVideo(path,currID))
			{
				upload(currID);
				QEventLoop loop;
				QObject::connect(this, SIGNAL(next()), &loop, SLOT(quit()));
				QObject::connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
				loop.exec();
				if (currID != 0)
				{
					emit finished();
					return;
				}
			}
		}
	}
	else
		qDebug() << "Brak filmów do konwersji";
	emit finished();
}

void Task::uploadFinished()
{
	qDebug() << "checkUploadFinished" << mp4OK << ogvOK << webmOK;
	if (mp4OK && ogvOK && webmOK)
	{
		QSqlQuery myQuery;
		if (!myQuery.exec("UPDATE K6_archiwum SET film=1 WHERE id="+ QString::number(currID)))
			qDebug() << "Błąd zapisu do bazy danych" << myQuery.lastError().text() << myQuery.lastQuery();
		QString file = QDir::currentPath() + QDir::separator() + "temp" + QDir::separator() + QString::number(currID);
		QFile::remove(QFileInfo(file + ".mp4").absoluteFilePath());
		QFile::remove(QFileInfo(file + ".ogv").absoluteFilePath());
		QFile::remove(QFileInfo(file + ".webm").absoluteFilePath());
		currID = 0;
		emit next();
	}
}


