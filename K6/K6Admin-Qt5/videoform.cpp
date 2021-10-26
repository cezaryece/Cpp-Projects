#include "videoform.h"
#include "fileutils.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>
#include "qftp.h"
#include "videoplayer.h"

VideoForm::VideoForm(MainWindow *parent) :
	GbBase(parent), stopklatkaNr(0)
{
	setupUi(this);
	con = console;
	openAVI = openAviButton;
	convertAVI = convertButton;
	mp4L = MP4label; mw->mp4PBar = mp4ProgressBar;
	ogvL = OGVlabel; mw->ogvPBar = ogvProgressBar;
	webmL = WEBMlabel;mw->webmPBar = webmProgressBar;
	
	aviLabel->setText("Brak pliku");
	aviLabel->setStyleSheet("QLabel { color: red; }");
	openAviButton->setStyleSheet("QPushButton { color: red; }");
	convertButton->setStyleSheet("QPushButton { color: red; }");
	fotkiGroupBox->setStyleSheet("QGroupBox { color: red; }");
	startButton->setEnabled(false);
	stopklatkaButton->setEnabled(false);
	pauseButton->setEnabled(false);
	convertButton->setEnabled(false);
	mw->actionSave->setEnabled(false);
	mw->aviConverted = false;
}

bool VideoForm::save()
{
	QString sql = "UPDATE K6_archiwum SET film=1 WHERE id=" + QString::number(newsID);
	QSqlQuery myQuery;
	if (myQuery.exec(sql))
	{
		mw->recordID = newsID;
		QFtp *ftp = new QFtp ();
		ftp->connectToHost("oferuje.pl");
		ftp->login("kanal6", "k2n21b");
		ftp->cd("video/newsy");
		ftp->mkdir(QString::number(mw->recordID));
		while (ftp->hasPendingCommands())
			qApp->processEvents(QEventLoop::WaitForMoreEvents);
		ftp->close();
		while (ftp->hasPendingCommands())
			qApp->processEvents(QEventLoop::WaitForMoreEvents);
		if (fotkaWidgetsList.count() > 0)
		{
			//wysylanie fotki nr 0
			mw->lastFoto = 0;
			mw->fileName = fotkaWidgetsList.at(mw->lastFoto)->fotkaName;
			QFileInfo fi(mw->fileName);
			QString fname = fi.baseName() + "-" + QString::number(mw->lastFoto) + ".jpg";
			mw->u.start(mw->fileName, fname, mw->galerieURL + QString::number(mw->recordID) + "/");
			con->append(QString :: fromUtf8("\nWysyłanie fotki ") + mw->fileName + "\n");
		}
		else
		{
			con->append(QString :: fromUtf8("\nWysyłanie pliku MP4 na serwer."));
			mw->fileName = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + QFileInfo(mw->aviFileName).baseName() + ".mp4";
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ".mp4", mw->newsyURL + QString::number(mw->recordID) + "/");
		}
		return true;
	}
	queryError(myQuery,this);
	return false;
}

void VideoForm::ftpFinished(int res)
{
	if (res == QNetworkReply::NoError)
	{
		
		con->append("Transfer pliku "+ mw->fileName + QString :: fromUtf8(" zakończony powodzeniem"));
		
		if (mw->fileName.right(3) == "thb")
		{
			++mw->lastFoto;
			if (mw->lastFoto < fotkaWidgetsList.count())
			{
				mw->fileName = fotkaWidgetsList.at(mw->lastFoto)->fotkaName;
				QFileInfo fi(mw->fileName);
				QString fname = fi.baseName() + "-" + QString::number(mw->lastFoto) + ".jpg";
				mw->u.start(mw->fileName, fname, mw->galerieURL + QString::number(mw->recordID) + "/");
				con->append(QString :: fromUtf8("\nWysyłanie fotki ") + mw->fileName + "\n");
			}
			else if (mw->aviConverted)
			{
				con->append(QString :: fromUtf8("\nWysyłanie pliku MP4 na serwer."));
				mw->fileName = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + QFileInfo(mw->aviFileName).baseName() + ".mp4";
				mw->u.start(mw->fileName, QString::number(mw->recordID) + ".mp4", mw->newsyURL + QString::number(mw->recordID) + "/");
			}
			else
			{
				mw->fileName.clear();
				con->append(QString :: fromUtf8("\n***************************Skończone"));
				emit finished();
			}
		}
		else if (mw->fileName.right(3) == "jpg")
		{
			//thumbnail
			con->append(QString :: fromUtf8("Wysyłanie pliku miniaturki.\n"));
			QString curUrl = mw->galerieURL + QString::number(mw->recordID) + "/thumb/";
			QString thbName = mw->createThumb(mw->fileName);
			QString saveName = QFileInfo(thbName).baseName() + "-" + QString::number(mw->lastFoto) + ".jpg";
			mw->u.start(thbName, saveName, curUrl);
			mw->fileName = thbName;
		}
		else if (mw->fileName.right(3) == "mp4")
		{
			con->append(QString :: fromUtf8("Wysyłanie pliku OGV na serwer.\n"));
			mw->fileName = mw->fileName.replace(".mp4",".ogv");
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ".ogv", mw->newsyURL + QString::number(mw->recordID) + "/");
		}
		else if (mw->fileName.right(3) == "ogv")
		{
			con->append(QString :: fromUtf8("Wysyłanie pliku WEBM na serwer.\n"));
			mw->fileName = mw->fileName.replace(".ogv",".webm");
			mw->u.start(mw->fileName, QString::number(mw->recordID) + ".webm", mw->newsyURL + QString::number(mw->recordID) + "/");
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
		con->append(QString :: fromUtf8("\nBłąd przy wysyłaniu ") + mw->fileName);
		mw->actionSave->setEnabled(true);
	}
}

void VideoForm::restartVideo()
{
	mw->vp.stop();
	mw->vp.seek(0);
	startButton->setEnabled(true);
	pauseButton->setEnabled(false);
}

void VideoForm::on_convertButton_clicked()
{
	convertButton->setEnabled(false);
	openAviButton->setEnabled(false);
	mw->actionNewList->setEnabled(false);
	mw->convertVideos();
}

void VideoForm::on_openAviButton_clicked()
{
	mw->aviConverted = false;
	QString fileName = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,QString :: fromUtf8("Otwórz plik VIDEO"), mw->lastDir, "Pliki VIDEO (*.avi *.mp4)"));
	if (!fileName.isEmpty()) {
		mw->lastDir = QFileInfo(fileName).absolutePath();
		aviLabel->setText(fileName);
		aviLabel->setStyleSheet("QLabel { color: black; }");
		openAviButton->setStyleSheet("QPushButton { color: black; }");
		convertButton->setStyleSheet("QPushButton { color: red; }");
		convertButton->setEnabled(true);
		mw->aviFileName = mw->fileName = fileName;
		mw->aviConverted = false;
		mw->aviTime = 0;
		mw->avi169 = fileName.endsWith(".mp4");
		wideCheckBox->setChecked(mw->avi169);
		mw->vp.load(fileName);
		mw->vp.play();
		mw->vp.pause();
		startButton->setEnabled(true);
		stopklatkaButton->setEnabled(true);
//		connect(vp.mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(totalTimeChanged()));
//		connect(vp, SIGNAL(finished()), this, SLOT(restartVideo()));
	}
}

void VideoForm::totalTimeChanged()
{
	bool seekable = mw->vp.isSeekable();
	long total = mw->vp.duration();
	if (mw->aviTime == 0)
	{
		mw->aviTime = (double) total / 1000.0;
		mw->aviFrames = (int) mw->aviTime * 16;
	}
	if (seekable)
	{
		totalTimeMin->setEnabled(true);
		totalTimeSec->setEnabled(true);
		int totalTime = total/1000;
		totalTimeMin->display(totalTime/60);
		totalTimeSec->display(totalTime % 60);
	}
	else
	{
		totalTimeMin->setEnabled(false);
		totalTimeSec->setEnabled(false);
	}
}

void VideoForm::on_startButton_clicked()
{
	startButton->setEnabled(false);
	pauseButton->setEnabled(true);
	mw->vp.play();
}

void VideoForm::on_pauseButton_clicked()
{
	mw->vp.pause();
	pauseButton->setEnabled(false);
	startButton->setEnabled(true);
}

void VideoForm::on_stopklatkaButton_clicked()
{
	QString fname = QFileInfo(mw->aviFileName).baseName() + "." + QString::number(stopklatkaNr++) + ".jpg";
	QString fpath = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + fname;
	int timeSec = mw->vp.position() / 1000;
	int currMin = timeSec / 60;
	int curSec = timeSec % 60;
	int mSec = mw->vp.position() - (timeSec * 1000);
	//    if (vp.currentTime() > 5)
	//        mSec += -5;
	//    else mSec = 0;
	QString deinterlace;
#ifndef Q_OS_UNIX
	deinterlace = "-filter:v yadif";
#else
	deinterlace = "-deinterlace";
#endif
	QString cmd = "ffmpeg -ss 0:"+ QString::number(currMin) + ":" + QString::number(curSec) + "." + QString::number(mSec) + " -i \"" + mw->aviFileName + "\" "+ deinterlace+" -t 0.001 -f image2 \"" + fpath + "\"";
	
	QProcess shutter;
	shutter.start(cmd);
	shutter.waitForFinished(-1);
	if (QFileInfo(fpath).exists())
		stopKlatkiAppend(fpath);
	else
		qDebug() << "stopklatka nieistnieje" << fpath;
}

void VideoForm::stopKlatkiAppend(QString fname)
{
	FotkaWidget * fotka = new FotkaWidget(fname, this);
	connect(fotka, SIGNAL(fotkaMove(int)), this, SLOT(moveFoto(int)));
	fotkiList->insertWidget(fotkiList->count()-1, fotka);
	fotkaWidgetsList.append(fotka);
	fotkiGroupBox->repaint();
	fotkiGroupBox->setStyleSheet("QGroupBox { color: black; }");
	mw->actionSave->setEnabled(walidacja());
}

bool VideoForm::walidacja()
{
	return mw->aviConverted;
}

void VideoForm::setNewsId(int id)
{
	newsID = mw->recordID = id;
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT DATE(data), tytul, miasto FROM K6_archiwum WHERE id=" + QString::number(newsID) + " LIMIT 1"))
	{
		myQuery.first();
		videoGroupBox->setTitle(myQuery.value(0).toString() + " " + myQuery.value(1).toString() + " " + myQuery.value(2).toString());
	}
	else
		queryError(myQuery,this);
}

void VideoForm::on_fotkiDelSel_clicked()
{
	int count = fotkaWidgetsList.count();
	for (int i = count-1; i >=0; --i)
	{
		FotkaWidget* fw = fotkaWidgetsList.at(i);
		if (fw->isSel())
		{
			fotkiList->removeWidget(fw);
			fotkaWidgetsList.removeOne(fw);
			disconnect(fw, SIGNAL(fotkaMove(int)), this, SLOT(moveFoto(int)));
			fw->deleteLater();
		}
	}
	mw->actionSave->setEnabled(walidacja());
	if (count != fotkiList->count()-1)
	{
		if (fotkiList->isEmpty())
			fotkiGroupBox->setStyleSheet("QGroupBox { color: red; }");
		fotkiGroupBox->repaint();
	}
}

void VideoForm::on_fotkiDelAll_clicked()
{
	for (int i = fotkaWidgetsList.count()-1; i >=0; --i)
	{
		FotkaWidget * fw = fotkaWidgetsList.at(i);
		fotkiList->removeWidget(fw);
		fotkaWidgetsList.removeOne(fw);
		disconnect(fw, SIGNAL(fotkaMove(int)), this, SLOT(moveFoto(int)));
		fw->deleteLater();
	}
	
	QString tempdir(mw->workingPath + QDir::separator() + "temp" + QDir::separator());
	FileUtils::removeFiles(tempdir, "jpg");
	fotkiGroupBox->setStyleSheet("QGroupBox { color: red; }");
	fotkiGroupBox->repaint();
	mw->actionSave->setEnabled(false);
}

void VideoForm::moveFoto(int move)
{
	FotkaWidget* fw = dynamic_cast<FotkaWidget*>( sender() );
	int index = fotkaWidgetsList.indexOf(fw);
	switch (move) {
	case 1:
		if (index == 0)
			return;
		fotkaWidgetsList.move(index, index -1);
		fotkiList->removeWidget(fw);
		fotkiList->insertWidget(index -1, fw);
		break;
	case 2:
		if (index == fotkaWidgetsList.count() -1)
			return;
		fotkaWidgetsList.move(index, index +1);
		fotkiList->removeWidget(fw);
		fotkiList->insertWidget(index +1, fw);
		break;
	case 0:
		if (index == 0)
			return;
		fotkaWidgetsList.move(index, 0);
		fotkiList->removeWidget(fw);
		fotkiList->insertWidget(0, fw);
		break;
	case 9:
		if (index == fotkaWidgetsList.count() -1)
			return;
		fotkaWidgetsList.move(index, fotkaWidgetsList.count() -1);
		fotkiList->removeWidget(fw);
		fotkiList->insertWidget(fotkaWidgetsList.count()-1, fw);
		break;
	}
	fotkiGroupBox->repaint();
	mw->actionSave->setEnabled(walidacja());
}

void VideoForm::on_wideCheckBox_clicked(bool checked)
{
	mw->avi169 = checked;
}
