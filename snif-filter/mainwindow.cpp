#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QStringList>
#include <QHostInfo>
#include <QHostAddress>
#include <netinet/in.h> //ntohs
#include <QDebug>

#include <iostream>

QString int2IP(uint i) {
	uchar ch[5];
	memcpy(ch,&i,4);
	return (QString::number(ch[0]) + "." +QString::number(ch[1]) + "." +QString::number(ch[2]) + "." +QString::number(ch[3]));
}

QString host2IP(QString host) {
	bool isIP = true;
	for(int i=0; i < host.length(); i++) {
		if (host.at(i) == '.') continue;
		else if (!host.at(i).isDigit()) {
			isIP = false;
			break;
		}
	}
	if (!isIP) {
		QHostInfo info = QHostInfo::fromName(host);
		if (info.error() == QHostInfo::NoError) {
			QHostAddress address = info.addresses().first();
			std::cout << address.toString().toStdString().c_str() << std::endl;
			return(address.toString());
		}
		else return info.errorString();
	}
	else return host;
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), max(1000){
	ui.setupUi(this);
	isFilter = false;
}

void MainWindow::LoadDumpFile() {
	ulong licznik = 1;
	start = 1;
	curRecord = 1;
	
	ui.statusBar->clearMessage();
	ui.textBrowser->clear();
	if (dumpFile.isOpen())
		dumpFile.close();
	filename = QFileDialog::getOpenFileName(this,"Choose a dump file to open",QString::null,QString::null,0,QFileDialog::DontUseNativeDialog);
	dumpFile.setFileName(filename);
	if (!dumpFile.open(QIODevice::ReadOnly)) {
		ui.statusBar->showMessage("Błąd ładowania pliku");
		return;
	}
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	ui.label_DUMPFILE->setText(QFileInfo(filename).fileName());
	numRecords = dumpFile.size() / 16;
	ui.label_REC->setText(QString::number(numRecords));
	readDump(licznik);
	
	ui.statusBar->showMessage("Rekordy: " + QString::number(start) + " - " + QString::number(curRecord));
	ui.pushButton_PREV->setEnabled(false);
	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::on_actionLoad_Dump_File_triggered() {
	LoadDumpFile();
}

void MainWindow::on_pushButton_loadDF_clicked() {
	LoadDumpFile();
}

void MainWindow::on_pushButton_apply_clicked() {
	QStringList sL;
	
	isFilter = false;
	max = 1000;
	
	ui.textBrowser->clear();
	ui.textBrowser->update();
	this->update();
	
	h = m = s = -1;
	if (ui.lineEdit_gms->text() != "") {
		sL = ui.lineEdit_gms->text().split(":");
		if ((sL.at(0).toUShort() > 23) ||
				(sL.size() > 1 && sL.at(1).toUShort() > 59) ||
				(sL.size() > 2 && sL.at(2).toUShort() > 59))
			ui.lineEdit_gms->setText("");
		else
		{
			isFilter = true;
			h = sL.at(0).toShort();
			if (sL.size() > 1)
				m = sL.at(1).toShort();
			if (sL.size() > 2)
				s = sL.at(2).toShort();
		}
	}
	if (!isFilter)
	{
		if (ui.lineEdit_sIP->text().trimmed() != "")
			isFilter = true;
		else if (ui.lineEdit_sport->text().trimmed() != "")
			isFilter = true;
		else if (ui.lineEdit_dIP->text().trimmed() != "")
			isFilter = true;
		else if (ui.lineEdit_dport->text().trimmed() != "")
			isFilter = true;
	}
	
	if (isFilter) {
		max = 100;
		found = 0;
		on_pushButton_PREV_clicked();
	}
}

void MainWindow::on_pushButton_PREV_clicked() {
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	
	ulong licznik = 1;
	start = 1;
	found = 0;
	ui.textBrowser->clear();
	ui.textBrowser->update();
	this->update();
	
	dumpFile.seek(0);
	readDump(licznik);
	
	ui.statusBar->clearMessage();
	ui.statusBar->showMessage("Rekordy: " + QString::number(start) + " - " + QString::number(start + licznik -1));
	ui.pushButton_PREV->setEnabled(false);
	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
	
}

void MainWindow::on_pushButton_NEXT_clicked() {
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	
	ulong licznik = 1;
	
	ui.textBrowser->clear();
	
	readDump(licznik);
	
	ui.statusBar->clearMessage();
	ui.statusBar->showMessage("Rekordy: " + QString::number(found) + " - " + QString::number(found + licznik -1));
	ui.pushButton_PREV->setEnabled(true);
	found =+ licznik -1;
	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::on_pushButton_PRINT_clicked()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	max = numRecords = dumpFile.size() / 16;
	QString outputFilename = dumpFile.fileName() + ".txt";
	QFile outputFile(outputFilename);
	outputFile.open(QIODevice::WriteOnly);
	/* Check it opened OK */
	if(!outputFile.isOpen()){
		qDebug() << "Error, unable to open" << outputFilename << "for output";
		return;
	}
	filterData fD = getFilterData();
	QTextStream outStream(&outputFile);
	dumpFile.seek(0);
	while(!dumpFile.atEnd()) {
		dumpFile.read((char*)&dp,16);
		//curRecord++;
		//ui.progressBar->setValue(curRecord);
		if (isFilter) {
			bool stop = false;
			if (filter(&dp, fD, stop)) {
				outStream << dp2string(&dp) << endl;
			}
			if (stop)
				break;
		}
		else {
			outStream << dp2string(&dp);
		}
	}
	outputFile.close();
	QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::on_actionQuit_triggered() {
	exit(0);
}

QString MainWindow::dp2string(datapacket *dp) {
	return (QString::number(dp->godzina).rightJustified(2,'0') + ":" + QString::number(dp->minuta).rightJustified(2,'0') + ":" + QString::number(dp->sekunda).rightJustified(2,'0') + " "
			+ QString::number(dp->proto) + " "
			+ int2IP(dp->ip_s) + ":" + QString::number(ntohs(dp->port_s)) + " "
			+ int2IP(dp->ip_d) + ":" + QString::number(ntohs(dp->port_d)));
}

void MainWindow::readDump(ulong &licznik) {

	filterData fData = getFilterData();
	while(!dumpFile.atEnd()) {
		dumpFile.read((char*)&dp,16);
		//curRecord++;
		//ui.progressBar->setValue(curRecord);
		//        std::cout << QString::number(numDP).toStdString().c_str() << std::endl;
		if (isFilter) {
			bool stop = false;
			if (filter(&dp, fData, stop)) {
				ui.textBrowser->append(QString::number(start + licznik - 1) + " " + dp2string(&dp));
				if (licznik == max) return;
				licznik++;
			}
			if (stop)
				return;
		}
		else {
			ui.textBrowser->append(QString::number(start + licznik - 1) + " " + dp2string(&dp));
			if (licznik == max) return;
			licznik++;
		}
	}
	//    ui.progressBar->reset();
}

filterData MainWindow::getFilterData()
{
	filterData fData;
	QString str;
	str = ui.lineEdit_sIP->text().remove(' ');
	if (str != "")
	{
		QStringList strList = str.split(',');
		foreach(QString ip, strList)
		{
			QList<uint> ipnums;
			QStringList ipstr = ip.split('.');
			foreach(QString seg, ipstr)
				ipnums.append(seg.toUInt());
			fData.sIP.append(ipnums);
		}
	}
	str = ui.lineEdit_dIP->text().remove(' ');
	if (str != "")
	{
		QStringList strList = str.split(',');
		foreach(QString ip, strList)
		{
			QList<uint> ipnums;
			QStringList ipstr = ip.split('.');
			foreach(QString seg, ipstr)
				ipnums.append(seg.toUInt());
			fData.dIP.append(ipnums);
		}
	}
	str = ui.lineEdit_sport->text().remove(' ');
	if (str != "")
	{
		QStringList strList = str.split(',');
		foreach (QString port, strList)
		{
			if (port.contains('-'))
			{
				QStringList ports = port.split('-');
				uint start = ports.at(0).toUInt();
				if (start == 0)
					continue;
				uint stop = ports.at(1).toUInt();
				if (stop > start)
				{
					for (uint i=start; i <=stop; ++i)
						fData.sPort.append(i);
				}
			}
			else
			{
				uint p = port.toUInt();
				if (p != 0)
					fData.sPort.append(p);
			}
		}
	}
	str = ui.lineEdit_dport->text().remove(' ');
	if (str != "")
	{
		QStringList strList = str.split(',');
		foreach (QString port, strList)
		{
			if (port.contains('-'))
			{
				QStringList ports = port.split('-');
				uint start = ports.at(0).toUInt();
				if (start == 0)
					continue;
				uint stop = ports.at(1).toUInt();
				if (stop > start)
				{
					for (uint i=start; i <=stop; ++i)
						fData.dPort.append(i);
				}
			}
			else
			{
				uint p = port.toUInt();
				if (p != 0)
					fData.dPort.append(p);
			}
		}
	}
	return fData;
}

bool MainWindow::filter(const datapacket * dp, const filterData &fData, bool &stop) {
	uchar IP[5];
	if (h>=0) {
		if (h != (short)dp->godzina)
		{
			if (h < (short)dp->godzina)
				stop = true;
			return false;
		}
		if (m >= 0 && m != (short)dp->minuta)
		{
			if (m < (short)dp->minuta)
				stop = true;
			return false;
		}
		if (s >= 0 && s != (short)dp->sekunda)
		{
			if (s < (short)dp->sekunda)
				stop = true;
			return false;
		}
	}
	if (!fData.sIP.isEmpty()) {
		memcpy(IP,&dp->ip_s,4);
		bool found = false;
		foreach(QList<uint> ipnums, fData.sIP)
		{
			bool ipOK = true;
			for (int i=0; i < 4; i++)
			{
				if (ipnums.at(i) != (uint) IP[i])
				{
					ipOK = false;
					break;
				}
			}
			if (ipOK)
			{
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}
	if (!fData.dIP.isEmpty()) {
		memcpy(IP,&dp->ip_d,4);
		bool found = false;
		foreach(QList<uint> ipnums, fData.dIP)
		{
			bool ipOK = true;
			for (int i=0; i < 4; i++)
			{
				if (ipnums.at(i) != (uint) IP[i])
				{
					ipOK = false;
					break;
				}
			}
			if (ipOK)
			{
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}
	if (!fData.sPort.isEmpty()) {
		bool found = false;
		foreach(uint port, fData.sPort)
		{
			if (port == ntohs(dp->port_s))
			{
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}
	if (!fData.dPort.isEmpty()) {
		bool found = false;
		foreach(uint port, fData.dPort)
		{
			if (port == ntohs(dp->port_d))
			{
				found = true;
				break;
			}
		}
		if (!found)
			return false;
	}
	return true;
}
