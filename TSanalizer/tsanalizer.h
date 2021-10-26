#ifndef TSANALIZER_H
#define TSANALIZER_H

#include <QDialog>
#include <QTcpSocket>
#include <QByteArray>
#include "structs.h"
#include "TSstruct.h"

namespace Ui {
    class TsAnalizer;
}

class TsAnalizer : public QDialog
{
    Q_OBJECT

public:
    explicit TsAnalizer(QWidget *parent = 0);
    ~TsAnalizer();

private:
    Ui::TsAnalizer *ui;
	QByteArray StrData;
	uint PacketsDone;
	int f_PID;

private slots:
	void connectToServer();
	void conectedToServer();
	void displayError(QAbstractSocket::SocketError socketError);
	void readSniff();
	void connectionClosedByServer();
	void error();

	void on_ClearButton_clicked();
	void on_StartButton_clicked();

	void on_BreakButton_clicked();

private:
	void closeConnection(bool);
	void sendRequest();
	void startRead(bool fromUI);
	int findNextSyncByte(int currPos);

	QString AnalizeTSpacket();
	QString AnalizeAdaptationField (const AdaptationField *);
	QString AnalizePAT(const PAT *);
	QString AnalizePATitem(const char *);
	QString AnalizePMT(const PMT *);
	QString AnalizePMTitem(const PMTitem *);

	filterconfig Filtr;
	unsigned short int PacketLimit, PacketCount;

	QTcpSocket tcpSocket;
	QString currentResponse;
	quint16 blockSize;
	uint AFsize;  //Adaptation Field size
};

#endif // TSANALIZER_H
