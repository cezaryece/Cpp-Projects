#include "mainwindow.h"
#include "walker.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QCheckBox>
#include <QDebug>
#include <QDateTime>
#include <QStatusBar>
#include <QMessageBox>
#include <QProgressBar>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>

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
#ifndef Q_OS_UNIX
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1250"));
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1250"));
	ffmpegExec = "ffmpeg.exe";
#else
	QTextCodec::setCodecForLocale (QTextCodec::codecForName ("UTF-8"));
	//QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	ffmpegExec = "ffmpeg";
#endif
	setupUi(this);
#ifndef QT_DEBUG
	//updates
	//connection to database
	db = QSqlDatabase::addDatabase("QMYSQL");
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
	int mustBeUpdated = checkForUpdates();
	if (mustBeUpdated ==2)
	{
		QMessageBox::critical(this,QString::fromUtf8("Ważna aktualizacja jest niezbędna"),QString::fromUtf8("Wymagana jest wazna aktualizacja. Sprawdź skrzynke email lub skontaktuj się z Adinistratorem w celu aktualizacji programu!"), QMessageBox::Cancel);
		exit(0);
	}
	else if (mustBeUpdated==1)
	{
		int ret = QMessageBox::critical(this,QString::fromUtf8("Dostępna nowa wersja programu"),QString::fromUtf8("Dostępna jest nowa wersja programu. Sprawdź skrzynkę pocztową lub skontaktuj się z administratorem."), QMessageBox::Ignore, QMessageBox::Cancel);
		if (ret == QMessageBox::Cancel)
			exit(0);
	}
#endif
	polaczButton->setEnabled(false);
	currDir = QDir::fromNativeSeparators(QDir::homePath());
	
	plikiLista->setColumnCount(3);
	QStringList labels;
	labels << "Wybierz" << "Plik" << "Rozmiar";
	plikiLista->setHorizontalHeaderLabels(labels);
	allButton->setEnabled(false);
	noneButton->setEnabled(false);
	moveButton->setEnabled(false);
	plikLineEdit->setEnabled(false);
	startButton->setIcon(QIcon(":/images/media-playback-start.png"));
	startButton->setEnabled(false);
	currRow = 0;
	progressBar->reset();
	progressBar->setEnabled(false);
}

void MainWindow::on_wybierzButton_clicked()
{
	textBrowser->clear();
	polaczButton->setEnabled(false);
	plikLineEdit->setEnabled(false);
	mp4Files.clear();
	QString selDir = QFileDialog::getExistingDirectory(this,QString :: fromUtf8("Otwórz katalog BPAV"), currDir.absolutePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog);
	qDebug() << selDir;
	if (selDir != "")
	{
		currDir = QDir(selDir);
		updateCurrDir();
	}
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

void MainWindow::on_polaczButton_clicked()
{
	if (innyCheckBox->isChecked())
	{
		destDirName = innyLineEdit->text();
		QDir destDir = QDir(destDirName);
		if (!destDir.exists())
		{
			QMessageBox::warning(NULL, QString::fromUtf8("Błąd"), QString("Folder %1 nie istnieje").arg(destDirName), QMessageBox::Cancel);
			return;
		}
	}
	else
		destDirName = currDir.absolutePath();
	QApplication::setOverrideCursor(Qt::WaitCursor);
	wybierzButton->setEnabled(false);
	polaczButton->setEnabled(false);
	allButton->setEnabled(false);
	noneButton->setEnabled(false);
	moveButton->setEnabled(false);
	plikLineEdit->setEnabled(false);
	videoPlayer->stop();
	videoPlayer->load(Phonon::MediaSource());
	startButton->setEnabled(false);
	progressBar->setEnabled(true);
	
	QString concat = "concat:";
	QDir temp = QDir::temp();
	int i=1;
	
	QPair<QFileInfo,bool>  fileInfPair;
	foreach( fileInfPair, listaPlikow)
	{
		if (fileInfPair.second)
		{
			QFileInfo fInfo = fileInfPair.first;
			
			textBrowser->append(QString::number(i) + ". " + fInfo.fileName());
			qApp->processEvents();
			QProcess::execute(QString(ffmpegExec + " -i \"%1\" -vcodec copy -f mpegts \"%2.ts\" -acodec copy -y").arg(fInfo.absoluteFilePath(), temp.absolutePath() + "/" + QString::number(i)));
			concat.append(temp.absolutePath() + "/" + QString::number(i)+".ts|");
			i++;
		}
	}
	concat.left(concat.length()-1);
	textBrowser->append(QString::fromUtf8("Łączenie plików..."));
	qApp->processEvents();
	p = new QProcess( this );
	p->setEnvironment( QProcess::systemEnvironment() );
	p->setProcessChannelMode( QProcess::MergedChannels );
	connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
	connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
	connect(p, SIGNAL(finished(int)), this, SLOT(processExit(int)));
	
	QString cmdLine = QString(ffmpegExec + " -i \"%1\" -vcodec copy -acodec copy \"%2.mpeg\" -y").arg(concat, destDirName + "/" +plikLineEdit->text());
	p->start( cmdLine );
	
	textBrowser->append("Zrobione!!!");
}

void MainWindow::on_plikLineEdit_textChanged(const QString &name)
{
	if (!name.trimmed().isEmpty())
		polaczButton->setEnabled(true);
}

void MainWindow::endProcess(QString str)
{
	Q_ASSERT(p != NULL);
	disconnect(p, SIGNAL(finished(int)), this, SLOT(processExit(int)));
	p->kill();
	p->deleteLater();
	p = NULL;
	
	progressBar->reset();
	progressBar->setEnabled(false);
	textBrowser->append(str);
	
	znalezioneLabel->setText("Znalezione pliki");
	plikLineEdit->clear();
	plikLineEdit->setEnabled(true);
	wybierzButton->setEnabled(true);
	allButton->setEnabled(true);
	noneButton->setEnabled(true);
	moveButton->setEnabled(true);
	polaczButton->setEnabled(true);
	
	QApplication::restoreOverrideCursor();
}

void MainWindow::updatePlikiListWidget()
{
	QModelIndex curIdx = plikiLista->currentIndex();
	plikiLista->blockSignals(true);
	plikiLista->clearContents();
	plikiLista->blockSignals(false);
	if (!listaPlikow.isEmpty())
	{
		plikiLista->setRowCount(listaPlikow.count());
		int row = 0;
		QTableWidgetItem* item = NULL;
		selectedSize = 0;
		
		QPair<QFileInfo,bool> fileInfPair;
		foreach(fileInfPair, listaPlikow)
		{
			QCheckBox * selected = new QCheckBox();
			selected->setChecked(fileInfPair.second);
			connect(selected,SIGNAL(toggled(bool)),this, SLOT(plikToggle(bool)));
			selected->setProperty("row", row);
			selected->setText(QString::number(row +1).rightJustified(2,'0'));
			plikiLista->setCellWidget(row,0,selected);
			
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(fileInfPair.first.fileName());
			plikiLista->setItem(row,1,item);
			
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			qint64 size = fileInfPair.first.size();
			item->setText(QString::number(size/(1024*1024)) + "MB");
			if (fileInfPair.second)
				selectedSize += size;
			
			plikiLista->setItem(row,2,item);
			
			++row;
		}
		selectedLabel->setText("Wybrano: " + QString::number(selectedSize/(1024*1024)) + "MB");
		plikiLista->selectRow(currRow);
		plikiLista->scrollTo(curIdx,QAbstractItemView::PositionAtCenter);
	}
}

void MainWindow::updateCurrDir()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QMainWindow::statusBar()->showMessage(currDir.absolutePath());
	Walker w(currDir.absolutePath());
	mp4Files = w.walk();
	QMainWindow::statusBar()->showMessage(currDir.absolutePath());
	znalezioneLabel->setText("Znalezione pliki: " + QString::number(mp4Files.size()));
	listaPlikow.clear();
	plikiLista->clearContents();
	videoPlayer->stop();
	videoPlayer->load(Phonon::MediaSource());
	startButton->setEnabled(false);
	totalLabel->clear();
	selectedLabel->clear();
	
	if (!mp4Files.isEmpty())
	{
		qint64 totalSize = 0;
		int i=1;
		foreach(QString fileName, mp4Files)
		{
			QFileInfo fInfo = QFileInfo(fileName);
			listaPlikow.append(qMakePair(fInfo, true));
			totalSize += fInfo.size();
			i++;
		}
		updatePlikiListWidget();
		totalLabel->setText("Razem: " + QString::number(totalSize/(qint64)(1024*1024)) + "MB");
		plikLineEdit->setEnabled(true);
		plikLineEdit->setText(currDir.dirName());
		polaczButton->setEnabled(true);
		allButton->setEnabled(true);
		noneButton->setEnabled(true);
		moveButton->setEnabled(true);
		
	}
	currRow = 0;
	updatePlikiListWidget();
	QApplication::restoreOverrideCursor();
}

void MainWindow::plikToggle(bool selected)
{
	QCheckBox * sender = (QCheckBox *) QObject::sender();
	currRow = sender->property("row").toInt();
	listaPlikow.replace(currRow, qMakePair<QFileInfo,bool>(listaPlikow.at(currRow).first,selected));
	updatePlikiListWidget();
}

void MainWindow::ReadOut()
{
	QString log = p->readAllStandardOutput().simplified();
	if (log.isEmpty())
		return;
	
	textBrowser->append(log);
	
	if (!log.startsWith("frame="))
		return;
	int fsizePos = log.indexOf("size=") +6;
	int kbPos = log.indexOf("kB");
	QString doneNumber = log.mid(fsizePos,kbPos - fsizePos).simplified();
	int progress = doneNumber.toInt() *100 / (selectedSize/1024);
	progressBar->setValue(progress);
}
void MainWindow::ReadErr()
{
	textBrowser->append( p->readAllStandardError() );
}

void MainWindow::processExit(int res)
{
	if (res == 0)
		endProcess("\nZROBIONE!");
	else
		endProcess("\nPRZERWANE!\n" + QString::number(res));
}

void MainWindow::setVideo(QString fileName)
{
	videoPlayer->load(fileName);
	videoPlayer->play();
	startButton->setIcon(QIcon(":/images/media-playback-pause.png"));
	seekSlider->setMediaObject(videoPlayer->mediaObject());
	startButton->setEnabled(true);
}

void MainWindow::on_plikiLista_itemClicked(QTableWidgetItem *item)
{
	currRow = item->row();
	setVideo(listaPlikow.at(currRow).first.absoluteFilePath());
}

void MainWindow::on_startButton_clicked()
{
	if (videoPlayer->isPlaying())
	{
		startButton->setIcon(QIcon(":/images/media-playback-start.png"));
		videoPlayer->pause();
	}
	else
	{
		startButton->setIcon(QIcon(":/images/media-playback-pause.png"));
		videoPlayer->play();
	}
}

void MainWindow::on_allButton_clicked()
{
	for (int i=0; i < listaPlikow.count(); ++i)
	{
		if (!listaPlikow.at(i).second)
			listaPlikow.replace(i, qMakePair(listaPlikow.at(i).first, true));
	}
	updatePlikiListWidget();
}

void MainWindow::on_noneButton_clicked()
{
	for (int i=0; i < listaPlikow.count(); ++i)
	{
		if (listaPlikow.at(i).second)
			listaPlikow.replace(i, qMakePair(listaPlikow.at(i).first, false));
	}
	updatePlikiListWidget();
}

void MainWindow::on_moveButton_clicked()
{
	QString newDirName = QFileDialog::getExistingDirectory(this,QString :: fromUtf8("Otwórz katalog"), currDir.absolutePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!newDirName.isEmpty())
	{
		videoPlayer->stop();
		videoPlayer->load(Phonon::MediaSource());
		
		QApplication::setOverrideCursor(Qt::WaitCursor);
		for (int i=0; i < listaPlikow.count(); ++i)
		{
			if (listaPlikow.at(i).second)
			{
				QDir dir = QDir(listaPlikow.at(i).first.absoluteDir());
				QString oldDirName = dir.dirName();
				QMainWindow::statusBar()->showMessage("Przenoszenie " + oldDirName);
				dir.rename(dir.absolutePath(),newDirName + "/" + oldDirName);
			}
		}
		updateCurrDir();
		QApplication::restoreOverrideCursor();
	}
}

void MainWindow::on_innyCheckBox_toggled(bool checked)
{
	innyButton->setEnabled(checked);
	innyLineEdit->setEnabled(checked);
	if (checked)
	{
		if (innyLineEdit->text().trimmed().isEmpty())
			innyLineEdit->setText(currDir.absolutePath());
	}
}

void MainWindow::on_innyButton_clicked()
{
	innyLineEdit->setText(QFileDialog::getExistingDirectory(this,QString :: fromUtf8("Otwórz katalog"), innyLineEdit->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}
