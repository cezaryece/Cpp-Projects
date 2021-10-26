/********************************************************************************
** Form generated from reading ui file 'window.ui'
**
** Created: Mon Jan 11 11:10:21 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QGroupBox *server;
    QLabel *status;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *restart;
    QGroupBox *console;
    QTextBrowser *tekst;

    void setupUi(QDialog *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QString::fromUtf8("Window"));
        Window->resize(451, 290);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Window->sizePolicy().hasHeightForWidth());
        Window->setSizePolicy(sizePolicy);
        Window->setSizeGripEnabled(false);
        Window->setModal(true);
        server = new QGroupBox(Window);
        server->setObjectName(QString::fromUtf8("server"));
        server->setGeometry(QRect(10, 10, 431, 51));
        status = new QLabel(server);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(10, 20, 101, 24));
        status->setFrameShape(QFrame::StyledPanel);
        status->setFrameShadow(QFrame::Raised);
        status->setAlignment(Qt::AlignCenter);
        status->setTextInteractionFlags(Qt::NoTextInteraction);
        start = new QPushButton(server);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(120, 20, 101, 24));
        stop = new QPushButton(server);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(220, 20, 101, 24));
        stop->setFlat(false);
        restart = new QPushButton(server);
        restart->setObjectName(QString::fromUtf8("restart"));
        restart->setGeometry(QRect(320, 20, 101, 24));
        console = new QGroupBox(Window);
        console->setObjectName(QString::fromUtf8("console"));
        console->setGeometry(QRect(10, 60, 431, 221));
        tekst = new QTextBrowser(console);
        tekst->setObjectName(QString::fromUtf8("tekst"));
        tekst->setGeometry(QRect(0, 20, 431, 191));

        retranslateUi(Window);

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QDialog *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "LAM center", 0, QApplication::UnicodeUTF8));
        server->setTitle(QApplication::translate("Window", "APACHE", 0, QApplication::UnicodeUTF8));
        status->setText(QApplication::translate("Window", "astatus", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("Window", "START", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("Window", "STOP", 0, QApplication::UnicodeUTF8));
        restart->setText(QApplication::translate("Window", "RESTART", 0, QApplication::UnicodeUTF8));
        console->setTitle(QApplication::translate("Window", "Console output:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Window);
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
