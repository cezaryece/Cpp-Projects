#include "newsgroupbox.h"
#include <QAction>
#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QFtp>
#include <QImageReader>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QPixmap>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>
#include <QTextCodec>
#include <QTextList>
#include <Phonon/MediaSource>
#include <Phonon/MediaObject>
#include <Phonon/VideoWidget>
#include "fileutils.h"
#include "uploader.h"

NewsGroupBox::NewsGroupBox(MainWindow *parent, News news) :
	GbBase(parent), currNews(news), stopklatkaNr(0), m_charTable(NULL)
{
	setupUi(this);
	con = console;
	openAVI = openAviButton;
	convertAVI = convertButton;
	mp4L = MP4label; mw->mp4PBar = mp4ProgressBar;
	ogvL = OGVlabel; mw->ogvPBar = ogvProgressBar;
	webmL = WEBMlabel;mw->webmPBar = webmProgressBar;
	
	miastoComboBox->insertItem(0, QString::fromUtf8("Słupsk"));
	miastoComboBox->insertItem(1, QString::fromUtf8("Lębork"));
	setupTextActions();
	
	katButton->setMenu(mw->katMenu);
	QList<QAction*> actionsList = katButton->menu()->actions();
	foreach (QAction * action, actionsList)
		action->setChecked(false);
	
	textEdit->setAlignment(Qt::AlignJustify);
	textAlignJ(true);
	
	if (currNews.id == 0)
	{
		miastoComboBox->setCurrentIndex(mw->miastoIndex);
		dataEdit->setDate(QDate::currentDate());
		waznyCheckBox->setChecked(false);
		lastMinuteCheckBox->setChecked(false);
		waznyDataCzasEdit->setEnabled(false);
		waznyDataCzasEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
		waznyDataCzasEdit->setTime(QTime(17,0));
		waznyDataCzasEdit->setMinimumDateTime(QDateTime::currentDateTime());
		imprezaGroupBox->setChecked(false);
		imprezaDataEdit->setDate(QDate::currentDate());
		imprezaDataEdit->setMinimumDate(QDate::currentDate());
		autorLabel->setStyleSheet("QLabel { color: red; }");
		tytulLabel->setStyleSheet("QLabel { color: red; }");
		mw->actionSave->setEnabled(false);
		mw->avi169 = true;
	}
	else
	{
		if (currNews.id == 0)
		{
			emit finished();
			return;
		}
		setTitle("Edycja Newsa");
		miastoComboBox->lineEdit()->setText(currNews.miasto);
		QDateTime dt = QDateTime::fromString(currNews.data,Qt::ISODate);
		dataEdit->setDate(dt.date());
		waznyCheckBox->setChecked(currNews.wazny);
		lastMinuteCheckBox->setChecked(currNews.lastminute);
		waznyDataCzasEdit->setEnabled(currNews.wazny);
		waznyDataCzasEdit->setDateTime(QDateTime::fromString(currNews.expire,Qt::ISODate));
		imprezaGroupBox->setChecked(currNews.impreza);
		if (currNews.impreza)
		{
			imprezaDataEdit->setDate(QDate::fromString(currNews.impreza_data,Qt::ISODate));
			imprezaNazwaLineEdit->setText(currNews.impreza_nazwa);
			patronatCheckBox->setChecked(currNews.patronat);
		}
		autorLineEdit->setText(currNews.podpis);
		
		textEdit->blockSignals(true);
		textEdit->setText(currNews.text);
		textEdit->blockSignals(false);
		
		tytulLineEdit->setText(currNews.tytul);
		
		//kategoriaID
		foreach (QString kategoriaID, currNews.katID)
		{
			foreach (QAction * action, actionsList)
			{
				if (action->data().toString() == kategoriaID)
				{
					action->setChecked(true);
					break;
				}
			}
		}
		mw->actionSave->setEnabled(true);
		mw->avi169 = currNews.avipath.endsWith(".mp4");
	}
	wideCheckBox->setChecked(mw->avi169);
	textEdit->setAcceptDrops(false);
	textEdit->setAcceptRichText(false);
	aviNoSaveCheckBox->setChecked(true);
	if (currNews.film)
		aviLabel->setText(currNews.avipath.isEmpty() ? QString::fromUtf8("Film jest już załączony") : currNews.avipath);
	else if (!currNews.avipath.isEmpty())
		aviLabel->setText(currNews.avipath + QString::fromUtf8(" czeka na konwersję w kolejce na serwerze"));
	else
	{
		aviLabel->setText("Brak pliku");
		aviNoSaveCheckBox->setChecked(false);
	}
	
	mw->aviConverted = false;
	startButton->setEnabled(false);
	stopklatkaButton->setEnabled(false);
	pauseButton->setEnabled(false);
	convertButton->setEnabled(false);
	if (mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept", mw->prawaID))
		acceptCheckBox->setChecked(currNews.acceptID >0);
	else
		acceptCheckBox->setVisible(false);
	
	charTableButton->setChecked(false);
}

NewsGroupBox::~NewsGroupBox()
{
	mw->mp4PBar = mw->ogvPBar = mw->webmPBar = NULL;
	mw->aviTime = 0;
	if (m_charTable != 0)
		delete m_charTable;
}

bool NewsGroupBox::save()
{
	currNews.data = dataEdit->dateTime().toString("yyyy-MM-dd") + QTime::currentTime().toString(" hh:mm:ss");
	currNews.wazny = waznyCheckBox->isChecked();
	currNews.expire = waznyDataCzasEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
	currNews.lastminute = lastMinuteCheckBox->isChecked();
	currNews.userID = mw->loginID;
	if (mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept", mw->prawaID))
		currNews.acceptID =  acceptCheckBox->isChecked() ? mw->loginID : 0;
	else
		currNews.acceptID = 0;
	currNews.katID.clear();
	for (int i=0; i < katButton->menu()->actions().count(); ++i)
	{
		QAction * action = katButton->menu()->actions().at(i);
		if (action->isChecked())
			currNews.katID.append(action->data().toString());
	}
	if (!aviNoSaveCheckBox->isChecked())
	{
		if (!mw->aviFileName.isEmpty())
		{
			currNews.film = mw->aviConverted;
			QString sd24Path = QDir::toNativeSeparators(mw->aviFileName);
			int pathStart = sd24Path.indexOf(QString(QDir::separator() + QString("DS_")));
			sd24Path.remove(0,pathStart);
			sd24Path.replace("\\","/");
			currNews.avipath = sd24Path;
		}
		else
			currNews.avipath.clear();
	}
	else
		mw->aviConverted = false;
	currNews.impreza = imprezaGroupBox->isChecked();
	currNews.patronat = currNews.impreza && patronatCheckBox->isChecked();
	currNews.impreza_data = imprezaDataEdit->date().toString("yyyy-MM-dd");
	currNews.impreza_nazwa = imprezaNazwaLineEdit->text();
	currNews.miasto = miastoComboBox->lineEdit()->text();
	currNews.tytul = tytulLineEdit->text();
	
	QString htmlText = textEdit->toHtml();
	int start = htmlText.indexOf("<p",0,Qt::CaseInsensitive);
	htmlText = htmlText.remove(0,start);
	htmlText = htmlText.remove("</body></html>");
	htmlText = htmlText.remove(" -qt-block-indent:0;");
	htmlText = htmlText.remove(" text-indent:0px;");
	htmlText = htmlText.remove("font-size:small;");
	QRegExp rx("font-family:.(['a-zA-Z0-9 _,.-])*;");
	rx.setMinimal(true);
	htmlText = htmlText.remove(rx);
	rx.setPattern("font-size:.(['a-zA-Z0-9 _,.-])*;");
	rx.setMinimal(true);
	htmlText = htmlText.remove(rx);
	htmlText.replace("font-weight:600","font-weight:bold");
	currNews.text = htmlText;
	qDebug() << htmlText;
	currNews.podpis = autorLineEdit->text();
	currNews.fotka_opis = currNews.tytul;
	
	QString sql;
	if (currNews.id == 0)
		sql = "INSERT INTO K6_archiwum (data,expire,wazny,lastminute,userID,acceptID,katID,film,avipath,film_data,impreza,impreza_patronat,impreza_data,impreza_nazwa,miasto,tytul,text,podpis,fotka_opis) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
	else
		sql = "UPDATE K6_archiwum SET data=?,expire=?,wazny=?,lastminute=?,userID=?,acceptID=?,katID=?,film=?,avipath=?,film_data=?,impreza=?,impreza_patronat=?,impreza_data=?,impreza_nazwa=?,miasto=?,tytul=?,text=?,podpis=?,fotka_opis=? WHERE id=" + QString::number(currNews.id);
	
	bool saved = saveNews(sql);
	
	if (saved)
	{
		if (mw->aviConverted || fotkaWidgetsList.count() > 0)
		{
			QFtp *ftp = new QFtp ();
			ftp->setTransferMode(QFtp::Passive);
			ftp->connectToHost("kanal6.pl");
			ftp->login("kanal6", "k2n21b");
			ftp->cd("galerieK6");
			ftp->mkdir(QString::number(mw->recordID));
			while (ftp->hasPendingCommands())
				qApp->processEvents(QEventLoop::WaitForMoreEvents);
			ftp->cd(QString::number(mw->recordID));
			ftp->mkdir("thumb");
			while (ftp->hasPendingCommands())
				qApp->processEvents(QEventLoop::WaitForMoreEvents);
			ftp->close();
			ftp->connectToHost("oferuje.pl");
			ftp->login("kanal6", "k2n21b");
			ftp->cd("video/newsy");
			ftp->mkdir(QString::number(mw->recordID));
			while (ftp->hasPendingCommands())
				qApp->processEvents(QEventLoop::WaitForMoreEvents);
			ftp->close();
			while (ftp->hasPendingCommands())
				qApp->processEvents(QEventLoop::WaitForMoreEvents);
			if (currNews.id==0) 
			{
				if (fotkaWidgetsList.count() > 0)
				{
					//wysylanie fotki nr 0
					mw->lastFoto = 0;
					mw->fileName = fotkaWidgetsList.at(0)->fotkaName;
					QString newName = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + QString::number(mw->recordID) + ".jpg";
					QFile(mw->fileName).copy(newName);
					mw->fileName = newName;
					mw->u.start(newName, "", mw->fotoURL);
					console->append(QString :: fromUtf8("\nWysyłanie głównej fotki na serwer. ") + newName);
				}
			}
			else
			{
				if (fotkaWidgetsList.count() > 0)
				{
					mw->lastFoto = 1;
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
			}
		}
		else
			emit finished();
	}
	return saved;
}

bool NewsGroupBox::saveNews(QString sql)
{
	
	QSqlQuery myQuery;
	myQuery.prepare(sql);
	myQuery.addBindValue(currNews.data);
	myQuery.addBindValue(currNews.expire);//expire
	myQuery.addBindValue(currNews.wazny);
	myQuery.addBindValue(currNews.lastminute);
	myQuery.addBindValue(currNews.userID);
	myQuery.addBindValue(currNews.acceptID);
	
	QString katIDStr = currNews.katID.join(":");
	myQuery.addBindValue(katIDStr.isEmpty() ? QVariant(QString("")) : katIDStr);
	
	myQuery.addBindValue(currNews.film);
	myQuery.addBindValue(currNews.avipath.isEmpty() ? QVariant(QString("")) : currNews.avipath);
	myQuery.addBindValue(dataEdit->dateTime().toString("yyyy-MM-dd"));
	myQuery.addBindValue(currNews.impreza);
	myQuery.addBindValue(currNews.patronat);
	myQuery.addBindValue(currNews.impreza_data.isEmpty() ? QVariant(QString("")) : currNews.impreza_data);
	myQuery.addBindValue(currNews.impreza_nazwa.isEmpty() ? QVariant(QString("")) : currNews.impreza_nazwa);
	myQuery.addBindValue(currNews.miasto);
	myQuery.addBindValue(currNews.tytul);
	myQuery.addBindValue(currNews.text);
	myQuery.addBindValue(currNews.podpis);
	myQuery.addBindValue(currNews.fotka_opis);
	
	if (myQuery.exec())
	{
		if (currNews.id == 0)
			mw->recordID = myQuery.lastInsertId().toInt();
		else
			mw->recordID = currNews.id;
		return true;
	}
	queryError(myQuery,this);
	return false;
}

void NewsGroupBox::ftpFinished(int res)
{
	if (res == QNetworkReply::NoError)
	{
		
		con->append("Transfer pliku "+ mw->fileName + QString :: fromUtf8(" zakończony powodzeniem"));
		
		if (mw->fileName.right(3) == "jpg")
		{
			//thumbnail
			con->append(QString :: fromUtf8("Wysyłanie pliku miniaturki.\n"));
			QString curUrl;
			if (mw->lastFoto == 0)
				curUrl = mw->fotoURL + "thumb/";
			else
				curUrl = mw->galerieURL + QString::number(mw->recordID) + "/thumb/";
			QString thbName = mw->createThumb(mw->fileName);
			QString saveName = QFileInfo(thbName).baseName();
			if (mw->lastFoto > 0)
				saveName.append("-" + QString::number(mw->lastFoto));
			saveName.append(".jpg");
			mw->u.start(thbName, saveName, curUrl);
			mw->fileName = thbName;
		}
		else if (mw->fileName.right(3) == "thb")
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
		con->append(QString :: fromUtf8("\nBłąd przy wysyłaniu ") + mw->fileName);
}

void NewsGroupBox::restartVideo()
{
	videoPlayer->stop();
	videoPlayer->seek(0);
	startButton->setEnabled(true);
	pauseButton->setEnabled(false);
}

void NewsGroupBox::setupTextActions()
{
	connect(boldButton,SIGNAL(clicked()), this, SLOT(textBold()));
	connect(italicButton,SIGNAL(clicked()), this, SLOT(textItalic()));
	connect(underlineButton,SIGNAL(clicked()), this, SLOT(textUnderline()));
	connect(leftButton,SIGNAL(clicked()), this, SLOT(textAlignL()));
	connect(centerButton,SIGNAL(clicked(bool)), this, SLOT(textAlignC(bool)));
	connect(rightButton,SIGNAL(clicked(bool)), this, SLOT(textAlignR(bool)));
	connect(justifyButton,SIGNAL(clicked(bool)), this, SLOT(textAlignJ(bool)));
	comboStyle->addItem("Standard");
	comboStyle->addItem(QString::fromUtf8("Lista (Koło)"));
	comboStyle->addItem(QString::fromUtf8("Lista (Okrąg)"));
	comboStyle->addItem("List (Kwadrat)");
	comboStyle->addItem("Lista (1,2,3)");
	comboStyle->addItem("Lista (a,b,c)");
	comboStyle->addItem("Lista (A,B,C)");
	comboStyle->addItem("Lista (i,ii,iii)");
	comboStyle->addItem("Lista (I,II,II)");
	connect(comboStyle, SIGNAL(activated(int)), this, SLOT(textStyle(int)));
	
	//	comboSize->setObjectName("comboSize");
	//	comboSize->setEditable(true);
	
	//	QFontDatabase fdb;
	//	foreach(int size, fdb.standardSizes())
	//		comboSize->addItem(QString::number(size));
	
	//	connect(comboSize, SIGNAL(activated(QString)), this, SLOT(textSize(QString)));
	//	comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font().pointSize())));
	
	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	colorButton->setIcon(QIcon(pix));
	connect(colorButton, SIGNAL(clicked()), this, SLOT(textColor()));
	connect(textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(currentCharFormatChanged(QTextCharFormat)));
	connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
	colorChanged(textEdit->textColor());
	alignmentChanged(textEdit->alignment());
}

void NewsGroupBox::on_tytulLineEdit_textChanged(const QString &arg1)
{
	QString str = arg1.trimmed();
	if (!str.isEmpty())
		tytulLabel->setStyleSheet("QLabel {color:black;}");
	mw->actionSave->setEnabled(walidacja());
}

void NewsGroupBox::on_miastoComboBox_editTextChanged(const QString &arg1)
{
	QString str = arg1.trimmed();
	if (!str.isEmpty())
		miastoLabel->setStyleSheet("QLabel {color:black;}");
	mw->actionSave->setEnabled(walidacja());
}

void NewsGroupBox::on_autorLineEdit_textChanged(const QString &arg1)
{
	QString str = arg1.trimmed();
	if (!str.isEmpty())
		autorLabel->setStyleSheet("QLabel {color:black;}");
	mw->actionSave->setEnabled(walidacja());
}

void NewsGroupBox::on_imprezaGroupBox_toggled(bool checked)
{
	if (checked)
	{
		QString str = imprezaNazwaLineEdit->text().trimmed();
		if (str.isEmpty())
			imprezaNazwaLineEdit->setStyleSheet("QLineEdit {color:red;}");
		else
			imprezaNazwaLineEdit->setStyleSheet("QLineEdit {color:black;}");
		imprezaDataEdit->setDate(QDate::currentDate());
	}
	else
		imprezaNazwaLineEdit->setStyleSheet("QLineEdit {color:black;}");
	mw->actionSave->setEnabled(walidacja());
}

void NewsGroupBox::on_imprezaNazwaLineEdit_textChanged(const QString &arg1)
{
	QString str = arg1.trimmed();
	if (str.isEmpty())
		imprezaNazwaLineEdit->setStyleSheet("QLineEdit {color:red;}");
	else
		imprezaNazwaLineEdit->setStyleSheet("QLineEdit {color:black;}");
	mw->actionSave->setEnabled(walidacja());
}

void NewsGroupBox::on_waznyCheckBox_clicked(bool checked)
{
	waznyDataCzasEdit->setEnabled(checked);
	mw->actionSave->setEnabled(walidacja());
	if (checked)
		waznyDataCzasEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
}

void NewsGroupBox::on_convertButton_clicked()
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

void NewsGroupBox::on_openAviButton_clicked()
{
	mw->resetProgress();
	QString fileName = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,QString :: fromUtf8("Otwórz plik VIDEO"), mw->lastDir, "Pliki video (*.avi *.mp4)"));
	if (!fileName.isEmpty()) {
		mw->aviConverted = false;
		mw->aviTime = 0;
		mw->lastDir = QFileInfo(fileName).absolutePath();
		aviLabel->setText(fileName);
		convertButton->setEnabled(!aviNoSaveCheckBox->isChecked());
		mw->aviFileName = mw->fileName = fileName;
		mw->aviConverted = false;
		mw->avi169 = fileName.endsWith(".mp4");
		wideCheckBox->setChecked(mw->avi169);
		videoPlayer->load(fileName);
		videoPlayer->play();
		videoPlayer->pause();
		seekSlider->setMediaObject(videoPlayer->mediaObject());
		startButton->setEnabled(true);
		stopklatkaButton->setEnabled(true);
		connect(videoPlayer->mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(totalTimeChanged()));
		connect(videoPlayer, SIGNAL(finished()), this, SLOT(restartVideo()));
	}
}

void NewsGroupBox::on_aviNoSaveCheckBox_toggled(bool checked)
{
	convertButton->setEnabled(!checked);
	con->clear();
	con->setText(QString::fromUtf8("Pliki nie będą wysyłane na serwer."));
}

void NewsGroupBox::totalTimeChanged()
{
	bool seekable = videoPlayer->mediaObject()->isSeekable();
	long total = videoPlayer->totalTime();
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

void NewsGroupBox::on_startButton_clicked()
{
	startButton->setEnabled(false);
	pauseButton->setEnabled(true);
	videoPlayer->play();
}

void NewsGroupBox::on_pauseButton_clicked()
{
	videoPlayer->pause();
	pauseButton->setEnabled(false);
	startButton->setEnabled(true);
}

void NewsGroupBox::on_stopklatkaButton_clicked()
{
	QString fname = QFileInfo(mw->aviFileName).baseName() + "." + QString::number(stopklatkaNr++) + ".jpg";
	QString fpath = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + fname;
	int timeSec = videoPlayer->currentTime() / 1000;
	int currMin = timeSec / 60;
	int curSec = timeSec % 60;
	int mSec = videoPlayer->currentTime() - (timeSec * 1000);
	//    if (videoPlayer->currentTime() > 5)
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

void NewsGroupBox::stopKlatkiAppend(QString fname)
{
	FotkaWidget * fotka = new FotkaWidget(fname, this);
	connect(fotka, SIGNAL(fotkaMove(int)), this, SLOT(moveFoto(int)));
	fotkiList->insertWidget(fotkiList->count()-1, fotka);
	fotkaWidgetsList.append(fotka);
	fotkiGroupBox->repaint();
}

bool NewsGroupBox::walidacja()
{
	if (imprezaGroupBox->isChecked() && !imprezaDataEdit->dateTime().isValid())
	{
		imprezaDataEdit->setStyleSheet("QDateEdit { color: red; }");
		return false;
	}
	else
		imprezaDataEdit->setStyleSheet("QDateEdit { color: black; }");
	if (waznyCheckBox->isChecked() && (!waznyDataCzasEdit->dateTime().isValid() || waznyDataCzasEdit->dateTime() <= QDateTime::currentDateTime()))
	{
		waznyDataCzasEdit->setStyleSheet("QDateEdit { color: red; }");
		return false;
	}
	else
		waznyDataCzasEdit->setStyleSheet("QDateEdit { color: black; }");
	return !(tytulLineEdit->text().trimmed().isEmpty()
			 || miastoComboBox->currentText().trimmed().isEmpty()
			 || dataEdit->text().trimmed().isEmpty()
			 || textEdit->toPlainText().trimmed().isEmpty()
			 || autorLineEdit->text().trimmed().isEmpty()
			 || (imprezaGroupBox->isChecked() && imprezaNazwaLineEdit->text().trimmed().isEmpty()) );
}

void NewsGroupBox::on_fotkiDelSel_clicked()
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
	if (count != fotkiList->count()-1)
		fotkiGroupBox->repaint();
}

void NewsGroupBox::on_fotkiDelAll_clicked()
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
	fotkiGroupBox->repaint();
}

void NewsGroupBox::on_zdyskuButton_clicked()
{
	qDebug() << QImageReader::supportedImageFormats();
	QStringList imageFileNames = QFileDialog::getOpenFileNames(this,QString :: fromUtf8("Obrazy"), mw->lastDir, "Obrazy (*.png *.xpm *.jpg)");
	if (!imageFileNames.isEmpty())
	{
		foreach (QString imageFileName, imageFileNames)
		{
			imageFileName = QDir::toNativeSeparators(imageFileName);
			
			QPixmap pix(imageFileName);
			if (pix.width() > 999 || pix.height() > 999)
			{
				if (pix.width() > pix.height())
					pix.convertFromImage(pix.scaledToWidth(999).toImage());
				else
					pix.convertFromImage(pix.scaledToHeight(999).toImage());
			}
			QString fname = QFileInfo(mw->aviFileName).baseName() + "." + QString::number(stopklatkaNr++) + ".jpg";
			QString fpath = mw->workingPath + QDir::separator() + "temp" + QDir::separator() + fname;
			pix.save(fpath,"JPG");
			stopKlatkiAppend(fpath);
		}
	}
}

void NewsGroupBox::moveFoto(int move)
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


//TEXT EDITOR
void NewsGroupBox::on_textEdit_textChanged()
{
	return;
	QString htmlText = textEdit->toHtml();
	int start = htmlText.indexOf("<p",0,Qt::CaseInsensitive);
	htmlText = htmlText.remove(0,start);
	if (htmlText.contains("font-family"))
	{
		QRegExp rx("font-family:.(['a-zA-Z0-9 _.-])*;");
		rx.setMinimal(true);
		htmlText = htmlText.remove(rx);
		
		textEdit->blockSignals(true);
		textEdit->setText(htmlText);
		textEdit->blockSignals(false);
	}
}

void NewsGroupBox::textBold()
{
	QTextCharFormat fmt;
	fmt.setFontWeight(boldButton->isChecked() ? QFont::Bold : QFont::Normal);
	mergeFormatOnWordOrSelection(fmt);
}

void NewsGroupBox::textUnderline()
{
	QTextCharFormat fmt;
	fmt.setFontUnderline(underlineButton->isChecked());
	mergeFormatOnWordOrSelection(fmt);
}

void NewsGroupBox::textItalic()
{
	QTextCharFormat fmt;
	fmt.setFontItalic(italicButton->isChecked());
	mergeFormatOnWordOrSelection(fmt);
}

void NewsGroupBox::textSize(const QString &p)
{
	qreal pointSize = p.toFloat();
	if (p.toFloat() > 0) {
		QTextCharFormat fmt;
		fmt.setFontPointSize(pointSize);
		mergeFormatOnWordOrSelection(fmt);
	}
}

void NewsGroupBox::textStyle(int styleIndex)
{
	QTextCursor cursor = textEdit->textCursor();
	
	if (styleIndex != 0) {
		QTextListFormat::Style style = QTextListFormat::ListDisc;
		
		switch (styleIndex) {
		default:
		case 1:
			style = QTextListFormat::ListDisc;
			break;
		case 2:
			style = QTextListFormat::ListCircle;
			break;
		case 3:
			style = QTextListFormat::ListSquare;
			break;
		case 4:
			style = QTextListFormat::ListDecimal;
			break;
		case 5:
			style = QTextListFormat::ListLowerAlpha;
			break;
		case 6:
			style = QTextListFormat::ListUpperAlpha;
			break;
		case 7:
			style = QTextListFormat::ListLowerRoman;
			break;
		case 8:
			style = QTextListFormat::ListUpperRoman;
			break;
		}
		cursor.beginEditBlock();
		QTextBlockFormat blockFmt = cursor.blockFormat();
		QTextListFormat listFmt;
		if (cursor.currentList()) {
			listFmt = cursor.currentList()->format();
		} else {
			listFmt.setIndent(blockFmt.indent() + 1);
			blockFmt.setIndent(0);
			cursor.setBlockFormat(blockFmt);
		}
		listFmt.setStyle(style);
		cursor.createList(listFmt);
		cursor.endEditBlock();
	} else {
		// ####
		QTextList * list = cursor.currentList();
		if (list)
		{
			QTextBlock block = cursor.block();
			list->remove(block);
			QTextBlockFormat bfmt = cursor.blockFormat();
			bfmt.setObjectIndex(-1);
			bfmt.setIndent(0);
			cursor.mergeBlockFormat(bfmt);
		}
	}
}

void NewsGroupBox::textColor()
{
	QColor col = QColorDialog::getColor(textEdit->textColor(), this);
	if (!col.isValid())
		return;
	QTextCharFormat fmt;
	fmt.setForeground(col);
	mergeFormatOnWordOrSelection(fmt);
	colorChanged(col);
}

void NewsGroupBox::textAlignL()
{
	leftButton->setChecked(true);
	centerButton->setChecked(false);
	rightButton->setChecked(false);
	justifyButton->setChecked(false);
	textAlign(aLeft);
}

void NewsGroupBox::textAlignR(bool checked)
{
	if (!checked)
		textAlignL();
	else
	{
		leftButton->setChecked(false);
		centerButton->setChecked(false);
		justifyButton->setChecked(false);
		textAlign(aRight);
	}
}

void NewsGroupBox::textAlignC(bool checked)
{
	if (!checked)
		textAlignL();
	else
	{
		leftButton->setChecked(false);
		rightButton->setChecked(false);
		justifyButton->setChecked(false);
		textAlign(aCenter);
	}
}

void NewsGroupBox::textAlignJ(bool checked)
{
	if (!checked)
		textAlignL();
	else
	{
		leftButton->setChecked(false);
		centerButton->setChecked(false);
		rightButton->setChecked(false);
		textAlign(aJustified);
	}
}

void NewsGroupBox::textAlign(Align a)
{
	if (a == aLeft)
		textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
	else if (a == aCenter)
		textEdit->setAlignment(Qt::AlignHCenter);
	else if (a == aRight)
		textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
	else if (a == aJustified)
		textEdit->setAlignment(Qt::AlignJustify);
}

void NewsGroupBox::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = textEdit->textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	cursor.mergeCharFormat(format);
	textEdit->mergeCurrentCharFormat(format);
}

void NewsGroupBox::currentCharFormatChanged(const QTextCharFormat &format)
{
	fontChanged(format.font());
	colorChanged(format.foreground().color());
}

void NewsGroupBox::colorChanged(const QColor &c)
{
	QPixmap pix(16, 16);
	pix.fill(c);
	colorButton->setIcon(pix);
}
void NewsGroupBox::alignmentChanged(Qt::Alignment a)
{
	leftButton->setChecked(false);
	centerButton->setChecked(false);
	rightButton->setChecked(false);
	justifyButton->setChecked(false);
	if (a & Qt::AlignHCenter) {
		centerButton->setChecked(true);
	} else if (a & Qt::AlignRight) {
		rightButton->setChecked(true);
	} else if (a & Qt::AlignJustify) {
		justifyButton->setChecked(true);
	}
	else
		leftButton->setChecked(true);
}

void NewsGroupBox::fontChanged(const QFont &f)
{
	//	comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
	boldButton->setChecked(f.bold());
	italicButton->setChecked(f.italic());
	underlineButton->setChecked(f.underline());
}

void NewsGroupBox::cursorPositionChanged()
{
	alignmentChanged(textEdit->alignment());
	QTextCursor cursor = textEdit->textCursor();
	QTextList * list = cursor.currentList();
	if (list)
	{
		QTextListFormat format = list->format();
		int styleIndex = abs(format.style());
		if (styleIndex != 0) {
			comboStyle->setCurrentIndex(styleIndex);
			return;
		}
	}
	comboStyle->setCurrentIndex(0);
}

void NewsGroupBox::on_charTableButton_clicked()
{
	if (m_charTable == NULL)
	{
		m_charTable = new CharTable(this);
		connect(m_charTable, SIGNAL(rejected()), this, SLOT(closeCharTable()));
		connect(m_charTable,SIGNAL(pushText(QString)), this->textEdit, SLOT(insertPlainText(QString)));
		m_charTable->show();
	}
	else
	{
		m_charTable->hide();
		delete m_charTable;
		closeCharTable();
	}
}

void NewsGroupBox::closeCharTable()
{
	m_charTable = NULL;
	charTableButton->setChecked(false);
}

void NewsGroupBox::on_wideCheckBox_clicked(bool checked)
{
	mw->avi169 = checked;
}
