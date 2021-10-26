#include "window.h"
#include "server.h"
#include "edit_window.h"
#include <iostream>
#include <QVector>
#include <QFile>
#include <QStringList>

extern bool wasEdited;

Window::Window(QWidget *parent) : QDialog(parent) {
    doClose = false;
    readConfig();
    setupUi(ServersList);
    connect (Bexit, SIGNAL (clicked()), this, SLOT (closing()));
    connect (Bedit, SIGNAL (clicked()), this, SLOT (edit_servers()));
    checkservers();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time2check()));
    timer->start(2000);
}

//Window::~Window() {
//    delete ServersList;
//    setResult(1);
//    std::cout << "~Window" << std::endl;
//}

void Window::setupUi(QVector<Server *> *ServerList) {
        if (objectName().isEmpty())
            setObjectName(QString::fromUtf8("Window"));
        if (ServerList->size()>1)
            resize(451, 322 + ((ServerList->size()-1)*61));
        setWindowTitle("LAM center");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
//        sizePolicy.setHeightForWidth(sizePolicy().hasHeightForWidth());
        setSizePolicy(sizePolicy);
        setSizeGripEnabled(false);
        setModal(true);

        console = new QGroupBox(this);
        console->setObjectName(QString::fromUtf8("console"));
        console->setGeometry(QRect(10, 65 + (61 * (ServerList->size() - 1)), 431, 221));
        console->setTitle("Console output:");
            tekst = new QTextBrowser(console);
            tekst->setObjectName(QString::fromUtf8("tekst"));
            tekst->setGeometry(QRect(2, 20, 427, 199));

        buttons = new QWidget(this);
        buttons->setObjectName("buttons");
        buttons->setGeometry(QRect(10,65 + (61 * (ServerList->size() - 1)) + 222, 432, 34));
            Bexit = new QPushButton(buttons);
            Bexit->setText("EXIT");
            Bexit->setGeometry(320, 5, 101, 24);
            Bedit = new QPushButton(buttons);
            Bedit->setText("Edit severs");
            Bedit->setGeometry(10, 5, 121, 24);
//        wstawienie serwerów
        for (int i=0; i < ServerList->size(); ++i) {
            serverUI(ServerList->at(i));
            ServerList->at(i)->text = tekst;
        }
    } //setupUi

void Window::serverUI(Server * server) {
    server->GBserver = new QGroupBox(this);
    server->GBserver->setObjectName(server->name);
    server->GBserver->setGeometry(QRect(10, 5 + (server->serverID * 61), 431, 51));
    server->GBserver->setTitle(server->name);
    server->led = new QLed(server->GBserver);
        server->led->setObjectName("LED");
        server->led->setGeometry(5,20,0,0);
        server->led->setColor(Qt::green);
    server->Lstatus = new QLabel(server->GBserver);
        server->Lstatus->setObjectName("status");
        server->Lstatus->setGeometry(QRect(40, 20, 71, 24));
        server->Lstatus->setFrameShape(QFrame::StyledPanel);
        server->Lstatus->setFrameShadow(QFrame::Raised);
        server->Lstatus->setAlignment(Qt::AlignCenter);
        server->Lstatus->setTextInteractionFlags(Qt::NoTextInteraction);
    server->PBstart = new QPushButton(server->GBserver);
        server->PBstart->setObjectName("start");
        server->PBstart->setGeometry(QRect(120, 20, 101, 24));
        server->PBstart->setText("start");
    server->PBstop = new QPushButton(server->GBserver);
        server->PBstop->setObjectName("stop");
        server->PBstop->setGeometry(QRect(220, 20, 101, 24));
        server->PBstop->setText("stop");
        server->PBstop->setFlat(false);
    server->PBrestart = new QPushButton(server->GBserver);
        server->PBrestart->setObjectName("restart");
        server->PBrestart->setGeometry(QRect(320, 20, 101, 24));
        server->PBrestart->setText("restart");
    server->set_slots();
}

void Window::readConfig() {
    QFile kfile;
    QString kfilename("lamcenter.conf");
    Server * server;

    ServersList = new QVector<Server*>;

    if (!kfile.exists(kfilename)) {
        std::cout << "Plik konfiguracyjny nie istnieje!!!" << std::endl;
        exit(1);
    }
    else {
        psettings = new QSettings (kfilename,QSettings::IniFormat);
        QStringList groups = psettings->childGroups();
        for (int i = 0; i < groups.size();++i){
            server = new Server(
                    groups.at(i).toLocal8Bit().constData(),
                    psettings->value(groups.at(i) + "/pid").toString(),
                    psettings->value(groups.at(i) + "/initd").toString(),
                    i);
            ServersList->push_back(server);
        }
    }
}

void Window::checkservers() {
    for (int i=0; i < ServersList->size();++i) {
        if (ServersList->at(i)->check_status()) {
            ServersList->at(i)->Lstatus->setText("running");
            ServersList->at(i)->led->setValue(true);
        }
        else {
            ServersList->at(i)->Lstatus->setText("dead");
            ServersList->at(i)->led->setValue(false);
        }
    }
}

void Window::time2check() {
    checkservers();
}

void Window::edit_servers() {
    int res;
    hide();
    EditWindow = new Edit_Window(this, ServersList, psettings);
    res = EditWindow->exec();
    if (res == QDialog::Accepted) {
        QCoreApplication::exit(1);
    }
}
void Window::closing() {
    doClose = true;
    done(0);
}
