#include "mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QTableWidget>
#include <QTableWidgetItem>

void queryError(QSqlQuery myQuery, QWidget* w) {
    QString bounded;
    QList<QVariant> list = myQuery.boundValues().values();
    for (int i = 0; i < list.size(); ++i)
        bounded.append(QString::number(i) + ": " + list.at(i).toString() + " ");
    QMessageBox::critical(w,QString::fromUtf8("Błąd operacji na bazie danych"), QString::fromUtf8("Niepowodzenie zapytania do bazy danych.\n") + myQuery.lastError().text() + "\n" + myQuery.lastQuery() + "\n" + bounded);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	
	db.setHostName("kanal6.pl");
	db.setDatabaseName("tks");
    db.setUserName("K6Admin");
	db.setPassword("k2n21b");
	
	if (!db.open())
	{
		bool ok = false;
        bool doexit = false;
        while (ok || doexit)
		{
			int ret = QMessageBox::critical(this,QString::fromUtf8("Błąd połączenia z bazą danych!!!"),QString::fromUtf8("Skontaktuj się z administratorem aby usunął problem..."), QMessageBox::Retry, QMessageBox::Cancel);
			if (ret == QMessageBox::Retry)
				ok = db.open();
			else if (ret == QMessageBox::Cancel)
                doexit = true;
		}
        if (doexit)
            exit(0);
	}
#ifndef QT_DEBUG
    //updates
    int mustBeUpdated = checkForUpdates();
    if (mustBeUpdated ==2)
    {
        QMessageBox::critical(this,QString::fromUtf8("Ważna aktualizacja jest niezbędna"),QString::fromUtf8("Wymagana jest ważna aktualizacja. Sprawdź skrzynke email lub skontaktuj się z Adinistratorem w celu aktualizacji programu!"), QMessageBox::Cancel);
        exit(0);
    }
    else if (mustBeUpdated==1)
    {
        int ret = QMessageBox::critical(this,QString::fromUtf8("Dostępna nowa wersja programu"),QString::fromUtf8("Dostępna jest nowa wersja programu. Sprawdź skrzynkę pocztową lub skontaktuj się z administratorem."), QMessageBox::Ignore, QMessageBox::Cancel);
        if (ret == QMessageBox::Cancel)
            exit(0);
    }
#endif
    lastDir = QDir::homePath();
	infoList->setColumnCount(4);
	infoList->setColumnHidden(0,true);
    infoList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	updateInfoList();
}

int MainWindow::checkForUpdates()
{
    //sprawdzenie wersji aplikacji
    QDate buildCompileDate = QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy"));
    QString buildDateTimeString = buildCompileDate.toString("yyyy-MM-dd") + " " + QString(__TIME__);
    QDateTime buildDateTime = QDateTime::fromString(buildDateTimeString, "yyyy-MM-dd hh:mm:ss");
    QString appName = QCoreApplication::applicationName();
    QSqlQuery myQuery("SELECT builddate,mustupdate FROM versions WHERE program='" + appName + "'");
    if (myQuery.exec())
    {
        QDateTime currBuildDateTime;
        if (myQuery.first())
        {
            currBuildDateTime = myQuery.value(0).toDateTime();
            if (buildDateTime < currBuildDateTime)
            {
                //trzeba zrobic update
                bool mustupdate = myQuery.value(1).toBool();
                if (mustupdate)
                    return 2;
                else
                    return 1;
            }
            else if (buildDateTime > currBuildDateTime)
            {
                //update builddate
                myQuery.prepare("UPDATE versions SET builddate=?,mustupdate=0 WHERE program=?");
                myQuery.addBindValue(buildDateTime.toString("yyyy-MM-dd hh:mm:ss"));
                myQuery.addBindValue(appName);
                if (!myQuery.exec())
                    queryError(myQuery, this);
            }
        }
        else
        {
            //insert program
            myQuery.prepare("INSERT INTO versions (program,builddate) VALUES(?,?)");
            myQuery.addBindValue(appName);
            myQuery.addBindValue(buildDateTime.toString("yyyy-MM-dd hh:mm:ss"));
            if (!myQuery.exec())
                queryError(myQuery, this);
        }
    }
    else
        queryError(myQuery, this);
    return 0;
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
		break;
		default:
		break;
	}
}

void MainWindow::updateInfoList()
{
	infoList->clearContents();
	QList<Info> infLista = getInfoFromDB();
	if (!infLista.isEmpty())
	{
		infoList->setRowCount(infLista.count());
		int row = 0;
		QTableWidgetItem* item = NULL;
		foreach(Info inf, infLista)
		{
			//id
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setData(Qt::UserRole, inf.id);
			infoList->setItem(row,0,item);
			
			//data
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(inf.data);
			infoList->setItem(row,1,item);
			
			//tytul
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(inf.tytul);
			infoList->setItem(row,2,item);
			
			//miasto
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(inf.miasto);
			infoList->setItem(row,3,item);
			
			++row;
		}
		infoList->resizeColumnsToContents();
	}
}

QList<Info> MainWindow::getInfoFromDB()
{
	QList<Info> infLista;
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT id, DATE(data), tytul, miasto FROM K6_archiwum WHERE film=0 AND avipath=\"\" ORDER BY DATE(data) DESC, miasto DESC"))
	{
		while (myQuery.next())
		{
			Info inf;
			inf.id = myQuery.value(0).toInt();
			inf.data = myQuery.value(1).toString();
			inf.tytul = myQuery.value(2).toString();
			inf.miasto = myQuery.value(3).toString();
			infLista.append(inf);
		}
	}
	else
        queryError(myQuery,this);
	
	return infLista;
}

void MainWindow::on_infoList_itemDoubleClicked(QTableWidgetItem *item)
{
	int row = item->row();
	int newsID = infoList->item(row,0)->data(Qt::UserRole).toInt();
    QString fileName = QFileDialog::getOpenFileName(this,QString :: fromUtf8("Otwórz plik VIDEO"), lastDir, "Pliki video (*.mp4 *.avi)");
	if (!fileName.isEmpty()) {
		lastDir = QFileInfo(fileName).absolutePath();
        QString sd24Path = QDir::toNativeSeparators(fileName);
        int pathStart = sd24Path.indexOf(QString(QDir::separator() + QString("DS_")));
        sd24Path.remove(0,pathStart);
        sd24Path.replace("\\","/");
		QSqlQuery myQuery;
		if (!myQuery.exec("UPDATE K6_archiwum SET avipath=\"" + sd24Path + "\" WHERE id="+ QString::number(newsID)))
            queryError(myQuery,this);
		updateInfoList();
	}
}
