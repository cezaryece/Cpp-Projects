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
				reply = nam.put(QNetworkRequest(url), data);
				connect(reply, SIGNAL(finished()),this, SLOT(uploadDone()));
			}
			else
			{
				//data->deleteLater();
				qDebug() << "Nie mogę otworzyć pliku" << file;
			}
		}
		else
			qDebug() << "NULL Oops " << file;
	}
	
public slots:
	void requestFinished(QNetworkReply* netReply)
	{
		if (netReply->error())
			qDebug() << netReply->errorString();
		netReply->abort();
		netReply->deleteLater();
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
	void uploadFinish(int);
private:
	QNetworkAccessManager nam;
	QNetworkReply *reply;
	QFile *data;
};
#endif // UPLOADER_H
