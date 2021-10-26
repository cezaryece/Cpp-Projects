/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtNetwork>

#include "client.h"
#include "ip.h"

Client::Client(QWidget *parent)
:   QDialog(parent), networkSession(0)
{
	ui.setupUi(this);
	ui.Interface->addItem("eth0");
	ui.Interface->addItem("eth1");
	ui.Interface->addItem("eth2");
	ui.Interface->addItem("eth3");

	ui.StartButton->setEnabled(true);
	ui.console->clear();

	ui.ServIP->setText("192.168.0.84");
	ui.ServPort->setText("6789");
	ui.Multicast->setChecked(false);
	ui.onlydata->setChecked(false);

	connect(&tcpSocket, SIGNAL(connected()), this, SLOT(conectedToServer()));
	connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
	connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readSniff()));
	connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void Client::connectToServer()
{
//	ui.StartButton->setDisabled(true);
	ui.console->insertPlainText("Connecting to server" + ui.ServIP->text() + ":" + ui.ServPort->text());
	ui.console->verticalScrollBar()->setValue(ui.console->verticalScrollBar()->maximum());

    blockSize = 0;
	tcpSocket.abort();
	tcpSocket.connectToHost(ui.ServIP->text(), ui.ServPort->text().toInt());
}

void Client::conectedToServer()
{
	ui.console->insertPlainText(" OK\n");
	ui.console->verticalScrollBar()->setValue(ui.console->verticalScrollBar()->maximum());
}

void Client::sendRequest()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_3);
	out << (quint16)0;
	out << (quint8) Filtr.eth_N << (quint8) Filtr.Protocol << (quint32) Filtr.pcktLen << (quint32) Filtr.pcktLimit << (quint32) Filtr.srcIP << (quint16) Filtr.srcPort << (quint32) Filtr.destIP << (quint16) Filtr.destPort << (quint8) Filtr.multicast << (quint8) Filtr.onlydata;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	tcpSocket.write(block);
}

void Client::readSniff()
{
	QDataStream in(&tcpSocket);
	in.setVersion(QDataStream::Qt_4_3);

	forever
	{
		if (blockSize == 0)
		{
			if (tcpSocket.bytesAvailable() < (int)sizeof(quint16))
				break;
			in >> blockSize;
		}
		if (blockSize == 0xFFFF)
		{
			closeConnection();
			break;
		}
		if (tcpSocket.bytesAvailable() < blockSize)
			break;

		QString response;
		in >> response;
		ui.console->insertPlainText(response + "\n");
		ui.console->verticalScrollBar()->setValue(ui.console->verticalScrollBar()->maximum());
		blockSize = 0;
	}
	ui.StartButton->setEnabled(true);
}

void Client::closeConnection()
{
	tcpSocket.close();
	ui.StartButton->setEnabled(true);
}

void Client::connectionClosedByServer()
{
	if (blockSize != 0xFFFF)
	{
		ui.console->insertPlainText("Error: Connection closed by server\n");
		ui.console->verticalScrollBar()->setValue(ui.console->verticalScrollBar()->maximum());
	}
	closeConnection();
}

void Client::displayError(QAbstractSocket::SocketError socketError)
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
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
	QMessageBox::information(this, tr("Sniff Client"),
                                 tr("The following error occurred: %1.")
								 .arg(tcpSocket.errorString()));
    }

	ui.StartButton->setEnabled(true);
}

void Client::error()
{
	ui.console->insertPlainText(tcpSocket.errorString() + "\n");
	ui.console->verticalScrollBar()->setValue(ui.console->verticalScrollBar()->maximum());
	closeConnection();
}

void Client::enableStartButton()
{
	ui.StartButton->setEnabled((!networkSession || networkSession->isOpen()) &&
								 !ui.ServIP->text().isEmpty() &&
								 !ui.ServPort->text().isEmpty());
}

void Client::on_StartButton_clicked()
{
	Filtr.pcktLimit = (unsigned short) ui.PcktLimit->value();
	bool OK;
	Filtr.pcktLen = (unsigned int) ui.PcktSize->text().toUInt(&OK);
	if (!OK)
		Filtr.pcktLen = 0;
	if (ui.Protocol->text() != "") Filtr.Protocol = (char) ui.Protocol->text().toUShort();
	else Filtr.Protocol = -1;

	Filtr.srcIP = IPstring2int(ui.SrcIP->text());
	if (ui.SrcPort->text() != "") Filtr.srcPort = ui.SrcPort->text().toUInt();
	else Filtr.srcPort = 0;
	Filtr.destIP = IPstring2int(ui.DestIP->text());
	if (ui.DestPort->text() != "") Filtr.destPort = ui.DestPort->text().toUInt();
	else Filtr.destPort = 0;
	Filtr.eth_N = ui.Interface->currentIndex();
	Filtr.multicast = ui.Multicast->isChecked();
	Filtr.onlydata = ui.onlydata->isChecked();

	//wysłanie danych filtra do serwera
	connectToServer();

	if (!tcpSocket.waitForConnected(3000))
	{
		ui.console->insertPlainText(tcpSocket.errorString() + "\n");
		ui.console->verticalScrollBar()->setValue(ui.console->verticalScrollBar()->maximum());

		closeConnection();
	}
	sendRequest();
}

void Client::on_ClearButton_clicked()
{
	ui.console->clear();
}
