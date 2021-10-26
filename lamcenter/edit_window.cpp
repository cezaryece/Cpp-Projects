#include "edit_window.h"
#include <QFileDialog>
#include <iostream>

Edit_Window::Edit_Window(QWidget *parent, QVector<Server*> *ServersList, QSettings * pset) : QDialog(parent), ServerList(ServersList), psettings (pset)
{
    for (int i=0; i < ServerList->size(); ++i) {
        serverUI(ServerList->at(i));
    }
    GBnewserver = new QGroupBox(this);
    GBnewserver->setObjectName("New server");
    GBnewserver->setGeometry(QRect(10, 10 + (ServerList->size() * 70), 431, 80));
    GBnewserver->setTitle("New server");
        Lname = new QLabel("New server name:",GBnewserver);
            Lname->setGeometry(QRect(5,5,70,20));
        LEname = new QLineEdit(GBnewserver);
            LEname->setGeometry(QRect(75,5,340,20));
        LEpid = new QLineEdit("New server pid file...",GBnewserver);
            LEpid->setGeometry(QRect(5,30,300,20));
        PBpid_file = new QPushButton("Find pid file...",GBnewserver);
            PBpid_file->setGeometry(QRect(305,30,120,20));
            connect (PBpid_file, SIGNAL (clicked()), this, SLOT (getPidFile()));
        LEinitd = new QLineEdit("New server initd script...",GBnewserver);
            LEinitd->setGeometry(QRect(5,55,300,20));
        PBinitd_file = new QPushButton("Find inid script...",GBnewserver);
            PBinitd_file->setGeometry(QRect(305,55,120,20));
            connect (PBinitd_file, SIGNAL (clicked()), this, SLOT (getInitdFile()));

//    PBreset = createButton(tr("&Reset"), SLOT(reset()));
    PBreset = new QPushButton("&Reset",this);
        PBreset->setGeometry(QRect(15, 95 + (ServerList->size() * 70), 70, 25));
        connect (PBreset, SIGNAL (clicked()), this, SLOT (reset()));
    PBsave = new QPushButton("&Save", this);
        PBsave->setGeometry(QRect(270, 95 + (ServerList->size() * 70), 70, 25));
        connect (PBsave, SIGNAL (clicked()), this, SLOT (save()));
    PBcancel = new QPushButton("Cancel",this);
        PBcancel->setGeometry(QRect(350, 95 + (ServerList->size() * 70), 70, 25));
        connect (PBcancel, SIGNAL (clicked()), this, SLOT (close()));

    setWindowTitle("Edition of servers to control");

}
void Edit_Window::serverUI(Server * server) {
    server->parent = (QWidget*) this;
    server->GBserver = new QGroupBox(this);
    server->GBserver->setObjectName(server->name);
    server->GBserver->setGeometry(QRect(10, 5 + (server->serverID * 70), 431, 70));
    server->GBserver->setTitle(server->name);
        server->CBdelete = new QCheckBox("Delete",server->GBserver);
            server->CBdelete->setGeometry(QRect(5,5,65,22));
            server->CBdelete->setCheckState(Qt::Unchecked);
            connect (server->CBdelete, SIGNAL (stateChanged(int)), server, SLOT (toggle_enabled()));
//        server->Lname = new QLabel(server->name,server->GBserver);
//            server->Lname->setGeometry(QRect(35,5,70,20));
        server->LEname = new QLineEdit(server->name,server->GBserver);
            server->LEname->setGeometry(QRect(115,5,300,20));
        server->LEpid = new QLineEdit(server->pid,server->GBserver);
            server->LEpid->setGeometry(QRect(0,25,300,20));
        server->PBpid_file = new QPushButton("Find pid file...",server->GBserver);
            server->PBpid_file->setGeometry(QRect(305,25,120,20));
            connect (server->PBpid_file, SIGNAL (clicked()), server, SLOT (getPidFile()));
        server->LEinitd = new QLineEdit(server->initd,server->GBserver);
            server->LEinitd->setGeometry(QRect(0,50,300,20));
        server->PBinitd_file = new QPushButton("Find init.d script...",server->GBserver);
            server->PBinitd_file->setGeometry(QRect(305,50,120,20));
            connect (server->PBinitd_file, SIGNAL (clicked()), server, SLOT (getInitdFile()));
    server->set_edit_slots();
}

void Edit_Window::getPidFile() {
    LEpid->setText(QFileDialog::getOpenFileName((QWidget*) this,"Find pid file...","/var/run/","pid files (*.pid);; All files(*.*)", 0, QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly) );
}

void Edit_Window::getInitdFile() {
    LEinitd->setText(QFileDialog::getOpenFileName((QWidget*) this,"Find initd script...","/etc/init.d/","All files(*.*)", 0, QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly) );
}

void Edit_Window::reset() {
    for (int i=0;i < ServerList->size(); ++i) {
        ServerList->at(i)->CBdelete->setCheckState(Qt::Unchecked);
        ServerList->at(i)->LEname->setText(ServerList->at(i)->name);
        ServerList->at(i)->LEpid->setText(ServerList->at(i)->pid);
        ServerList->at(i)->LEinitd->setText(ServerList->at(i)->initd);

        LEname->setText("");
        LEpid->setText("New server pid file...");
        LEinitd->setText("New server initd script...");
    }
}

void Edit_Window::save() {
    QFile * kfile;
    QString kfilename("lamcenter.conf");

    if (QFile::exists(kfilename)) {
        QFile::remove(kfilename);

        kfile = new QFile(kfilename);
        kfile->unsetError();
        if (!kfile->open(QIODevice::ReadWrite))
            std::cout << "błąd utworzenia pliku " << " error=" << kfile->errorString().toStdString()  << std::endl;
        else kfile->setPermissions(QFile::WriteUser|QFile::WriteGroup|QFile::WriteOther|QFile::ReadUser|QFile::ReadGroup|QFile::ReadOther);
    }

    delete psettings;
    psettings = new QSettings(kfilename,QSettings::IniFormat);

    for (int i=0;i < ServerList->size(); ++i) {
        if (!ServerList->at(i)->CBdelete->isChecked()) {
            psettings->beginGroup(ServerList->at(i)->LEname->text());
            psettings->setValue("pid",ServerList->at(i)->LEpid->text());
            psettings->setValue("initd",ServerList->at(i)->LEinitd->text());
            psettings->endGroup();
        }
    }
    if (LEname->text() != "" && QFile::exists(LEpid->text()) && QFile::exists(LEinitd->text())) {
        psettings->beginGroup(LEname->text());
        psettings->setValue("pid",LEpid->text());
        psettings->setValue("initd",LEinitd->text());
        psettings->endGroup();
    }
    psettings->sync();
//    std::cout << "psettings status: " << psettings->status() << std::endl;
    accept();
}
