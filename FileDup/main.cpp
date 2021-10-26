#include <QtGui/QApplication>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> //do obsługi katalogów na dysku
#include <time.h> //do obsługi funkcji czasowych

//#include <errno.h>
//#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
//#include <sstream>
//#include <vector>
//#include <stdio.h>  // for printf
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QList>
#include <QPair>


using namespace std;

string msg2email = "";
string EMail = "czarek@tvkslupsk.pl", Host;
const long long GB = 1024*1024*1024; //bajtów w 1 GB
const long long MB = 1024*1024; //bajtów w 1 MB
const long long KB = 1024; //bajtów w 1 kB
long long maxSize = -1, minSize = -1;
bool limitSize = false;
bool findEmpty = true, findDup = true, scan = true;

//QTextCodec *codec = QTextCodec::codecForName("Windows-1250");

string itoa(long long i) {
	string tmp; // brzydkie rozwiązanie
	sprintf((char*)tmp.c_str(), "*.*l%d", i);
	return tmp.c_str();
}
void SendMail(const string email, const string msg, const string Host) {
	FILE *mailer = popen(("/usr/bin/mail -a 'FROM:DUPLIKATY_" + Host + "' -s 'DUPLIKATY " + Host + "' -a 'Content-Type: text/plain; charset=utf-8' -a 'Content-Transfer-Encoding: quoted-printable' " + email).c_str(), "w");
	if (mailer == NULL) {
		cout << "BLAD OTWARCIA POTOKU mailer" << endl;
		exit(66);
	}
	fprintf(mailer, msg.c_str(), "root");
	pclose(mailer);
}

void queryError(string where, QSqlQuery &query, QSqlDatabase &db)
{
	cout << "blad SQL " << query.lastQuery().toStdString() << endl << query.lastError().databaseText().toStdString() << " / " << query.lastError().driverText().toStdString() << endl;
	cout << "KONIEC ("<< where << ")" << endl;
	db.close();
	exit(1);
}

QPair<long long, long long> walker(char * dpath, long long parentID, QSqlQuery &query, QSqlDatabase &db) {
	cout << dpath << endl;
	DIR *d;
	struct dirent *sdir;
	
	struct stat file_stat;
	char filepath[MAXPATHLEN];
	char newpath[MAXPATHLEN];
	
	d = opendir(dpath);
	if (d == NULL) {
		if( chdir(dpath) != 0 ) {
			cout << endl << "UWAGA, nie mogę otworzyć <" << dpath << ">" << endl;
			query.prepare( "UPDATE dirs SET error = 1 WHERE id = :ID");
			query.bindValue( ":ID", parentID );
			if (!query.exec())
				queryError("walker DIR error update", query, db);
			return QPair<long long, long long>(0,0);
		}
	}

	long long size = 0, size_r = 0, files = 0, files_r = 0;
	while(( sdir = readdir(d) )) {
		if (strcmp(sdir->d_name, ".") == 0) continue;   /* current dir */
		if (strcmp(sdir->d_name, "..") == 0) continue;  /* parent dir  */
		
		strcpy(filepath, dpath);
		strcat(filepath, "/");
		strcat(filepath, sdir->d_name);
		if ((sdir->d_type == DT_DIR)) {
			strcpy(newpath, dpath);
			strcat(newpath, "/");
			strcat(newpath, sdir->d_name);
			query.prepare( "INSERT INTO dirs (parentID, name) VALUES (:pId, :name) ");
			query.bindValue( ":pId", parentID );
			query.bindValue( ":name", sdir->d_name);
			if (!query.exec())
				queryError("walker DIRS error insert", query, db);
			QPair<long long, long long> result = walker(newpath, query.lastInsertId().toLongLong(), query, db);
			files_r += result.first;
			size_r += result.second;
			
		}
		else {
			if (strcmp(sdir->d_name, "Thumbs.db") == 0)
			{
				unlink(filepath);
				continue;
			}
			files++;
			stat(filepath, &file_stat);
			size += file_stat.st_size;
			query.prepare( "INSERT INTO files (dirID, name, size, date) VALUES ( :dirID, :name, :size, :date ) ");
			query.bindValue( ":dirID", parentID );
			query.bindValue( ":name", sdir->d_name);
			query.bindValue( ":size", (long long) file_stat.st_size );
			query.bindValue( ":date", (long long) file_stat.st_mtim.tv_sec );
			if (!query.exec())
				queryError("walker FILES error insert", query, db);
		}
	}
	closedir(d);
	query.prepare("UPDATE dirs SET files = :Files, files_r = :Files_r, size = :Size, size_r = :Size_r WHERE id = :ID");
	query.bindValue(":Files", files);
	query.bindValue(":Files_r", files_r);
	query.bindValue(":Size", size);
	query.bindValue(":Size_r",size_r);
	query.bindValue(":ID",parentID);
	if (!query.exec())
		queryError("walker end DIRS error update", query, db);
	
	return QPair<long long, long long>(files + files_r, size + size_r);
}

string getDirName(long long dirID, QSqlDatabase &db)
{
	string dirName = "";
	QSqlQuery query( db );
	while (true)
	{
		query.prepare("SELECT parentID, name FROM dirs WHERE id = :DIR");
		query.bindValue(":DIR",dirID);
		if (!query.exec())
			queryError("getDirName error select", query, db);
		if (!query.next())
			break;
		dirID = query.value(0).toLongLong();
		if (dirID == 0)
			break;
		else
			dirName = query.value(1).toString().toStdString() + "/" + dirName;
	}
	return dirName;
}

void findDuplicates (QSqlDatabase &db)
{
	cout << "Znajdowanie duplikatow" << endl;
	msg2email += "#################################\nDuplicaty plików\n\n";
	QSqlQuery query( db );
	QList<long long> skipID;
	skipID.empty();
	if (!query.exec("SELECT * FROM files ORDER BY id ASC"))
		queryError("finfDuplicates error select", query, db);
	while (query.next())
	{
		if (skipID.contains(query.value(0).toLongLong()))
			continue;
		
		if (limitSize)
		{
			if ((minSize > 0 && query.value(3).toLongLong() < minSize) ||
			(maxSize > 0 && query.value(3).toLongLong() > maxSize))
				continue;
		}
		
		cout << "F" << query.value(0).toLongLong() << endl;
		string dirName1 = getDirName(query.value(1).toLongLong(), db);
		string fileName = query.value(2).toString().toStdString();
		QSqlQuery query2( db );
		query2.prepare("SELECT * FROM files WHERE name = :NAME AND size = :SIZE AND id > :ID");
		query2.bindValue(":NAME", query.value(2).toString());
		query2.bindValue(":SIZE", query.value(3).toLongLong());
		query2.bindValue(":ID", query.value(0).toLongLong());
		if (!query2.exec())
			queryError("finfDuplicates error select", query, db);
		else if (query2.size() > 0)
		{
			string msgtemp = "";
			msgtemp += "\nPlik: " + fileName + " " + query.value(3).toString().toStdString() + "\n";
			msgtemp += dirName1 + "\n";
			while(query2.next())
			{
				skipID.append(query2.value(0).toLongLong());
				string dirName2 = getDirName(query2.value(1).toLongLong(), db);
				msgtemp += dirName2 + "\n";
			}
			cout << msgtemp << endl;
			msg2email += msgtemp;
		}
	}
}

void findDirDuplicates (QSqlDatabase &db)
{
	cout << "Znajdowanie duplikatow katalogów" << endl;
	msg2email += "#################################\nDuplicaty katalogów\n\n";
	QSqlQuery query( db );
	QList<long long> skipID;
	skipID.empty();
	if (!query.exec("SELECT * FROM dirs ORDER BY id ASC"))
		queryError("finfDuplicates error select1", query, db);
	while (query.next())
	{
		//skip empty dirs
		if (query.value(4).toLongLong() == 0 && query.value(5) == 0)
			continue;
		if (skipID.contains(query.value(0).toLongLong()))
			continue;
		if (skipID.contains(query.value(1).toLongLong()))
			continue;
		if (limitSize)
		{
			if ((minSize > 0 && query.value(6).toLongLong() < minSize) ||
			(maxSize > 0 && query.value(6).toLongLong() > maxSize))
				continue;
		}
		
		cout << "D" << query.value(0).toLongLong() << endl;
		string dirName1 = getDirName(query.value(0).toLongLong(), db);
		QSqlQuery query2( db );
		query2.prepare("SELECT * FROM dirs WHERE files = :FILES AND files_r = :FILES_R AND size = :SIZE AND size_r = :SIZE_R AND id > :ID");
		query2.bindValue(":SIZE", query.value(6).toLongLong());
		query2.bindValue(":SIZE_R", query.value(7).toLongLong());
		query2.bindValue(":FILES", query.value(4).toLongLong());
		query2.bindValue(":FILES_R", query.value(5).toLongLong());
		query2.bindValue(":ID", query.value(0).toLongLong());
		if (!query2.exec())
			queryError("finfDuplicates error select2", query, db);
		else if (query2.size() > 0)
		{
			string msgtemp = "";
			msgtemp += "\nKatalogi:\n";
			msgtemp += dirName1 + "\n";
			while(query2.next())
			{
				skipID.append(query2.value(0).toLongLong());
				if (skipID.contains(query.value(1).toLongLong()))
					continue;
				string dirName2 = getDirName(query2.value(0).toLongLong(), db);
				msgtemp += dirName2 + "\n";
			}
			cout << msgtemp << endl;
			msg2email += msgtemp;
		}
	}
}

void findEmptys (QSqlDatabase &db)
{
	cout << "Znajdowanie pustych plikow i katalogow" << endl;
	msg2email += "#################################\nPuste katalogi i pliki\n\n";
	string msgtemp = "";
	QSqlQuery query( db );
	if (!query.exec("SELECT * FROM files WHERE size=0"))
		queryError("finfEmptys FILES error select", query, db);
		if (query.size() > 0)
	{
		msgtemp = "\nPUSTE PLIKI\n";
		while (query.next())
		{
			cout << query.value(0).toLongLong() << endl;
			string dirName = getDirName(query.value(1).toLongLong(), db);
			string fileName = query.value(2).toString().toStdString();
			msgtemp += dirName + fileName + "\n";
		}
		cout << msgtemp;
		msg2email += msgtemp;
	}
	if (!query.exec("SELECT * FROM dirs WHERE size_r=0"))
		queryError("finfEmptys DIRS error select", query, db);
	else if (query.size() > 0)
	{
		msgtemp = "\nPUSTE KATALOGI\n";
		while (query.next())
		{
			cout << query.value(0).toLongLong() << endl;
			string dirName = getDirName(query.value(0).toLongLong(), db);
			msgtemp += dirName + "\n";
		}
		cout << msgtemp;
		msg2email += msgtemp;
	}
}

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	string config_file;
	ifstream kfile;
	
	if (argc > 1)  {
		//podano plik konfiguracyjny
		config_file = argv[1];
	}
	else {
		//standardowy plik plik konfiguracyjny
		config_file = "FD.conf";
	}
	cout << "config="<<config_file<<endl;
	
	kfile.open(config_file.c_str());
	if (kfile.fail()) {
		cout << config_file.c_str() << " nie istnieje" << endl;
		exit(4);
	}
	QString kline;
	char chline[256];
	QString key, value;
	size_t pos;
	
	char dirpath[MAXPATHLEN];
	QString dbHost = "tvkslupsk.pl";
	QString dbName = "FileDup";
	QString dbUser = "sd24";
	QString dbPass = "x315ALFA";
	
	while (!kfile.eof()) {
		kfile.getline(chline,256);
		kline.clear();
		kline.append(chline);
		if (kline.length()<1) continue;
		pos = kline.indexOf("=");
		if (pos != string::npos) {
			key = kline.left(pos);
			value = kline.right(kline.length() - (pos +1));
			cout << key.toStdString() << " " << value.toStdString() << endl;
			if (key == "dbHost") dbHost = value;
			if (key == "dbName") dbName = value;
			if (key == "dbUser") dbUser = value;
			if (key == "dbPass") dbPass = value;
			if (key == "dir") strcpy(dirpath,value.toStdString().c_str());
			if (key == "EMail") EMail = value.toStdString();
			if (key == "Host") Host = value.toStdString();
			if (key == "maxGB") maxSize = value.toLongLong() * GB;
			if (key == "minGB") minSize = value.toLongLong() * GB;
			if (key == "maxMB") maxSize = value.toLongLong() * MB;
			if (key == "minMB") minSize = value.toLongLong() * MB;
			if (key == "maxKB") maxSize = value.toLongLong() * KB;
			if (key == "minKB") minSize = value.toLongLong() * KB;
			if (key == "findEmpty") 
			{
				if (value.toCaseFolded() == "no")
					findEmpty = false;
			}
			if (key == "findDup") 
			{
				if (value.toCaseFolded() == "no")
					findDup = false;
			}
			if (key == "scan") 
			{
				if (value.toCaseFolded() == "no")
					scan = false;
			}
		}
	}
	
	if (minSize > 0 || maxSize > 0)
		limitSize = true;

	msg2email += "Znajdowanie duplikatow w katalogu " + (string) dirpath + "\n";
	cout << "Otwieranie połączenia z bazą" << endl;
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(dbHost);  // host
	db.setDatabaseName(dbName);            // database
	db.setUserName(dbUser);                // user
	db.setPassword(dbPass);               // password
	if (!db.open()) {
		cout << "blad otwarcia bazy " << db.lastError().databaseText().toStdString() << endl;
		exit(0);
	}
	QSqlQuery query( db );
//	query.exec("SET NAMES latin2");
//	query.exec("SET CHARACTER SET latin2");
	if (scan)
	{
		cout << "czyszczenie tabel" << endl;
		if (!query.exec("TRUNCATE `dirs`"))
		{
			cout << "DB problem truncate dirs" << endl;
			exit(1);
		}
		if (!query.exec("TRUNCATE `files`"))
		{
			cout << "DB problem truncate files" << endl;
			exit(1);
		}
		
		query.prepare( "INSERT INTO dirs (parentID, name) VALUES (0, :name) ");
		query.bindValue( ":name", dirpath );
		if (!query.exec())
			queryError("main DIRS error insert", query, db);
		QPair<long long, long long> result = walker(dirpath, query.lastInsertId().toLongLong(), query, db);
		cout << "BAZA WYPELNIONA!" << endl;
		query.exec("OPTIMIZE TABLE dirs , files");
		msg2email += "calkowity rozmiar plików" + itoa(result.second/GB) + " GB" + "\n";
	}
	if (findDup)
	{
		findDirDuplicates(db);
		findDuplicates(db);
	}
	if (findEmpty)
		findEmptys(db);
	SendMail(EMail, msg2email, "SD24");
	cout << "KONIEC (MAIN)" << endl;
	db.close();
}

