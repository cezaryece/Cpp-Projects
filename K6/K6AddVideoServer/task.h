#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QMap>
#include "uploader.h"

class Task : public QObject
{
	Q_OBJECT
public:
	explicit Task(QObject *parent = 0);
private:
	int currID;
	void connectDB();
	bool mp4OK, ogvOK, webmOK;
	QMap<int,QString> getConvertMap();
	bool convertVideo(QString fileName, int id);
	void upload(int id);
public slots:
	void mp4Finished(int);
	void ogvFinished(int);
	void webmFinished(int);
	void run();
	void uploadFinished();
signals:
	void finished();
	void checkUploadFinished();
	void next();
};

#endif // TASK_H
