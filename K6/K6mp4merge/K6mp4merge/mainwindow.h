#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QDir>
#include <QProcess>
#include <QtSql/QSqlDatabase>

//const qint64 maxSize = 300 * 1024 * 1024;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
private:
	QDir currDir;
	QString destDirName;
	QStringList mp4Files;
	QString ffmpegExec;
	QProcess *p;
	void endProcess(QString);
	QList<QPair<QFileInfo,bool> > listaPlikow;
	QFileInfo getSelectedFile();
	void showPlikPreview();
	void updatePlikiListWidget();
	void updateCurrDir();
	int currRow;
	qint64 selectedSize;
	QSqlDatabase db;
	
	int checkForUpdates();
private slots:
	void plikToggle(bool);
	void on_wybierzButton_clicked();
	void on_polaczButton_clicked();
	void on_plikLineEdit_textChanged(const QString &arg1);
	void ReadOut();
	void ReadErr();
	void processExit(int);
	void setVideo(QString fileName);
	
	void on_plikiLista_itemClicked(QTableWidgetItem *item);
	void on_startButton_clicked();
	void on_allButton_clicked();
	void on_noneButton_clicked();
	void on_moveButton_clicked();
	void on_innyCheckBox_toggled(bool checked);
	void on_innyButton_clicked();
};

#endif // MAINWINDOW_H
