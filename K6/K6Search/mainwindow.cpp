#include "mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QTextCodec>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
#ifndef Q_OS_UNIX
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1250"));
#else
    QTextCodec::setCodecForLocale (QTextCodec::codecForName ("UTF-8"));
#endif
	setupUi(this);
	//connection to database
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("kanal6.pl");
	db.setDatabaseName("tks");
	db.setUserName("K6Admin");
	db.setPassword("k2n21b");
	fdDB = QSqlDatabase::addDatabase("QMYSQL","filedup");
	fdDB.setHostName("192.168.0.250");
	fdDB.setDatabaseName("FileDup");
	fdDB.setUserName("root");
	fdDB.setPassword("x315OMEGA");
	if ( !( fdDB.open() && db.open() ))
	{
		bool ok = false;
		bool doexit = false;
		while (ok || doexit)
		{
			int ret = QMessageBox::critical(this,QString::fromUtf8("Błąd połączenia z bazą danych!!!"),QString::fromUtf8("Skontaktuj się z administratorem aby usunął problem..."), QMessageBox::Retry, QMessageBox::Cancel);
			if (ret == QMessageBox::Retry)
				ok = fdDB.open();
			else if (ret == QMessageBox::Cancel)
				doexit = true;
		}
		if (doexit)
			exit(0);
	}
	searchAll = true;
	allfilesRadio->setChecked(true);
	swords = anyWord;
	anyRadio->setChecked(true);
	escapeKeyPressed = false;
	videoFiles = false;
	audioFiles = false;
	fotoFiles = false;
	textFiles = false;
	searchDirs = false;
	customFiles = false;
	searchInTxt = true;
	extLineEdit->setEnabled(false);
}

void MainWindow::MainWindow::keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Escape)
		escapeKeyPressed = true;
	else if(e->key() == Qt::Key_Return && SzukajButton->isEnabled())
		on_SzukajButton_clicked();
}

void MainWindow::on_SzukajButton_clicked()
{
	escapeKeyPressed = false;
	SzukajButton->setEnabled(false);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	listWidget->clear();
	//compose query
	QString szukajStr = szukajLineEdit->text().trimmed();
	QString where;
	QStringList wordList = szukajStr.split(" ", QString::SkipEmptyParts);
	if (!wordList.isEmpty())
	{
		switch (swords) {
		case anyWord:
		{
			
			foreach(QString str, wordList)
				where += " OR name LIKE '%" +str + "%' ";
			where = where.remove(0,3);
			where = "WHERE (" + where +")";
			break;
		}
		case allWords:
		{
			QStringList wordList = szukajStr.split(" ", QString::SkipEmptyParts);
			foreach(QString str, wordList)
				where += " AND name LIKE '%" +str + "%' ";
			where = where.remove(0,4);
			where = "WHERE (" + where +")";
			break;
		}
		case exactSentence:
			where = "WHERE (name LIKE '%" + szukajStr + "%')";
			break;
		}
	}
	if (searchAll || searchDirs)
	{
		QString dirsSQL = QString("SELECT * FROM dirs %1 ORDER BY name ASC").arg(where);
		QStringList dirsResultList;
		QSqlQuery dirsQuery(fdDB);
		if (dirsQuery.exec(dirsSQL))
		{
			while (dirsQuery.next() && !escapeKeyPressed)
			{
				QString dirName = getDirName(dirsQuery.value(1).toLongLong());
				QString fileName = dirsQuery.value(3).toString();
				dirsResultList.append(QDir::toNativeSeparators(dirName) + fileName);
				QCoreApplication::processEvents();
			}
			if (!dirsResultList.isEmpty())
			{
				dirsResultList.sort();
				listWidget->addItem("************** KATALOGI ***************");
				listWidget->addItems(dirsResultList);
				listWidget->addItem("  ");
			}
		}
		else
			queryError("files names query", dirsQuery);
	}
	
	if (escapeKeyPressed)
	{
		QApplication::restoreOverrideCursor();
		escapeKeyPressed = false;
		SzukajButton->setEnabled(true);
		return;
	}
	if (!searchAll)
	{
		QString filesFilter;
		if (videoFiles)
            filesFilter += " OR RIGHT(name,4)='.avi' OR RIGHT(name,4)='.mp4' OR RIGHT(name,4)='.mod' OR RIGHT(name,4)='.mkv' OR RIGHT(name,4)='.mov' OR RIGHT(name,4)='.wmv' OR RIGHT(name,4)='.ogv' OR RIGHT(name,4)='.mpg' OR RIGHT(name,5)='.mpeg' OR RIGHT(name,4)='.mts'";
		if (audioFiles)
            filesFilter += " OR RIGHT(name,4)='.wav' OR RIGHT(name,4)='.mp3' OR RIGHT(name,4)='.wma' OR RIGHT(name,4)='.ogg'";
		if (textFiles)
			filesFilter += " OR RIGHT(name,4)='.txt' OR RIGHT(name,4)='.odt' OR RIGHT(name,4)='.doc' OR RIGHT(name,5)='.docx' OR RIGHT(name,4)='.rtf'";
		if (fotoFiles)
            filesFilter += " OR RIGHT(name,4)='.jpg' OR RIGHT(name,4)='.tif' OR RIGHT(name,4)='.bmp' OR RIGHT(name,4)='.png' OR RIGHT(name,4)='.pcx' OR RIGHT(name,4)='.tga'";
		if (customFiles)
		{
			foreach (QString fileExt, extLineEdit->text().trimmed().split(' '))
			{
				fileExt = fileExt.trimmed();
				if (!fileExt.startsWith('.'))
					fileExt.prepend('.');
				filesFilter += " OR RIGHT(name," + QString::number(fileExt.length()) + ")='"+ fileExt+"'";
			}
		}
		if (where.trimmed().isEmpty())
			where = filesFilter.replace(0,3,"WHERE");
		else if (!filesFilter.remove(0,4).isEmpty())
			where += " AND (" + filesFilter.remove(0,4) + ")";
	}
	QString filesSQL = QString("SELECT * FROM files %1 ORDER BY name ASC").arg(where);
	QStringList filesResultList;
	QSqlQuery filesQuery(fdDB);
	if (filesQuery.exec(filesSQL))
	{
		while (filesQuery.next() && !escapeKeyPressed)
		{
			QString dirName = getDirName(filesQuery.value(1).toLongLong());
			QString fileName = filesQuery.value(2).toString().toUtf8();
			filesResultList.append(QDir::toNativeSeparators(dirName) + fileName);
			QCoreApplication::processEvents();
		}
	}
	else
		queryError("files names query", filesQuery);
	if (!filesResultList.isEmpty())
	{
		filesResultList.sort();
		listWidget->addItem("************** PLIKI ***************");
		listWidget->addItems(filesResultList);
	}
	//szukanie w tekstach
	if (escapeKeyPressed)
	{
		QApplication::restoreOverrideCursor();
		escapeKeyPressed = false;
		SzukajButton->setEnabled(true);
		return;
	}
	if (searchInTxt)
	{
		QString against;
		switch (swords) {
		case anyWord:
			against = "('"+ wordList.join("* ") + "*' IN BOOLEAN MODE)";
			break;
		case allWords:
			against = "('+"+ wordList.join("* +") + "*' IN BOOLEAN MODE)";
			break;
		case exactSentence:
			against = "('+"+ wordList.join(" +") + "' IN BOOLEAN MODE)";
			break;
		}
		//newsy
		QString txtSQL = QString("SELECT id, tytul, DATE_FORMAT(DATE(data),'%Y-%m-%d') AS dzien, miasto, MATCH (impreza_nazwa,miasto,tytul,text,podpis,fotka_opis) AGAINST %1 AS score FROM K6_archiwum WHERE MATCH (impreza_nazwa,miasto,tytul,text,podpis,fotka_opis) AGAINST %1 ORDER BY score,data DESC").arg(against);
		QStringList txtResultList;
		QSqlQuery txtQuery(db);
		if (txtQuery.exec(txtSQL))
		{
			while (txtQuery.next() && !escapeKeyPressed)
			{
				txtResultList.append(txtQuery.value(2).toString() + " " + txtQuery.value(1).toString() + " ["+ txtQuery.value(3).toString() + "]");
				QCoreApplication::processEvents();
			}
		}
		else
			queryError("txt news query", txtQuery);
		if (!txtResultList.isEmpty())
		{
			listWidget->addItem("************** NEWSY ***************");
			listWidget->addItems(txtResultList);
		}
		if (escapeKeyPressed)
		{
			QApplication::restoreOverrideCursor();
			escapeKeyPressed = false;
			SzukajButton->setEnabled(true);
			return;
		}
		//programy
		txtSQL = QString("SELECT id, tytul, oryginal, MATCH (tytul, opis) AGAINST %1 AS score FROM video WHERE MATCH (tytul, opis) AGAINST %1 ORDER BY score DESC").arg(against);
		txtResultList.clear();
		txtQuery.clear();
		if (txtQuery.exec(txtSQL))
		{
			while (txtQuery.next() && !escapeKeyPressed)
			{
				txtResultList.append(txtQuery.value(1).toString() + " " + txtQuery.value(2).toString());
				QCoreApplication::processEvents();
			}
		}
		else
			queryError("txt progs query", txtQuery);
		if (!txtResultList.isEmpty())
		{
			listWidget->addItem("************** PROGRAMY ***************");
			listWidget->addItems(txtResultList);
		}
	}
	QApplication::restoreOverrideCursor();
	escapeKeyPressed = false;
	SzukajButton->setEnabled(true);
}

void MainWindow::on_anyRadio_toggled(bool checked)
{
	if (checked)
		swords = anyWord;
}

void MainWindow::on_allRadio_toggled(bool checked)
{
	if (checked)
		swords = allWords;
}

void MainWindow::on_exactRadio_toggled(bool checked)
{
	if (checked)
		swords = exactSentence;
}

void MainWindow::on_allfilesRadio_toggled(bool checked)
{
	searchAll = checked;
	if (checked)
	{
		videoCheckBox->setChecked(false);
		audioCheckBox->setChecked(false);
		textCheckBox->setChecked(false);
		fotoCheckBox->setChecked(false);
		customCheckBox->setChecked(false);
		extLineEdit->setEnabled(false);
	}
}

void MainWindow::on_videoCheckBox_clicked(bool checked)
{
	videoFiles = checked;
	searchAll = checkFilesFilter();
	allfilesRadio->setChecked(searchAll);
}

void MainWindow::on_audioCheckBox_clicked(bool checked)
{
	audioFiles = checked;
	searchAll = checkFilesFilter();
	allfilesRadio->setChecked(searchAll);
}

void MainWindow::on_textCheckBox_clicked(bool checked)
{
	textFiles = checked;
	searchAll = checkFilesFilter();
	allfilesRadio->setChecked(searchAll);
}

void MainWindow::on_fotoCheckBox_clicked(bool checked)
{
	fotoFiles = checked;
	searchAll = checkFilesFilter();
	allfilesRadio->setChecked(searchAll);
}

void MainWindow::on_dirCheckBox_clicked(bool checked)
{
	searchDirs = checked;
	searchAll = checkFilesFilter();
	allfilesRadio->setChecked(searchAll);
}

void MainWindow::on_customCheckBox_clicked(bool checked)
{
	customFiles = checked;
	extLineEdit->setEnabled(checked);
	searchAll = checkFilesFilter();
	allfilesRadio->setChecked(searchAll);
}

bool MainWindow::checkFilesFilter()
{
	return (!videoCheckBox->isChecked() && !audioCheckBox->isChecked() && !textCheckBox->isChecked() && !fotoCheckBox->isChecked() && !dirCheckBox->isChecked() && !customCheckBox->isChecked());
}

QString MainWindow::getDirName(long long dirID)
{
	QString dirName = "";
	QSqlQuery query( fdDB );
	while (true)
	{
		query.prepare("SELECT parentID, name FROM dirs WHERE id = :DIR LIMIT 1000");
		query.bindValue(":DIR",dirID);
		if (!query.exec())
			queryError("getDirName error select", query);
		if (!query.next())
			break;
		dirID = query.value(0).toLongLong();
		if (dirID == 0)
			break;
		else
			dirName = query.value(1).toString() + "/" + dirName;
	}
	return dirName;
}

void MainWindow::on_txtCheckBox_clicked(bool checked)
{
	searchInTxt = checked;
}

void MainWindow::queryError(QString where, QSqlQuery &query)
{
	qDebug() << "blad SQL " << where;
	qDebug() << query.lastQuery() << endl << query.lastError().databaseText() << " / " << query.lastError().driverText();
}


void MainWindow::on_allfilesRadio_clicked(bool checked)
{
	if (checked)
		allfilesRadio->setChecked(true);
}
