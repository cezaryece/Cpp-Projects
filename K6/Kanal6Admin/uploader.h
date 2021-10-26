#ifndef UPLOADER_H
#define UPLOADER_H
#include <QObject>
#include <QtNetwork>
#include <QDebug>
class Uploader: public QObject
{
	Q_OBJECT
public:
	Uploader(QObject *p = 0): QObject(p), reply(0), data(0)
	{
		connect(&nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
	}
	~Uploader() {}
	
	void start(const QString file, QString saveName, const QString urlStr)
	{
		
		data = new QFile(file, this);
		if (data != NULL)
		{
			if (saveName.isEmpty())
				saveName = QFileInfo(file).fileName();
			if (data->open(QIODevice::ReadOnly)) {
				QUrl url(urlStr + saveName);
				url.setUserName("kanal6");
				url.setPassword("k2n21b");
				url.setPort(21);
				emit sendLog("Creating reply", true);
				reply = nam.put(QNetworkRequest(url), data);
				connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(uploadProgress(qint64, qint64)));
				connect(reply, SIGNAL(finished()),this, SLOT(uploadDone()));
			}
			else
			{
				//data->deleteLater();
				emit sendLog(QString :: fromUtf8("Nie mogę otworzyć pliku ")+ file, false);
			}
		}
		else
			emit sendLog("NULL Oops "+ file, true);
	}
	
public slots:
	void requestFinished(QNetworkReply* netReply)
	{
		if (netReply->error())
			emit sendLog (netReply->errorString(), false);
		netReply->abort();
		netReply->deleteLater();
	}
	
	void uploadProgress(qint64 bytesSent, qint64 bytesTotal)
	{
		emit sendLog(QString :: fromUtf8("Wysłano ") + QString("%1").arg(bytesSent) + " z " + QString("%1").arg(bytesTotal), false);
	}
	
	void uploadDone()
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		emit uploadFinish(reply->error());
	}
signals:
	void sendLog(QString,bool);
	void uploadFinish(int);
private:
	QNetworkAccessManager nam;
	QNetworkReply *reply;
	QFile *data;
};
#endif // UPLOADER_H
