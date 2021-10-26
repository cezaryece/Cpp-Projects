#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>
#include <QMessageBox>
#include <QKeyEvent>

typedef enum {
	anyWord,
	allWords,
	exactSentence
} searchwords;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	void keyPressEvent(QKeyEvent *e);

private slots:
	void on_anyRadio_toggled(bool checked);
	void on_allRadio_toggled(bool checked);
	void on_exactRadio_toggled(bool checked);
	void on_allfilesRadio_toggled(bool checked);
	void on_videoCheckBox_clicked(bool checked);
	void on_audioCheckBox_clicked(bool checked);
	void on_textCheckBox_clicked(bool checked);
	void on_fotoCheckBox_clicked(bool checked);
	void on_dirCheckBox_clicked(bool checked);
	void on_SzukajButton_clicked();
	void on_customCheckBox_clicked(bool checked);
	void on_txtCheckBox_clicked(bool checked);
	void on_allfilesRadio_clicked(bool checked);
	
private:
	searchwords swords;
	bool searchAll;
	bool videoFiles;
	bool audioFiles;
	bool textFiles;
	bool fotoFiles;
	bool searchDirs;
	bool customFiles;
	bool searchInTxt;
	bool escapeKeyPressed;
	QString customExtension;
	
	QSqlDatabase db, fdDB;
	
	
	bool checkFilesFilter();
	QString getDirName(long long dirID);
	void queryError(QString where, QSqlQuery &query);
};

#endif // MAINWINDOW_H
