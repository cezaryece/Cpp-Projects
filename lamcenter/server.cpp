#include "server.h"
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QString>
#include <iostream>

extern bool wasEdited;

Server::Server(QString server_name, QString pid_path, QString initd_script, ushort ID) {
    name = server_name;
    pid = pid_path;
    initd = initd_script;
    serverID = ID;
    is_running = check_status();
}
//Server::~Server() {
//    std::cout << "Server " << name.toStdString() << " DESTRUCTOR start" <<std::endl;
//}

bool Server::check_status() {
    QFile file(pid);
    if (file.exists()) return true;
    else return false;
}
void Server::start() {
    QProcess daemon;
    daemon.setProcessChannelMode(QProcess::MergedChannels);
    daemon.start("sudo", QStringList() << initd << "start");
    daemon.waitForFinished();
    text->setText("Starting of " + name + " server");
    text->setText(daemon.readAll());
}
void Server::stop() {
    QProcess daemon;
    daemon.setProcessChannelMode(QProcess::MergedChannels);
    daemon.start("sudo", QStringList() << initd << "stop");
    daemon.waitForFinished();
    text->setText("Stoping of " + name + " server");
    text->setText(daemon.readAll());
}
void Server::restart() {
    led->setColor("yellow");
    QProcess daemon;
    daemon.setProcessChannelMode(QProcess::MergedChannels);
    daemon.start("sudo", QStringList() <<initd << "restart");
    daemon.waitForFinished();
    text->setText("Retarting of " + name + " server");
    text->setText(daemon.readAll());
}
void Server::set_slots() {
    connect (PBstart, SIGNAL (clicked()), this, SLOT (start()));
    connect (PBstop, SIGNAL (clicked()), this, SLOT (stop()));
    connect (PBrestart, SIGNAL (clicked()), this, SLOT (restart()));
}
void Server::set_edit_slots() {
}
void Server::toggle_enabled() {
    if (CBdelete->isChecked()) {
        LEname->setEnabled(false);
        LEpid->setEnabled(false);
        PBpid_file->setEnabled(false);
        LEinitd->setEnabled(false);
        PBinitd_file->setEnabled(false);
    }
    else {
        LEname->setEnabled(true);
        LEpid->setEnabled(true);
        PBpid_file->setEnabled(true);
        LEinitd->setEnabled(true);
        PBinitd_file->setEnabled(true);
    }
}
void Server::getPidFile() {
    LEpid->setText(QFileDialog::getOpenFileName((QWidget*) this,"Find pid file...","/var/run/","pid files (*.pid);; All files(*.*)", 0, QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly) );
}
void Server::getInitdFile() {
    LEinitd->setText(QFileDialog::getOpenFileName((QWidget*) this,"Find initd script...","/etc/init.d/","All files(*.*)", 0, QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly) );
}
