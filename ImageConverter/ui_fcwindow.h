/********************************************************************************
** Form generated from reading ui file 'fcwindow.ui'
**
** Created: Thu Aug 20 11:25:18 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FCWINDOW_H
#define UI_FCWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FCWindow
{
public:
    QLabel *label;
    QCheckBox *checkBox_subdirs;
    QCheckBox *checkBox_resize;
    QLineEdit *lineEdit_size;
    QCheckBox *checkBox_2JPG;
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QPushButton *pushButton_wybierz;
    QCheckBox *checkBox_greyscale;
    QLineEdit *lineEdit_dir;
    QLabel *znaleziono;

    void setupUi(QDialog *FCWindow)
    {
        if (FCWindow->objectName().isEmpty())
            FCWindow->setObjectName(QString::fromUtf8("FCWindow"));
        FCWindow->resize(401, 160);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FCWindow->sizePolicy().hasHeightForWidth());
        FCWindow->setSizePolicy(sizePolicy);
        FCWindow->setMinimumSize(QSize(401, 160));
        FCWindow->setMaximumSize(QSize(401, 160));
        FCWindow->setBaseSize(QSize(401, 160));
        FCWindow->setSizeGripEnabled(false);
        label = new QLabel(FCWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(9, 9, 153, 16));
        checkBox_subdirs = new QCheckBox(FCWindow);
        checkBox_subdirs->setObjectName(QString::fromUtf8("checkBox_subdirs"));
        checkBox_subdirs->setGeometry(QRect(10, 50, 171, 21));
        checkBox_resize = new QCheckBox(FCWindow);
        checkBox_resize->setObjectName(QString::fromUtf8("checkBox_resize"));
        checkBox_resize->setGeometry(QRect(10, 80, 147, 21));
        lineEdit_size = new QLineEdit(FCWindow);
        lineEdit_size->setObjectName(QString::fromUtf8("lineEdit_size"));
        lineEdit_size->setGeometry(QRect(160, 80, 71, 21));
        checkBox_2JPG = new QCheckBox(FCWindow);
        checkBox_2JPG->setObjectName(QString::fromUtf8("checkBox_2JPG"));
        checkBox_2JPG->setGeometry(QRect(10, 100, 129, 21));
        buttonBox = new QDialogButtonBox(FCWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(230, 110, 160, 26));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel);
        label_2 = new QLabel(FCWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 80, 16, 20));
        pushButton_wybierz = new QPushButton(FCWindow);
        pushButton_wybierz->setObjectName(QString::fromUtf8("pushButton_wybierz"));
        pushButton_wybierz->setGeometry(QRect(322, 30, 71, 26));
        pushButton_wybierz->setFlat(false);
        checkBox_greyscale = new QCheckBox(FCWindow);
        checkBox_greyscale->setObjectName(QString::fromUtf8("checkBox_greyscale"));
        checkBox_greyscale->setGeometry(QRect(10, 120, 104, 21));
        lineEdit_dir = new QLineEdit(FCWindow);
        lineEdit_dir->setObjectName(QString::fromUtf8("lineEdit_dir"));
        lineEdit_dir->setGeometry(QRect(10, 30, 301, 22));
        znaleziono = new QLabel(FCWindow);
        znaleziono->setObjectName(QString::fromUtf8("znaleziono"));
        znaleziono->setGeometry(QRect(10, 140, 381, 16));

        retranslateUi(FCWindow);
        QObject::connect(checkBox_resize, SIGNAL(stateChanged(int)), lineEdit_size, SLOT(setFocus()));

        QMetaObject::connectSlotsByName(FCWindow);
    } // setupUi

    void retranslateUi(QDialog *FCWindow)
    {
        FCWindow->setWindowTitle(QApplication::translate("FCWindow", "FCWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FCWindow", "Wybierz katalog z plikami", 0, QApplication::UnicodeUTF8));
        checkBox_subdirs->setText(QApplication::translate("FCWindow", "przeszukaj podkatalogi", 0, QApplication::UnicodeUTF8));
        checkBox_resize->setText(QApplication::translate("FCWindow", "zmniejsz rozmiar do:", 0, QApplication::UnicodeUTF8));
        checkBox_2JPG->setText(QApplication::translate("FCWindow", "konwertuj do JPG", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FCWindow", "px", 0, QApplication::UnicodeUTF8));
        pushButton_wybierz->setText(QApplication::translate("FCWindow", "Wybierz", 0, QApplication::UnicodeUTF8));
        checkBox_greyscale->setText(QApplication::translate("FCWindow", "do greyscale", 0, QApplication::UnicodeUTF8));
        znaleziono->setText(QApplication::translate("FCWindow", "Znaleziono", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FCWindow);
    } // retranslateUi

};

namespace Ui {
    class FCWindow: public Ui_FCWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCWINDOW_H
