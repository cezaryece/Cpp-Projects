#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QDialog>
#include <QVector>
#include <QSettings>
#include <QGroupBox>
#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QGridLayout>
#include "edit_window.h"
#include "server.h"
namespace Ui {
    class Window;
}

class Window : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(Window)
public:
    explicit Window(QWidget *parent = 0);
    bool doClose;
//    virtual ~Window();

//protected:
//    virtual void changeEvent(QEvent *e);

private:
    QVector<Server*> * ServersList;
    QSettings * psettings;
    Edit_Window * EditWindow;

    QGroupBox *console;
    QWidget *buttons;
    QPushButton *Bexit;
    QPushButton *Bedit;
    QTextBrowser *tekst;

    //metody
    void setupUi(QVector<Server *> * ServerList);
    void serverUI(Server * server);
    void checkservers();
    void readConfig();

private slots:
    void time2check();
    void edit_servers();
    void closing();
};

#endif // WINDOW_H
