#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chartable.h"
#include "uploader.h"
#include "ui_mainwindow.h"
#include "gbbase.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>
#include <QMenu>
#include <QMessageBox>
#include <QProgressBar>
#include <QTableWidget>
#include "videoplayer.h"

class QGroupBox;

enum focused { none, news, prog };

void queryError(QString where, QSqlQuery &query);

struct News {
	int id;
	QString data, expire;
	bool wazny, lastminute;
	int userID, acceptID;
	QList<int> katID;
	bool film, impreza, patronat;
	QString avipath;
	QString impreza_data, impreza_nazwa;
	QString miasto, tytul, text, podpis, fotka_opis;
};
struct Prog {
	int id;
	QString tytul, opis;
	bool wide;
	bool zablokowany;
	int cyklID;
	QString cyklTytul;
	QList<int> katID;
	QString czas, oryginal;
};

void queryError(QSqlQuery myQuery, QWidget* w);

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow()
	{
		if (katMenu)
			delete katMenu;
		if(db.isOpen())
			db.close();
	}
	
	GbBase * currentGB;
	QProcess *p;
	QAction *actionNewList, *actionNewNews, *actionNewProgram, *actionSave, *actionSearch;
	QString fileName, aviFileName;
	QString workingPath;
	Uploader u;
	QSqlDatabase db;
	QString programyURL, newsyURL, galerieURL, fotoURL, lastDir;
	QMap<QString,int> kategorieMap;
	int miastoIndex;
	bool aviConverted;
	bool avi169;
	int aviFrames;
	double aviTime;
	int lastFoto;
	int lastNewsID, lastProgID;
	int recordID;
	int loginID;
	uint prawaID;
	
	QStringList listaPraw;
	bool sprawdzPrawa(QStringList prawaList, uint prawaID);
	bool sprawdzPrawo(QString prawoStr, uint prawaID);
	
	void convertVideos();
	void breakConvertion();
	void resetProgress();
	QString createThumb(QString fileName);
	QMenu * katMenu;
	QProgressBar *mp4PBar, *ogvPBar, *webmPBar;
	QTableWidget * m_newsList, * m_progList;
	QByteArray m_newsHeaderState, m_progHeaderState;
	bool escapeKeyPressed;
	VideoPlayer vp;
private:
	News getNewsFromDB(int);
	Prog getProgFromDB(int);
	void closeEvent(QCloseEvent *event);
	void setupActions();
	QAction *actionCopy, *actionCut, *actionPaste, *actionUndo, *actionRedo;
	bool potwierdzDlg();
	void cleanTemp();
	void keyReleaseEvent(QKeyEvent *) { if (currentGB) actionSave->setEnabled(currentGB->walidacja()); }
	void mouseReleaseEvent(QMouseEvent *) { if (currentGB) actionSave->setEnabled(currentGB->walidacja()); }
	void parseLog(QString);
	void clearTablesPointers();
	int checkForUpdates();
private slots:
	void ReadOut();
	void ReadErr();
	void processExit(int);
	void printLog(QString, bool);
	void clipboardDataChanged();
	void newNews();
	void editNews(int);
	void newProgram();
	void editProgram(int);
	void addVideo(int);
	void save();
	void koniec();
public slots:
	void newListForm(focused what=none);
	void newSearchForm();
	virtual void keyPressEvent(QKeyEvent *e);
	
};

#endif // MAINWINDOW_H
