#ifndef MYDATABASE_H
#define MYDATABASE_H
#include <QSqlDatabase>
#include <QSqlError>

const int FILE_ADDED = 0;
const int FILE_2DELETE = 1;
const int FILE_NOCHANGE = -1;

class MyDataBase
{
public:
	MyDataBase(QString name);
	~MyDataBase();
	int checkFile(QString filePath, int keepDays);
	QStringList getAllFiles2DeletionList();
	QStringList getFiles2DeleteList(int daysBefore);
	void deleteEntries(QStringList fileList);
	bool isFileInDB(QString filePath);
	QSqlError lastError();
	
private:
	QString DBtype;
	QString DBfile;
	void checkDbSetup();
	QSqlDatabase db;
	QString name;
};

#endif // MYDATABASE_H
