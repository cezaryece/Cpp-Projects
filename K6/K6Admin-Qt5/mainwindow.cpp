#include "listform.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QLocale>
#include <QMessageBox>
#include <QProcess>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>

#include "fileutils.h"
#include "newsgroupbox.h"
#include "programgroupbox.h"
#include "listform.h"
#include "videoform.h"
#include "searchgroupbox.h"

const QString rsrcPath = "images";

void queryError(QSqlQuery myQuery, QWidget* w) {
	QString bounded;
	QList<QVariant> list = myQuery.boundValues().values();
	for (int i = 0; i < list.size(); ++i)
		bounded.append(QString::number(i) + ": " + list.at(i).toString() + " ");
	QMessageBox::critical(w,QString::fromUtf8("Błąd operacji na bazie danych"), QString::fromUtf8("Niepowodzenie zapytania do bazy danych.\n") + myQuery.lastError().text() + "\n" + myQuery.lastQuery() + "\n" + bounded);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), currentGB(0), p(0), actionNewList(0), actionNewNews(0), actionNewProgram(0), actionSave(0), actionSearch(0),
	miastoIndex(0), aviConverted(false), avi169(true), aviFrames(-1), aviTime (-1.0), lastFoto(-1), lastNewsID(-1), lastProgID(-1), recordID(0), loginID(0), prawaID(0), katMenu(0),
	mp4PBar(0), ogvPBar(0), webmPBar(0),
	m_newsList(0), m_progList(0),
	escapeKeyPressed(false),
	actionCopy(0), actionCut(0), actionPaste(0), actionUndo(0), actionRedo(0)
{
#ifndef Q_OS_UNIX
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1250"));
//	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1250"));
#else
	QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));
//	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
#endif
	setupUi(this);
	workingPath = QDir::toNativeSeparators(QDir::current().absolutePath());
#ifndef QT_NO_CLIPBOARD
	//	connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
#endif
	
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
#ifndef Q_OS_UNIX
#ifndef QT_DEBUG
	//updates
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
#endif
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT define FROM prawa ORDER BY id ASC"))
	{
		while (myQuery.next())
			listaPraw << myQuery.value(0).toString();
	}
	else
		queryError(myQuery,this);
#ifdef QT_DEBUG
	loginID = 2;
	prawaID = 1;
#else
	LoginDialog* loginDialog = new LoginDialog( this );
	while (loginID == 0)
	{
		int res = loginDialog->exec();
		if (res == QDialog::Rejected)
			exit(0);
	}
	
#endif
	setupActions();
	QSqlQuery kategorieQuery;
	if (kategorieQuery.exec("SELECT * FROM kategorie ORDER BY kategoria ASC"))
	{
		while (kategorieQuery.next())
			kategorieMap.insert(kategorieQuery.value(1).toString(),kategorieQuery.value(0).toInt());
		katMenu = new QMenu;
		foreach (QString kategoria, kategorieMap.keys())
		{
			QAction* action = new QAction(kategoria, katMenu);
			action->setCheckable(true);
			action->setData(kategorieMap.value(kategoria));
			katMenu->addAction(action);
		}
	}
	else
		queryError(kategorieQuery,this);
	
	programyURL = "ftp://oferuje.pl/video/programy/";
	newsyURL = "ftp://oferuje.pl/video/newsy/";
	galerieURL = "ftp://kanal6.pl/galerieK6/";
	fotoURL = "ftp://kanal6.pl/fotkiK6/";
	lastDir = QDir::homePath();
	connect(&u, SIGNAL(sendLog(QString,bool)), this, SLOT(printLog(QString,bool)));
	
	newListForm();
}

bool MainWindow::sprawdzPrawa(QStringList prawaList, uint prawaID)
{
	foreach(QString prawo, prawaList)
	{
		if (sprawdzPrawo(prawo, prawaID))
			return true;
	}
	db.close();
	return false;
}

bool MainWindow::sprawdzPrawo(QString prawoStr, uint prawaID)
{
	int bit = listaPraw.indexOf(prawoStr);
	if (bit < 0)
		return false;
	int pow2 = pow(2,bit);
	return (prawaID & pow2);
}

void MainWindow::setupActions()
{
	QAction *a;
	a = actionNewList = new QAction(QIcon(rsrcPath + "/new_news.png"), "Lista", this);
	connect(a, SIGNAL(triggered()), this, SLOT(newListForm()));
	tb->addAction(a);
	if (sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "_k6_news_all" <<  "_k6_news_user", prawaID))
	{
		a = actionNewNews = new QAction(QIcon(rsrcPath + "/new_news.png"), "Nowy News", this);
		connect(a, SIGNAL(triggered()), this, SLOT(newNews()));
		tb->addAction(a);
	}
	if (sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "_k6_news_all" <<  "_k6prog_edit" << "k6_flv", prawaID))
	{
		a = actionNewProgram = new QAction(QIcon(rsrcPath + "/avi.png"), "Nowy Program", this);
		connect(a, SIGNAL(triggered()), this, SLOT(newProgram()));
		tb->addAction(a);
	}
	a = actionSearch = new QAction(QIcon(rsrcPath + "/new_news.png"), "Szukaj", this);
	connect(a, SIGNAL(triggered()), this, SLOT(newSearchForm()));
	tb->addAction(a);
	
	a = actionSave = new QAction(QIcon(rsrcPath + "/filesave.png"), "Zapisz i zamknij", this);
	connect(a, SIGNAL(triggered()), this, SLOT(save()));
	actionSave->setEnabled(false);
	tb->addAction(a);
	a = actionUndo = new QAction(QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png")), tr("&Undo"), this);
	a->setShortcut(QKeySequence::Undo);
	//	tb->addAction(a);
	a = actionRedo = new QAction(QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png")), tr("&Redo"), this);
	a->setPriority(QAction::LowPriority);
	a->setShortcut(QKeySequence::Redo);
	//	tb->addAction(a);
	a = actionCut = new QAction(QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png")), tr("Wytnij"), this);
	a->setPriority(QAction::LowPriority);
	a->setShortcut(QKeySequence::Cut);
	//	tb->addAction(a);
	a = actionCopy = new QAction(QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png")), tr("Kopiuj"), this);
	a->setPriority(QAction::LowPriority);
	a->setShortcut(QKeySequence::Copy);
	//	tb->addAction(a);
	a = actionPaste = new QAction(QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png")), tr("Wklej"), this);
	a->setPriority(QAction::LowPriority);
	a->setShortcut(QKeySequence::Paste);
	//	tb->addAction(a);
#ifndef QT_NO_CLIPBOARD
	if (const QMimeData *md = QApplication::clipboard()->mimeData()) actionPaste->setEnabled(md->hasText());
#endif
}

bool MainWindow::potwierdzDlg()
{
	int ret = QMessageBox::warning(this,QString::fromUtf8("Możliwa utrata danych"), QString::fromUtf8("Dane wprowadzone w tym formularzu nie były zapisane\n i mogą być utracone. Mimo to zamknąć formularz?"), QMessageBox::Yes, QMessageBox::No);
	return (ret == QMessageBox::Yes);
}

void MainWindow::cleanTemp()
{
	QDir curDir(workingPath);
	QString temp = curDir.absolutePath() + QDir::separator() + "temp" + QDir::separator();
	FileUtils::removeDir(temp);
	curDir.mkpath("temp");
	fileName.clear();
	aviFileName.clear();
	aviConverted = false;
	recordID = 0;
}

void MainWindow::newListForm(focused what)
{
	if ((what != none || m_newsHeaderState.isEmpty()) && m_newsList != NULL)
	{
		m_newsHeaderState = m_newsList->horizontalHeader()->saveState();
		m_progHeaderState = m_progList->horizontalHeader()->saveState();
	}
	if (currentGB)
	{
		if (!potwierdzDlg())
			return;
		disconnect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	}
	currentGB = NULL;
	ListForm* lf = new ListForm(this, what);
	setCentralWidget(lf);
	connect(lf, SIGNAL(dodajFilm4News(int)), this, SLOT(addVideo(int)));
	connect(lf, SIGNAL(editNews(int)), this, SLOT(editNews(int)));
	connect(lf, SIGNAL(editProg(int)), this, SLOT(editProgram(int)));
	actionNewList->setEnabled(false);
}

void MainWindow::newSearchForm()
{
	if (currentGB)
	{
		if (!potwierdzDlg())
			return;
		disconnect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	}
	currentGB = NULL;
	SearchGroupBox* sgb = new SearchGroupBox(this);
	setCentralWidget(sgb);
	actionNewList->setEnabled(true);
	actionNewNews->setEnabled(true);
	actionNewProgram->setEnabled(true);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
		escapeKeyPressed = true;
}

void MainWindow::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
	if (const QMimeData *md = QApplication::clipboard()->mimeData())
		actionPaste->setEnabled(md->hasText());
#endif
}

News MainWindow::getNewsFromDB(int newsID)
{
	News inf;
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT * FROM K6_archiwum WHERE id=" + QString::number(newsID)))
	{
		myQuery.first();
		inf.id = newsID;
		inf.data = myQuery.value(1).toString();
		inf.expire = myQuery.value(2).toString();
		inf.wazny = myQuery.value(3).toBool();
		inf.lastminute = myQuery.value(4).toBool();
		inf.userID = myQuery.value(5).toInt();
		inf.acceptID = myQuery.value(6).toInt();
		QString kategorie = myQuery.value(7).toString();
		QStringList katList = kategorie.split(":",QString::SkipEmptyParts);
		foreach (QString kat, katList)
			inf.katID.append(kat.toInt());
		inf.film = myQuery.value(9).toBool();
		inf.avipath = myQuery.value(10).toString();
		inf.impreza = myQuery.value(12).toBool();
		inf.patronat = myQuery.value(13).toBool();
		inf.impreza_data = myQuery.value(14).toString();
		inf.impreza_nazwa = myQuery.value(15).toString();
		inf.miasto = myQuery.value(16).toString();
		inf.tytul = myQuery.value(17).toString();
		inf.text = myQuery.value(18).toString();
		inf.podpis = myQuery.value(19).toString();
	}
	else
		queryError(myQuery,this);
	
	return inf;
}

Prog MainWindow::getProgFromDB(int id)
{
	Prog program;
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT * FROM video WHERE id=" + QString::number(id)))
	{
		myQuery.first();
		program.id = id;
		program.tytul = myQuery.value(1).toString();
		program.opis = myQuery.value(2).toString();
		program.zablokowany = myQuery.value(3).toBool();
		program.cyklID = myQuery.value(4).toInt();
		QString kategorie = myQuery.value(5).toString();
		QStringList katList = kategorie.split(":",QString::SkipEmptyParts);
		foreach (QString kat, katList)
			program.katID.append(kat.toInt());
		program.czas = myQuery.value(6).toString();
		program.oryginal = myQuery.value(7).toString();
	}
	else
		QMessageBox::critical(this,QString::fromUtf8("Błąd odczytu programu z bazy danych"), QString::fromUtf8("Odczyt danych się nie powiódł.\n") + myQuery.lastError().text() + "\n" + myQuery.lastQuery());
	
	return program;
	
}

void MainWindow::newNews()
{
	clearTablesPointers();
	
	if (currentGB)
	{
		if (!potwierdzDlg())
			return;
		disconnect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	}
	
	currentGB = new NewsGroupBox(this);
	setCentralWidget(currentGB);
	repaint();
	recordID = 0;
	cleanTemp();
	connect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	connect(currentGB,SIGNAL(finished()), this, SLOT(koniec()));
	lastProgID = -1;
	actionNewList->setEnabled(true);
}

void MainWindow::editNews(int id)
{
	clearTablesPointers();
	
	News news = getNewsFromDB(id);
	currentGB = new NewsGroupBox(this,news);
	setCentralWidget(currentGB);
	repaint();
	recordID = id;
	cleanTemp();
	connect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	connect(currentGB,SIGNAL(finished()), this, SLOT(koniec()));
	actionNewList->setEnabled(true);
}

void MainWindow::newProgram()
{
	clearTablesPointers();
	
	if (currentGB)
	{
		if (!potwierdzDlg())
			return;
		disconnect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	}
	currentGB = new ProgramGroupBox(this);
	setCentralWidget(currentGB);
	recordID = 0;
	cleanTemp();
	connect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	connect(currentGB,SIGNAL(finished()), this, SLOT(koniec()));
	actionNewList->setEnabled(true);
}

void MainWindow::editProgram(int id)
{
	clearTablesPointers();
	
	Prog program = getProgFromDB(id);
	currentGB = new ProgramGroupBox(this,program);
	setCentralWidget(currentGB);
	repaint();
	recordID = id;
	cleanTemp();
	connect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	connect(currentGB,SIGNAL(finished()), this, SLOT(koniec()));
	actionNewList->setEnabled(true);
}

void MainWindow::addVideo(int newsID)
{
	VideoForm * vf = new VideoForm(this);
	vf->setNewsId(newsID);
	currentGB = vf;
	cleanTemp();
	setCentralWidget(currentGB);
	connect(&u, SIGNAL(uploadFinish(int)), currentGB, SLOT(ftpFinished(int)));
	connect(currentGB,SIGNAL(finished()), this, SLOT(koniec()));
	actionNewList->setEnabled(true);
}

void MainWindow::save()
{
	Q_ASSERT(currentGB != NULL);
	
	actionSave->setEnabled(false);
	actionNewNews->setEnabled(false);
	actionNewProgram->setEnabled(false);
	actionNewList->setEnabled(false);
	if (!currentGB->save())
	{
		actionSave->setEnabled(true);
		actionNewNews->setEnabled(true);
		actionNewProgram->setEnabled(true);
		actionNewList->setEnabled(true);
	}
}

void MainWindow::koniec()
{
	currentGB = NULL;
	actionNewNews->setEnabled(true);
	actionNewProgram->setEnabled(true);
	actionNewList->setEnabled(true);
	newListForm();
	cleanTemp();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (currentGB && QMessageBox::warning(this,QString::fromUtf8("Możliwa utrata danych"), QString::fromUtf8("Dane wprowadzone w formularzu nie były zapisane\n i zostaną utracone po zamknięciu programu. Mimo to zamknąć program?"), QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
		event->ignore();
	else
		event->accept();
}

void MainWindow::convertVideos()
{
	currentGB->converting = true;
	fileName = aviFileName;
	QFileInfo fi(fileName);
	QString fname = fi.baseName();
	
	Q_ASSERT(p == NULL);
	p = new QProcess( this );
	Q_ASSERT(p != NULL);
	
	actionNewNews->setEnabled(false);
	actionNewProgram->setEnabled(false);
	currentGB->openAVI->setEnabled(false);
	
	p->setEnvironment( QProcess::systemEnvironment() );
	p->setProcessChannelMode( QProcess::MergedChannels );
	connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
	connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
	connect(p, SIGNAL(finished(int)), this, SLOT(processExit(int)));
	QString fpath = workingPath + QDir::separator() + "temp" + QDir::separator() + fname;
	QString resize = avi169 ? "400x226" : "400x320";
	QString cmdLine = "ffmpeg -i \"" + fileName +"\" -vcodec libx264 -preset slower -threads 4 -deinterlace -b:v 300k -bufsize 1835k -s " + resize + " -acodec libvo_aacenc -b:a 64k -y -f mp4 -r 16 \""+ fpath + ".mp4\"";
	currentGB->mp4L->setText(QString :: fromUtf8("MP4 - robię"));
	currentGB->mp4L->setStyleSheet("QLabel {color:red;}");
	fileName = fpath + ".mp4";
	p->start( cmdLine );
}

void MainWindow::breakConvertion()
{
	Q_ASSERT(p != NULL);
	disconnect(p, SIGNAL(finished(int)), this, SLOT(processExit(int)));
	p->kill();
	p->deleteLater();
	p = NULL;
	currentGB->converting = false;
	resetProgress();
}

QString MainWindow::createThumb(QString fN)
{
	QFileInfo fi(fN);
	QString fname = fi.baseName() + ".thb";
	QString fpath = workingPath + QDir::separator() + "temp" + QDir::separator() + fname;
	QFile file(fpath);
	if (file.open(QIODevice::WriteOnly))
	{	
		QPixmap pix (fN);
		QPixmap pix2 =  pix.scaled(180,144, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		pix2.save(fpath,"JPG");
		return fpath;
	}
	return QString("");
}

void MainWindow::parseLog(QString log)
{
	log = log.simplified();
	if (log.isEmpty())
		return;
	if (fileName.right(3) == "ogv")
	{
		if (log.length() >4 && log.at(1) == ':' && log.at(4) == ':')
		{
			Q_ASSERT(aviTime > 0);
			int audioPos = log.indexOf("audio:");
			QString timeStr = log.left(audioPos -1).trimmed();
			QTime time = QTime::fromString(timeStr,"h:mm:ss.z");
			double currTime = time.hour() * 3600 *1000;
			currTime += time.minute() * 60;
			currTime += time.second();
			currTime += time.msec()/1000;
			int progress = currTime * 100 / aviTime;
			ogvPBar->setValue(progress);
		}
	}
	else
	{
		if (!log.startsWith("frame="))
			return;
		Q_ASSERT(aviFrames > 0);
		int fpsPos = log.indexOf("fps=");
		QString frameNumber = log.mid(6,fpsPos -7).trimmed();
		int progress = frameNumber.toInt() * 100 / aviFrames;
		if (fileName.right(3) == "mp4")
			mp4PBar->setValue(progress);
		else
			webmPBar->setValue(progress);
	}
}

void MainWindow::clearTablesPointers()
{
	if (m_newsList)
		m_newsList = NULL;
	if (m_progList )
		m_progList = NULL;
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

void MainWindow::resetProgress()
{
	mp4PBar->reset();
	ogvPBar->reset();
	webmPBar->reset();
}

void MainWindow::ReadOut()
{
	Q_ASSERT(p != NULL);
	
	QString log = p->readAllStandardOutput();
	currentGB->con->append(log);
	parseLog(log);
}
void MainWindow::ReadErr()
{
	if (p)
		currentGB->con->append( p->readAllStandardError() );
}

void MainWindow::processExit(int res)
{
	if (p == NULL)
		return;
	if (res != 0)
	{
		currentGB->con->append("Błąd konwertowania pliku " + fileName);
		actionNewNews->setEnabled(true);
		actionNewProgram->setEnabled(true);
		actionNewList->setEnabled(true);
		currentGB->openAVI->setEnabled(true);
	}
	else
	{
		if (fileName.right(3) == "mp4")
		{
			if (mp4PBar)
				mp4PBar->setValue(100);
			currentGB->mp4L->setText("MP4 - zrobiony");
			currentGB->mp4L->setStyleSheet("QLabel {color:green;}");
			currentGB->ogvL->setText(QString :: fromUtf8("OGV - robię"));
			currentGB->ogvL->setStyleSheet("QLabel {color:red;}");
			fileName = fileName.replace(".mp4", "");
			QString cmdLine = "ffmpeg2theora -v 6 -a 1 -o \"" + fileName +".ogv\" \"" + fileName + ".mp4\"";
			currentGB->con->append("\n ************** ffmpeg2theora \n" + cmdLine);
			fileName.append(".ogv");
			p->start( cmdLine );
		}
		else if (fileName.right(3) == "ogv")
		{
			if (ogvPBar)
				ogvPBar->setValue(100);
			currentGB->ogvL->setText("OGV - zrobiony");
			currentGB->ogvL->setStyleSheet("QLabel {color:green;}");
			currentGB->webmL->setText(QString :: fromUtf8("WEBM - robię"));
			currentGB->webmL->setStyleSheet("QLabel {color:red;}");
			fileName = fileName.replace(".ogv", "");
			QString cmdLine("ffmpeg -i \"" + fileName + ".mp4\" -vcodec libvpx -preset slow -threads 2 -bufsize 1835k -b:v 300k -acodec libvorbis -y \""+ fileName + ".webm\"");
			currentGB->con->append("\n ************** ffmpeg WEBM\n" + cmdLine);
			fileName.append(".webm");
			p->start( cmdLine );
		}
		else if ((fileName.right(4) == "webm"))
		{
			if (webmPBar)
				webmPBar->setValue(100);
			currentGB->webmL->setText("WEBM - zrobiony");
			currentGB->webmL->setStyleSheet("QLabel {color:green;}");
			currentGB->con->append("\n\n ________________________________\nPliki przygotowane!");
			fileName = fileName.replace(".webm","");
			p->deleteLater();
			p = NULL;
			aviConverted = true;
			currentGB->openAVI->setEnabled(true);
			currentGB->convertAVI->setEnabled(false);
			currentGB->convertAVI->setStyleSheet("QPushButton { color: black; }");
			currentGB->convertAVI->setText("Konwertuj video");
			actionSave->setEnabled(currentGB->walidacja());
			actionNewNews->setEnabled(true);
			actionNewProgram->setEnabled(true);
			actionNewList->setEnabled(true);
			currentGB->openAVI->setEnabled(true);
			currentGB->converting = false;
		}
	}
}

void MainWindow::printLog(QString str, bool onlyDebug)
{
	if (!onlyDebug)
		currentGB->con->append(str);
	qDebug() << str;
}


void queryError(QString where, QSqlQuery &query)
{
	qDebug() << "blad SQL " << where;
	qDebug() << query.lastQuery() << endl << query.lastError().databaseText() << " / " << query.lastError().driverText();
}
