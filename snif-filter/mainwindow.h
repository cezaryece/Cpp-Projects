#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QList>
#include <QFile>
#include <QString>

struct __attribute__ ((__packed__)) datapacket {
	unsigned char       godzina;
	unsigned char       minuta;
	unsigned char       sekunda;
	unsigned char       proto;
	unsigned int        ip_s;
	unsigned short int  port_s;
	unsigned int        ip_d;
	unsigned short int  port_d;
};

struct filterData {
	QList< QList<uint> > sIP, dIP;
	QList<ushort> sPort, dPort;
};


class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
private:
	Ui::MainWindow ui;
	ulong numRecords, curRecord, start, max, found;
	datapacket dp;
	QList<datapacket> dpList;
	QFile dumpFile;
	QString filename;
	bool isFilter;
	short h,m,s;
	
	
	//metody
	void LoadDumpFile();
	QString dp2string(datapacket*);
	void readDump(ulong &licznik);
	bool filter(const datapacket*,const filterData&,bool&);
	
	filterData getFilterData();
private slots:
	void on_actionQuit_triggered();
	void on_pushButton_PRINT_clicked();
	void on_pushButton_NEXT_clicked();
	void on_pushButton_PREV_clicked();
	void on_pushButton_apply_clicked();
	void on_pushButton_loadDF_clicked();
	void on_actionLoad_Dump_File_triggered();
};

#endif // MAINWINDOW_H
