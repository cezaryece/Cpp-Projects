#include "mydatabase.h"
#include "config.h"
#include "tools.h"

#include <QSqlQuery>
#include <QStringList>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QVariant>

extern "C" Config * configuration;

MyDataBase::MyDataBase(QString confname) : name(confname)
{
	DBtype = "QSQLITE";
	DBfile = QDir::home().path() + "/backup/backup."+ name + ".sqlite";
	
	db = QSqlDatabase::addDatabase(DBtype);
	db.setDatabaseName(DBfile);
	if (!db.open())
	{
		qDebug() << "\nFATAL - Problem otwarcia bazy danych " << DBtype << DBfile;
		qDebug() << lastError();
		exit(1);
	}
	checkDbSetup();
}

MyDataBase::~MyDataBase()
{
	db.close();
	QSqlDatabase::removeDatabase(db.connectionName());
}

int MyDataBase::checkFile(QString filePath, int keepDays)
{
	QSqlQuery query;
	if (isFileInDB(filePath))
	{
		if (!configuration->verbose)
			qDebug() << "Plik " << filePath << "jest w bazie";
		query.prepare("SELECT deldate FROM deletedfiles WHERE path=:filename");
		query.bindValue(":filename", filePath);
		if (query.exec() && query.next())
		{
			QString dateFromDB = query.value(0).toString();
			QDate deletionDate = QDate().fromString(dateFromDB, "yyyy-MM-dd");
			if (deletionDate.daysTo(QDate::currentDate()) >= keepDays)
				return FILE_2DELETE;
			else
				return FILE_NOCHANGE;
		}
	}
	else
	{
		if (!configuration->verbose)
			qDebug() << "Dodaję " << filePath << "do bazy";
		query.prepare("INSERT INTO deletedfiles (path, deldate) VALUES(:filename,date('now'))");
		query.bindValue(":filename", filePath);
		if (query.exec())
			return FILE_ADDED;
	}
	qDebug() << "\nERROR - Problem z bazą danych";
	qDebug() << lastError();
	qDebug() << query.lastQuery();
	if (configuration->debug)
		sleep(5);

	return -99;
}

QStringList MyDataBase::getAllFiles2DeletionList()
{
	QStringList resultList;
	QSqlQuery query;
	query.prepare("SELECT path FROM deletedfiles ORDER BY path");
	if (query.exec())
	{
		while (query.next())
			resultList.append(query.value(0).toString());
	}
	return resultList;
}

QStringList MyDataBase::getFiles2DeleteList(int daysBefore)
{
	QStringList resultList;
	QSqlQuery query;
	query.prepare(QString("SELECT path FROM deletedfiles WHERE date(deldate) <= date('now','-%1 days') ORDER BY path").arg(QString::number(daysBefore)));
	if (query.exec())
	{
		while (query.next())
			resultList << query.value(0).toString();
	}
	return resultList;
}

void MyDataBase::deleteEntries(QStringList fileList)
{
	QSqlQuery query;
	foreach(QString filePath, fileList)
	{
		query.prepare("DELETE FROM deletedfiles WHERE path=:filename");
		query.bindValue(":filename", filePath);
		if (!query.exec())
		{
			qDebug() << "\nERROR - Nie mogę skasować z bazy pliku " << filePath;
			qDebug() << query.lastError();
			qDebug() << query.lastQuery();
			if (configuration->debug)
				sleep(5);
		}
	}
}

bool MyDataBase::isFileInDB(QString filePath)
{
	QSqlQuery query;
	query.prepare(QString("SELECT * FROM deletedfiles WHERE path='%1'").arg(filePath));
	if (query.exec())
	{
		if (query.next())
			return true;
	}
	return false;
}

QSqlError MyDataBase::lastError()
{
	return db.lastError();
}

void MyDataBase::checkDbSetup()
{
	QSqlQuery query;
	query.prepare("CREATE TABLE IF NOT EXISTS deletedfiles (path TEXT, deldate TEXT)");
	if (!query.exec())
	{
		qDebug() << "\nFATAL -" << query.lastError();
		exit(1);
	}
	else if (!configuration->verbose)
		qDebug() << "SQL: Tabela deletedfiles gotowa do pracy";
}
