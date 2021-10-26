#ifndef SERVER_H
#define SERVER_H

#include <QtCore>
#include <QWidget>
#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextBrowser>
#include "qled.h"

class Server : public QWidget
{
    Q_OBJECT
public:
    bool is_running;
    Server(QString server_name, QString pid_path, QString initd_script, ushort ID);
//    ~Server();
    bool check_status();
    QString name;
    QString pid;
    QString initd;
    QWidget * parent;
    QPushButton * PBstart;
    QPushButton * PBstop;
    QPushButton * PBrestart;
    QGroupBox * GBserver;
    QLabel * Lstatus;
    QLed * led;
    QCheckBox * CBdelete;
    QLabel *Lname;QLineEdit *LEname;
    QLabel *Lpid; QLineEdit *LEpid; QPushButton *PBpid_file;
    QLabel *Linitd; QLineEdit *LEinitd; QPushButton *PBinitd_file;

    ushort serverID;
    QTextBrowser * text;

    void set_slots();
    void set_edit_slots();

private slots:
    void toggle_enabled();
    void getPidFile();
    void getInitdFile();

public slots:
    void start();
    void stop();
    void restart();
};

#endif // SERVER_H
