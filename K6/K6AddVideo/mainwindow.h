#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtSql/QSqlQuery>
#include <QTableWidgetItem>

struct Info {
	int id;
	QString data, tytul, miasto;
};
void queryError(QSqlQuery myQuery, QWidget* w);

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	
protected:
	QString lastDir;
	void changeEvent(QEvent *e);
	void updateInfoList();
	QList<Info> getInfoFromDB();
    int checkForUpdates();
private slots:
	void on_infoList_itemDoubleClicked(QTableWidgetItem *item);
};

#endif // MAINWINDOW_H
