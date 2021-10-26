#ifndef EDIT_WINDOW_H
#define EDIT_WINDOW_H

#include <QDialog>
#include <QWidget>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
#include "server.h"

class Edit_Window : public QDialog
{
    Q_OBJECT

public:
    Edit_Window(QWidget *parent, QVector<Server*> *ServersList, QSettings  * pset);

private:
    QVector<Server*> *ServerList;
    QSettings * psettings;

    //elementy UI dla nowego servera
    QGroupBox *GBnewserver;
    QLabel *Lname;QLineEdit *LEname;
    QLabel *Lpid; QLineEdit *LEpid; QPushButton *PBpid_file;
    QLabel *Linitd; QLineEdit *LEinitd; QPushButton *PBinitd_file;

    //przyciski sterowania okienkiem dialogowym
    QPushButton *PBreset;
    QPushButton *PBsave;
    QPushButton *PBcancel;

    //metody
    void serverUI(Server *);

private slots:
    void reset();
    void save();
    void getPidFile();
    void getInitdFile();
};

#endif // EDIT_WINDOW_H
