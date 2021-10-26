#include <QtGui>
#include "tsanalizer.h"
#include "ui_tsanalizer.h"
#include "../MY_LIBS/QTip.h"
#include <arpa/inet.h>

TsAnalizer::TsAnalizer(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TsAnalizer),
	PacketsDone(0)
{
    ui->setupUi(this);
	ui->Interface->addItem("eth0");
	ui->Interface->addItem("eth1");
	ui->Interface->addItem("eth2");
	ui->Interface->addItem("eth3");
	ui->Interface->setCurrentIndex(1);

	ui->StartButton->setEnabled(true);
	ui->BreakButton->setDisabled(true);
	ui->console->clear();

	ui->ServIP->setText("83.2.25.11");
	ui->ServPort->setText("6789");
	ui->Multicast->setChecked(false);
	ui->onlydata->setChecked(true);
	ui->FiltrALL->setChecked(true);
	ui->PcktLimit->setValue(9);
	ui->PcktSize->setText("11261");

	connect(&tcpSocket, SIGNAL(connected()), this, SLOT(conectedToServer()));
	connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
	//connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
	connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

TsAnalizer::~TsAnalizer()
{
    delete ui;
}

void TsAnalizer::on_ClearButton_clicked()
{
	ui->console->clear();
}

void TsAnalizer::on_BreakButton_clicked()
{
	//qDebug() << "on_BreakButton_clicked()";
	disconnect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
	PacketsDone = Filtr.pcktLimit +1;
	closeConnection(true);
}

void TsAnalizer::connectToServer()
{
//qDebug() << "connectToServer()";
	blockSize = 0;
	tcpSocket.connectToHost(ui->ServIP->text(), ui->ServPort->text().toInt());
	connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
}

void TsAnalizer::conectedToServer()
{
	//qDebug() << "conectedToServer()";
//	ui->console->insertPlainText(" OK\n");
//	ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
}

void TsAnalizer::closeConnection(bool error)
{
	//qDebug() << "closeConnection" << error << PacketsDone;
	tcpSocket.disconnectFromHost();
	int i = 0;
	while (tcpSocket.state() != QAbstractSocket::UnconnectedState)
	{
		qDebug() << "tcpSocket.state()" << tcpSocket.state();
		tcpSocket.waitForDisconnected(1000);
		i++;
		if (i > 10)
		{
			qDebug() << "nie moge sie doczekać";
			error = true;
			break;
		}
	}
	
	if (!error && (PacketsDone < Filtr.pcktLimit))
		startRead(false);
	else
	{
		ui->StartButton->setEnabled(true);
		ui->BreakButton->setDisabled(true);
		disconnect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
	}
}

void TsAnalizer::connectionClosedByServer()
{
	//qDebug() << "connectionClosedByServer()";
	bool isError = false;
	if (blockSize != 0xFFFF)
	{
		isError = true;
		//ui->console->insertPlainText("Error: Connection closed by server\n");
		//ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
	}
	closeConnection(false);
}

void TsAnalizer::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
	QMessageBox::information(this, tr("Sniff Client"),
								 tr("The host was not found. Please check the "
									"host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
	QMessageBox::information(this, tr("Sniff Client"),
								 tr("The connection was refused by the peer. "
									"Make sure the SniffServer is running, "
									"and check that the host name and port "
									"settings are correct."));
		break;
	default:
	QMessageBox::information(this, tr("Sniff Client"),
								 tr("The following error occurred: %1.")
								 .arg(tcpSocket.errorString()));
	}
}

void TsAnalizer::error()
{
	ui->console->insertPlainText("\n\n $$$$$$$ SOCKET ERROR\n" + tcpSocket.errorString() + "\n");
	ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
	//closeConnection(true);
}

void TsAnalizer::on_StartButton_clicked()
{
	PacketsDone = 0;
	ui->StartButton->setDisabled(true);
	ui->BreakButton->setEnabled(true);
	startRead(true);
}

void TsAnalizer::startRead(bool fromUI)
{
	disconnect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));

	if (fromUI)
		PacketsDone = 0;
	Filtr.pcktLimit = (unsigned short) ui->PcktLimit->value();
	bool OK;
	Filtr.pcktLen = (unsigned int) ui->PcktSize->text().toUInt(&OK);
	if (!OK)
		Filtr.pcktLen = 0;
	if (ui->Protocol->text() != "") Filtr.Protocol = (char) ui->Protocol->text().toUShort();
	else Filtr.Protocol = -1;

	Filtr.srcIP = IPstring2int(ui->SrcIP->text());
	if (ui->SrcPort->text() != "") Filtr.srcPort = ui->SrcPort->text().toUInt();
	else Filtr.srcPort = 0;
	Filtr.destIP = IPstring2int(ui->DestIP->text());
	if (ui->DestPort->text() != "") Filtr.destPort = ui->DestPort->text().toUInt();
	else Filtr.destPort = 0;
	Filtr.eth_N = ui->Interface->currentIndex();
	Filtr.multicast = ui->Multicast->isChecked();
	Filtr.onlydata = ui->onlydata->isChecked();

	f_PID = -1;
	if (!ui->TsPID->text().isEmpty())
	{
		bool OK;
		f_PID = (int) ui->TsPID->text().toUShort(&OK, 16);
		if (!OK)
			f_PID = -1;
	}


	//wysłanie danych filtra do serwera
	connectToServer();

	if (!tcpSocket.waitForConnected())
	{
		ui->console->insertPlainText(tcpSocket.errorString() + "\n");
		ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
		closeConnection(true);
	}
	else
	{
		sendRequest();
		connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
	}
}

void TsAnalizer::sendRequest()
{
	//qDebug() << "sendRequest()";
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_3);
	out << (quint16)0;
	out << (quint8) Filtr.eth_N << (quint8) Filtr.Protocol << (quint32) Filtr.pcktLen << (quint32) Filtr.pcktLimit << (quint32) Filtr.srcIP << (quint16) Filtr.srcPort << (quint32) Filtr.destIP << (quint16) Filtr.destPort << (quint8) Filtr.multicast << (quint8) Filtr.onlydata;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	tcpSocket.write(block);
}

void TsAnalizer::readSniff()
{
	//qDebug() << "readSniff()";
	disconnect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
	QDataStream in(&tcpSocket);
	in.setVersion(QDataStream::Qt_4_3);
	//blockSize = 0;

	forever
	{
		if (blockSize == 0) {
			if (tcpSocket.bytesAvailable() < (int)sizeof(quint16))
				break;
			in >> blockSize;
		}
		if (blockSize == 0xFFFF)
		{
			closeConnection(false);
			break;
		}
		if (tcpSocket.bytesAvailable() < blockSize)
		{
			//qDebug() << "tcpSocket.bytesAvailable() < blockSize" << tcpSocket.bytesAvailable() << blockSize;
			break;
		}

		in >> StrData;
		if (Filtr.onlydata)
		{
			ui->console->insertPlainText(AnalizeTSpacket());
		}
		else
			ui->console->insertPlainText(StrData.data());
		ui->console->verticalScrollBar()->setValue(ui->console->verticalScrollBar()->maximum());
		blockSize = 0;
	}
	connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
//	ui->StartButton->setEnabled(true);
}


// ANALIZATORY

int TsAnalizer::findNextSyncByte(int currPos)
{
	bool SBfound = false;
	while ( currPos < StrData.length() - (5*TSlen) )
	{
		for (int pos = 1; pos < TSlen; pos++)
		{
			if (StrData.at(currPos + pos) == 0x47)
			{
				SBfound = true;
				currPos += pos;
				break;
			}
		}
		if (SBfound)
		{
			for (int i=0; i < 5; ++i)
			{
				if (StrData.at(currPos + (i*TSlen)) != 0x47)
				{
					SBfound = false;
					break;
				}
			}
		}
		if (SBfound)
			return currPos;
		currPos += TSlen;
	}
	return -1;
}

QString TsAnalizer::AnalizeTSpacket()
{
	QString t, result;
	int pcktNum = 0;

	result = "*";
//	result += "StrData.length " + t.number(StrData.length()) + "     TS pakets " + t.number(StrData.length() / TSlen) + "\n";

	for (int bytePos = 0; bytePos < (StrData.length() - TSlen);)
	{
		AFsize = 0;
		TSpacket* tspP;

		if (StrData.at(bytePos) != 0x47)
		{
			bytePos = findNextSyncByte(bytePos);
			if ( bytePos == -1)
			{
				//nie znaleziono SyncByte w tej paczce pakietów
				//qDebug() <<"!!!!!!!!!!!!!!! NIE ZNALEZIONO SyncByte - pomijam resztę\n\n";
				break;
			}
		}
		tspP = (TSpacket*) StrData.mid(bytePos, TSlen).data();
		bool ShowMe = true;

		unsigned char buf[4];
		memcpy(&buf, tspP, 4);

		TSheader ts_header;
		ts_header.sync_byte = (unsigned char) buf[0];
		ts_header.transport_error_indicator    = (unsigned char) ((buf[1] & 0x80) >> 7);
		ts_header.payload_unit_start_indicator = (unsigned char) ((buf[1] & 0x40) >> 6);
		ts_header.transport_priority           = (unsigned char) ((buf[1] & 0x20) >> 5);
		ts_header.PID                          = (unsigned int) (((buf[1] & 0x1F) << 8) | buf[2]);
		ts_header.transport_scrambling_control = (unsigned char) ((buf[3] & 0xC0) >> 6);
		ts_header.adaptation_field_control     = (unsigned char) ((buf[3] & 0x30) >> 4);
		ts_header.continuity_counter           = (unsigned char)  (buf[3] & 0x0F);

		//filtrowanie pakietów TS

		if (ts_header.sync_byte != 0x47)
		{
			//qDebug() << "wrong SyncByte" << t.number(ts_header.sync_byte,16);
			ShowMe = false;
		}
		if ((f_PID >= 0) && (ts_header.PID != (uint) f_PID))
			ShowMe = false;


		if (ShowMe)
		{
			if (ts_header.sync_byte != 0x47)
				qDebug() << "wrong SyncByte" << t.number(ts_header.sync_byte,16);

			result += "\nTS packet " + t.number(PacketsDone + pcktNum +1) + " | ";
			result +=" PID " + t.number(ts_header.PID,16);
			result +=" SyncByte " + t.number(ts_header.sync_byte,16);
			result +=" TEI " + t.number(ts_header.transport_error_indicator);
			result +=" PUSI " + t.number(ts_header.payload_unit_start_indicator);
			result +=" TP " + t.number(ts_header.transport_priority);
			result +=" Scrambling: " + t.number(ts_header.transport_scrambling_control,2);
			result +=" AFE: " + t.number(ts_header.adaptation_field_control,2);
			result +=" CC: " + t.number(ts_header.continuity_counter,16);

			if (ts_header.adaptation_field_control > 1)
				result.append(AnalizeAdaptationField((AdaptationField*) (tspP + 4)));
			if (ts_header.PID == 0)
				result.append(AnalizePAT( (PAT*) (tspP + 4 + AFsize)));
			//		if (tspP->SyncByte != 0x47)
			//		{
			//			result += "\n  @@@@ pcktNum " + t.number(pcktNum);
			//			result += "   @@@@ nieprawidłowy SyncByte " + t.number(tspP->SyncByte,16)  + "\n\n";
			////			break;
			//		}
			//		StrData.remove(0,TSlen);
			result.append("\n\n");
			pcktNum++;
		}
		bytePos = bytePos + TSlen;
	}
	PacketsDone += pcktNum;

	return result;
}

QString TsAnalizer::AnalizeAdaptationField (const AdaptationField * afP)
{
	QString result = "\n* Adaptation Field\n";
	QString t;
	AFsize = afP->Length;
	result += " Length " + t.number(afP->Length);
	result += " DI " + t.number(afP->DI);
	result += " RAI " + t.number(afP->RAI);
	result += " ESPI " + t.number(afP->ESPI);
	result += " PCR " + t.number(afP->PCR);
	result += " OPCR " + t.number(afP->OPCR);
	result += " SP " + t.number(afP->SP);
	result += " TPD " + t.number(afP->TPD);
	result += " AFE " + t.number(afP->AFE);
	return result;
}

QString TsAnalizer::AnalizePAT(const PAT * patP)
{
	QString result = "\n *** tabela PAT ";
	QString t;
	PATheader pat_header;
	unsigned char buf[8];
	memcpy(&buf, patP, 8);

	pat_header.version_number         =  (unsigned int)((buf[5] & 0x3E) >> 1);
	pat_header.section_length         = (((unsigned int)(buf[1] & 0x0F) << 8) | buf[2]);
	pat_header.section_number         =  (unsigned int)(buf[6]);
	pat_header.last_section_number    =  (unsigned int)(buf[7]);
	pat_header.current_next_indicator =  (unsigned int)(buf[5] & 0x01);

	result += " ver " + t.number(pat_header.version_number);

	unsigned int number_of_programs = ((pat_header.section_length - (5 + 4)) / 4);
	result += " Nproggs " + t.number(number_of_programs) + "\n";
	if (number_of_programs <= 8192)
	{
		if (pat_header.last_section_number != 0)
			qDebug() << "(PAT) more than one section found in PAT !!!" << endl;
		for(uint i=0; i < number_of_programs; i++)
			result += AnalizePATitem((char*)(patP + 8 + (4*i)));
	}

//	result += " pointer " + t.number(patP->Pointer);
//	result += " TableID " + t.number(patP->TableID) + "[00]";
//	result += " Misc " + t.number(patP->Misc,2) + "[10]";
//	result += " Res " + t.number(patP->Res,2) + "[11]";
//	result += " Len " + t.number(patP->Len);
//	result += " TSid " + t.number(patP->TSid,16);
//	result += " Misc2 " + t.number((uint) patP->Misc2,16);
//	result += "\nLen / PATitem size = " + t.number(patP->Len / sizeof(PATitem)) + " reszta " + t.number(patP->Len % sizeof(PATitem));
	return result;
}

QString TsAnalizer::AnalizePATitem(const char * buf)
{
	QString result = "\n *** PAT item\n";
	QString t;

	uint program_number  = (uint)(((buf[0]) << 8) | buf[1]);
	uint program_map_PID = (uint)(((buf[2] & 0x1F) << 8) | buf[3]);

	result += " ProgNum " + t.number(program_number,16);
	result += " PID " + t.number(program_map_PID,16) + "\n";
	return result;
}

QString TsAnalizer::AnalizePMT(const PMT * pmtP)
{
	QString result = "\n * PMT\n";
	return result;
}

QString TsAnalizer::AnalizePMTitem(const PMTitem * pmtitemP)
{
	QString result = "\n *** PMT item\n";
	return result;
}
