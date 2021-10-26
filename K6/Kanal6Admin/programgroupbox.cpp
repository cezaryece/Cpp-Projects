#include "programgroupbox.h"
#include "fileutils.h"
#include <QAction>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFtp>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <Phonon/MediaSource>
#include <Phonon/MediaObject>
#include <Phonon/VideoWidget>

ProgramGroupBox::ProgramGroupBox(MainWindow *parent, Prog program) :
	GbBase(parent), currProg(program), stopKlatkaName(""), totalTime(0), m_charTable(NULL)
{
	setupUi(this);
	con = console;
	openAVI = openAviButton;
	convertAVI = convertButton;
	mp4L = MP4label; mw->mp4PBar = mp4ProgressBar;
	ogvL = OGVlabel; mw->ogvPBar = ogvProgressBar;
	webmL = WEBMlabel;mw->webmPBar = webmProgressBar;
	
	cykleCombo->addItem(QString(""),0);
	QSqlQuery cykleQuery;
	if (cykleQuery.exec("SELECT * FROM video_cykle ORDER BY tytul ASC"))
	{
		while (cykleQuery.next())
			cykleCombo->addItem(cykleQuery.value(1).toString(),cykleQuery.value(0).toInt());
	}
	else
		queryError(cykleQuery,this);
	cykleCombo->setCurrentIndex(0);
	cykleCombo->lineEdit()->setPlaceholderText(QString::fromUtf8("Wybierz lub wpisz tytuł nowego cyklu"));
	
	katButton->setMenu(mw->katMenu);
	QList<QAction*> actionsList = katButton->menu()->actions();
	foreach (QAction * action, actionsList)
		action->setChecked(false);
	
	if (currProg.id ==0)
	{
		nazwa_pliku->setText("Brak pliku");
		nazwa_pliku->setStyleSheet("QLabel { color: red; }");
		openAviButton->setStyleSheet("QPushButton { color: red; }");
		convertButton->setStyleSheet("QPushButton { color: red; }");
		tytulLabel->setStyleSheet("QLabel {color:red;}");
		stopklatkaBox->setStyleSheet("QGroupBox { color: red; }");
		
		convertButton->setEnabled(false);
		console->clear();
		daneGroup->setEnabled(false);
		mw->actionSave->setEnabled(false);
		videoGroupBox->setEnabled(false);
		mw->avi169 = true;
	}
	else
	{
		setTitle("Edycja programu");
		nazwa_pliku->setText(currProg.oryginal);
		if (QFileInfo(currProg.oryginal).exists())
			setVideo(currProg.oryginal);
		else
		{
			videoGroupBox->setEnabled(false);
			nazwa_pliku->setText("Nie znaleziono pliku: "+ currProg.oryginal);
			nazwa_pliku->setStyleSheet("QLabel { color: red; }");
		}
		tytulLineEdit->setText(currProg.tytul);
		opis->insertPlainText(currProg.opis);
		cykleCombo->setCurrentIndex(cykleCombo->findData(currProg.cyklID));
		currProg.cyklTytul = cykleCombo->currentText();
		//kategoriaID
		for (int i=0; i < currProg.katID.length(); ++i)
		{
			foreach (QAction * action, actionsList)
			{
				if (action->data().toString() == currProg.katID.at(i))
				{
					action->setChecked(true);
					break;
				}
			}
		}
		mw->avi169 = currProg.wide;
	}
	wideCheckBox->setChecked(mw->avi169);
	charTableButton->setChecked(false);
	katButton->setStyleSheet(currProg.katID.isEmpty() ? "QPushButton { color: red; }" : "QPushButton { color: black; }");
	foreach (QAction * action, actionsList)
		connect(action,SIGNAL(changed()),this, SLOT(menuChange()));
}

void ProgramGroupBox::setVideo(QString fileName)
{
	videoGroupBox->setEnabled(true);
	convertButton->setEnabled(true);
	mw->aviFileName = fileName;
	mw->aviConverted = false;
	videoPlayer->load(fileName);
	videoPlayer->play();
	videoPlayer->pause();
	seekSlider->setMediaObject(videoPlayer->mediaObject());
	startButton->setEnabled(true);
	stopklatkaButton->setEnabled(true);
	connect(videoPlayer->mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(totalTimeChanged()));
	connect(videoPlayer, SIGNAL(finished()), this, SLOT(restartVideo()));
}

void ProgramGroupBox::on_openAviButton_clicked()
{
	mw->resetProgress();
	QString dirStr = mw->lastDir;
	if (QFileInfo(currProg.oryginal).exists())
		dirStr = QFileInfo(currProg.oryginal).absolutePath();
	QString fileName = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,QString :: fromUtf8("Otwórz plik VIDEO"), dirStr, "Pliki VIDEO (*.avi *.mp4)"));
	if (!fileName.isEmpty()) {
		mw->aviTime = 0;
		mw->avi169 = fileName.endsWith(".mp4");
		wideCheckBox->setChecked(mw->avi169);
		mw->lastDir = QFileInfo(fileName).absolutePath();
		nazwa_pliku->setText(fileName);
		nazwa_pliku->setStyleSheet("QLabel { color: black; }");
		openAviButton->setStyleSheet("QPushButton { color: black; }");
		daneGroup->setEnabled(true);
		setVideo(fileName);
	}
}

void ProgramGroupBox::totalTimeChanged()
{
	bool seekable = videoPlayer->mediaObject()->isSeekable();
	if (mw->aviTime <= 0)
	{
		mw->aviTime = (double) videoPlayer->totalTime() / 1000.0;
		mw->aviFrames = (int) mw->aviTime * 16;
	}
	totalTime = (int) mw->aviTime;
	if (seekable)
	{
		totalTimeMin->setEnabled(true);
		totalTimeSec->setEnabled(true);
		totalTimeMin->display(totalTime/60);
		totalTimeSec->display(totalTime % 60);
	}
	else
	{
		totalTimeMin->setEnabled(false);
		totalTimeSec->setEnabled(false);
	}
}

void ProgramGroupBox::on_startButton_clicked()
{
	startButton->setEnabled(false);
	pauseButton->setEnabled(true);
	videoPlayer->play();
}

void ProgramGroupBox::on_pauseButton_clicked()
{
	videoPlayer->pause();
	pauseButton->setEnabled(false);
	startButton->setEnabled(true);
}

void ProgramGroupBox::on_stopklatkaButton_clicked()
{
	QString tempdir(mw->workingPath + QDir::separator() + "temp" + QDir::separator());
	if (!stopKlatkaName.isEmpty())
		FileUtils::removeFiles(tempdir, "jpg");
	
	int timeSec = videoPlayer->currentTime() / 1000;
	int currMin = timeSec / 60;
	int curSec = timeSec % 60;
	int mSec = videoPlayer->currentTime() - (timeSec * 1000);
	//    if (videoPlayer->currentTime() > 5)
	//        mSec += -5;
	//    else mSec = 0;
	QFileInfo fi(mw->aviFileName);
	QString fname = fi.baseName() + ".jpg";
	stopKlatkaName = tempdir + fname;
	QString deinterlace;
#ifndef Q_OS_UNIX
	deinterlace = "-filter:v yadif";
#else
	deinterlace = "-deinterlace";
#endif
	QString cmd = "ffmpeg -ss 0:"+ QString::number(currMin) + ":" + QString::number(curSec) + "." + QString::number(mSec) + " -i \"" + mw->aviFileName + "\" "+ deinterlace+" -vframes 1 -f image2 \"" + stopKlatkaName + "\"";
	QProcess shutter;
	shutter.start(cmd);
	shutter.waitForFinished(-1);
	if (QFileInfo(stopKlatkaName).exists())
	{
		stopKlatkaLabel->setPixmap(QPixmap(stopKlatkaName).scaledToWidth(90));
		stopklatkaBox->setStyleSheet("QGroupBox { color: black; }");
		stopklatkaBox->repaint();
		mw->actionSave->setEnabled(walidacja());
	}
	else
		qDebug() << "stopklatka nieistnieje" << stopKlatkaName;
}
void ProgramGroupBox::on_convertButton_clicked()
{
	if (converting)
		mw->breakConvertion();
	else
		mw->convertVideos();
	convertButton->setText(converting? QString::fromUtf8("Przerwij konwersję") : "Konwertuj video");
	openAviButton->setEnabled(!converting);
	mw->actionNewNews->setEnabled(!converting);
	mw->actionNewProgram->setEnabled(!converting);
	mw->actionNewList->setEnabled(!converting);
}

bool ProgramGroupBox::save()
{
	QSqlQuery myQuery;
	
	if (currProg.id == 0)
		myQuery.prepare("INSERT INTO video (tytul, opis, wide, cyklID, katId, czas, oryginal) VALUES (?, ?, ?, ?, ?, ?, ?)");
	else
		myQuery.prepare("UPDATE video SET tytul=?, opis=?, wide=?, cyklID=?, katId=?, czas=?, oryginal=? WHERE id=" + QString::number(currProg.id));
	
	currProg.tytul = tytulLineEdit->text().trimmed();
	currProg.opis = opis->toPlainText().trimmed();
	currProg.wide = wideCheckBox->isChecked();
	//zapisz cykle jeśli nowy
	int index = cykleCombo->currentIndex();
	if (index == 0)
	{
		if (!cykleCombo->currentText().trimmed().isEmpty())
		{
			QSqlQuery dodajCykl;
			dodajCykl.prepare("INSERT INTO video_cykle (tytul) values(?)");
			dodajCykl.addBindValue(cykleCombo->currentText().trimmed());
			if (dodajCykl.exec())
				currProg.cyklID = dodajCykl.lastInsertId().toInt();
			else
				queryError(dodajCykl,this);
		}
	}
	else
		currProg.cyklID = cykleCombo->itemData(index).toInt();
	
	//kategoriaID
	currProg.katID.clear();
	for (int i=0; i < katButton->menu()->actions().count(); ++i)
	{
		QAction * action = katButton->menu()->actions().at(i);
		if (action->isChecked())
			currProg.katID.append(action->data().toString());
	}
	
	if (mw->aviConverted)
	{
		QTime time = QTime(0,0).addSecs(totalTime);
		currProg.czas = time.toString("HH:mm:ss");
		currProg.oryginal = mw->aviFileName.right(512);
	}
	
	
	myQuery.addBindValue(currProg.tytul);
	myQuery.addBindValue(currProg.opis);
	myQuery.addBindValue(currProg.wide);
	if (currProg.cyklID)
		myQuery.addBindValue(currProg.cyklID);
	else
		myQuery.addBindValue(QVariant::Int);
	QString katIDStr = currProg.katID.join(":");
	myQuery.addBindValue(katIDStr.isEmpty() ? QVariant(QString("")) : katIDStr);
	myQuery.addBindValue(currProg.czas);
	myQuery.addBindValue(currProg.oryginal);
	
	bool saved = false;
	if (myQuery.exec())
	{
		saved = true;
		if (currProg.id == 0)
			currProg.id = mw->recordID = myQuery.lastInsertId().toInt();
		else
			mw->recordID = currProg.id;
	}
	else
		queryError(myQuery,this);
	
	if (saved)
	{
		if (mw->aviConverted || !stopKlatkaName.isEmpty())
		{
			mw->actionSave->setEnabled(false);
			QFtp *ftp = new QFtp ();
			ftp->connectToHost("oferuje.pl");
			ftp->login("kanal6", "k2n21b");
			ftp->cd("video/programy");
			ftp->mkdir(QString::number(mw->recordID));
			ftp->close();
			while (ftp->hasPendingCommands())
				qApp->processEvents(QEventLoop::WaitForMoreEvents);
			QString ext;
			if (!stopKlatkaName.isEmpty())
			{
				mw->fileName = stopKlatkaName;
				ext = ".jpg";
			}
			else if (mw->aviConverted)
			{
				ext = ".mp4";
				mw->fileName = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + QFileInfo(mw->aviFileName).baseName() + ext;
			}
			console->append(QString :: fromUtf8("\nWysyłanie pliku %1 na serwer.\n").arg(mw->fileName));
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ext, mw->programyURL + QString::number(mw->recordID) + "/");
			return true;
		}
		else
			emit finished();
	}
	mw->actionNewNews->setEnabled(true);
	mw->actionNewProgram->setEnabled(true);
	mw->actionNewList->setEnabled(true);
	
	return saved;
}

bool ProgramGroupBox::walidacja()
{
	return (!tytulLineEdit->text().isEmpty() && ((mw->aviConverted && !stopKlatkaName.isEmpty()) || currProg.id >0));
}

void ProgramGroupBox::ftpFinished(int res)
{
	if (res == QNetworkReply::NoError)
	{
		con->append("Transfer pliku "+ mw->fileName + QString :: fromUtf8(" zakończony powodzeniem"));
		if (mw->fileName.right(3) == "jpg")
		{
			con->append(QString :: fromUtf8("\nWysyłanie pliku miniaturki na serwer.\n"));
			QString thbName = mw->createThumb(mw->fileName);
			QString saveName = QString::number(mw->recordID) + "-thb.jpg";
			mw->u.start(thbName, saveName, mw->programyURL + QString::number(mw->recordID) + "/");
			mw->fileName = thbName;
		}
		else if (mw->fileName.right(3) == "thb")
		{
			if (!mw->aviConverted)
			{
				emit finished();
				return;
			}
			con->append(QString :: fromUtf8("\nWysyłanie pliku MP4 na serwer.\n"));
			mw->fileName = mw->fileName.replace(".thb",".mp4");
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ".mp4", mw->programyURL + QString::number(mw->recordID) + "/");
		}
		else if (mw->fileName.right(3) == "mp4")
		{
			con->append(QString :: fromUtf8("\nWysyłanie pliku OGV na serwer.\n"));
			mw->fileName = mw->fileName.replace(".mp4",".ogv");
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ".ogv", mw->programyURL + QString::number(mw->recordID) + "/");
		}
		else if (mw->fileName.right(3) == "ogv")
		{
			con->append(QString :: fromUtf8("\nWysyłanie pliku WEBM na serwer.\n"));
			mw->fileName = mw->fileName.replace(".ogv",".webm");
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ".webm", mw->programyURL + QString::number(mw->recordID) + "/");
		}
		else if (mw->fileName.right(4) == "webm")
		{
			mw->fileName.clear();
			con->append(QString :: fromUtf8("\n\n***************************Skończone"));
			emit finished();
		}
	}
	else
	{
		mw->actionNewNews->setEnabled(true);
		mw->actionNewProgram->setEnabled(true);
		mw->actionNewList->setEnabled(true);
		mw->actionSave->setEnabled(true);
		con->append(QString :: fromUtf8("\nBłąd przy wysyłaniu ") + mw->fileName);
	}
}

void ProgramGroupBox::restartVideo()
{
	videoPlayer->stop();
	videoPlayer->seek(0);
	startButton->setEnabled(true);
	pauseButton->setEnabled(false);
}

void ProgramGroupBox::on_tytulLineEdit_textChanged(const QString &arg1)
{
	QString str = arg1.trimmed();
	if (!str.isEmpty())
	{
		tytulLabel->setStyleSheet("QLabel {color:black;}");
		mw->actionSave->setEnabled(walidacja());
	}
}

void ProgramGroupBox::on_charTableButton_clicked()
{
	if (m_charTable == NULL)
	{
		m_charTable = new CharTable(this);
		connect(m_charTable, SIGNAL(rejected()), this, SLOT(closeCharTable()));
		connect(m_charTable,SIGNAL(pushText(QString)), this->opis, SLOT(insertPlainText(QString)));
		m_charTable->show();
	}
	else
	{
		m_charTable->hide();
		delete m_charTable;
		closeCharTable();
	}
}

void ProgramGroupBox::closeCharTable()
{
	m_charTable = NULL;
	charTableButton->setChecked(false);
}

void ProgramGroupBox::menuChange()
{
	bool notEmpty = false;
	for (int i=0; i < katButton->menu()->actions().count(); ++i)
	{
		QAction * action = katButton->menu()->actions().at(i);
		if (action->isChecked())
		{
			notEmpty = true;
			break;
		}
	}
	katButton->setStyleSheet(notEmpty ? "QPushButton { color: black; }" : "QPushButton { color: red; }");
}

void ProgramGroupBox::on_wideCheckBox_toggled(bool checked)
{
	mw->avi169 = checked;
}

void ProgramGroupBox::on_aviNoSaveCheckBox_toggled(bool checked)
{
	convertButton->setEnabled(!checked);
	con->clear();
	con->setText(QString::fromUtf8("Pliki nie będą wysyłane na serwer."));
}
