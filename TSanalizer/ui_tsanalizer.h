/********************************************************************************
** Form generated from reading UI file 'tsanalizer.ui'
**
** Created: Tue May 31 09:27:51 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TSANALIZER_H
#define UI_TSANALIZER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TsAnalizer
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_11;
    QSpinBox *PcktLimit;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_12;
    QLineEdit *PcktSize;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *onlydata;
    QPushButton *StartButton;
    QPushButton *BreakButton;
    QPushButton *ClearButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *SrcIP;
    QLineEdit *SrcPort;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_10;
    QLineEdit *DestIP;
    QLineEdit *DestPort;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_14;
    QLineEdit *Protocol;
    QCheckBox *Multicast;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_15;
    QLineEdit *ServIP;
    QLabel *label_16;
    QLineEdit *ServPort;
    QLabel *label_13;
    QComboBox *Interface;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *TsPID;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QRadioButton *FiltrALL;
    QRadioButton *FiltrAFE;
    QRadioButton *FiltrPAT;
    QRadioButton *FiltrPMT;
    QTextBrowser *console;

    void setupUi(QDialog *TsAnalizer)
    {
        if (TsAnalizer->objectName().isEmpty())
            TsAnalizer->setObjectName(QString::fromUtf8("TsAnalizer"));
        TsAnalizer->resize(712, 364);
        verticalLayout = new QVBoxLayout(TsAnalizer);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_11 = new QLabel(TsAnalizer);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_5->addWidget(label_11);

        PcktLimit = new QSpinBox(TsAnalizer);
        PcktLimit->setObjectName(QString::fromUtf8("PcktLimit"));
        PcktLimit->setMinimum(1);
        PcktLimit->setMaximum(999);

        horizontalLayout_5->addWidget(PcktLimit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        label_12 = new QLabel(TsAnalizer);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_5->addWidget(label_12);

        PcktSize = new QLineEdit(TsAnalizer);
        PcktSize->setObjectName(QString::fromUtf8("PcktSize"));

        horizontalLayout_5->addWidget(PcktSize);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        onlydata = new QCheckBox(TsAnalizer);
        onlydata->setObjectName(QString::fromUtf8("onlydata"));

        horizontalLayout_5->addWidget(onlydata);

        StartButton = new QPushButton(TsAnalizer);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));

        horizontalLayout_5->addWidget(StartButton);

        BreakButton = new QPushButton(TsAnalizer);
        BreakButton->setObjectName(QString::fromUtf8("BreakButton"));

        horizontalLayout_5->addWidget(BreakButton);

        ClearButton = new QPushButton(TsAnalizer);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));

        horizontalLayout_5->addWidget(ClearButton);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(TsAnalizer);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        SrcIP = new QLineEdit(TsAnalizer);
        SrcIP->setObjectName(QString::fromUtf8("SrcIP"));

        horizontalLayout_4->addWidget(SrcIP);

        SrcPort = new QLineEdit(TsAnalizer);
        SrcPort->setObjectName(QString::fromUtf8("SrcPort"));
        SrcPort->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(SrcPort);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        label_10 = new QLabel(TsAnalizer);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        DestIP = new QLineEdit(TsAnalizer);
        DestIP->setObjectName(QString::fromUtf8("DestIP"));

        horizontalLayout_4->addWidget(DestIP);

        DestPort = new QLineEdit(TsAnalizer);
        DestPort->setObjectName(QString::fromUtf8("DestPort"));
        DestPort->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(DestPort);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_14 = new QLabel(TsAnalizer);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_6->addWidget(label_14);

        Protocol = new QLineEdit(TsAnalizer);
        Protocol->setObjectName(QString::fromUtf8("Protocol"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Protocol->sizePolicy().hasHeightForWidth());
        Protocol->setSizePolicy(sizePolicy);
        Protocol->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_6->addWidget(Protocol);

        Multicast = new QCheckBox(TsAnalizer);
        Multicast->setObjectName(QString::fromUtf8("Multicast"));

        horizontalLayout_6->addWidget(Multicast);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);

        label_15 = new QLabel(TsAnalizer);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_6->addWidget(label_15);

        ServIP = new QLineEdit(TsAnalizer);
        ServIP->setObjectName(QString::fromUtf8("ServIP"));

        horizontalLayout_6->addWidget(ServIP);

        label_16 = new QLabel(TsAnalizer);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_6->addWidget(label_16);

        ServPort = new QLineEdit(TsAnalizer);
        ServPort->setObjectName(QString::fromUtf8("ServPort"));
        ServPort->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(ServPort);

        label_13 = new QLabel(TsAnalizer);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_6->addWidget(label_13);

        Interface = new QComboBox(TsAnalizer);
        Interface->setObjectName(QString::fromUtf8("Interface"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Interface->sizePolicy().hasHeightForWidth());
        Interface->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(Interface);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(TsAnalizer);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(TsAnalizer);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        TsPID = new QLineEdit(TsAnalizer);
        TsPID->setObjectName(QString::fromUtf8("TsPID"));

        horizontalLayout->addWidget(TsPID);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(TsAnalizer);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        FiltrALL = new QRadioButton(TsAnalizer);
        FiltrALL->setObjectName(QString::fromUtf8("FiltrALL"));

        horizontalLayout_2->addWidget(FiltrALL);

        FiltrAFE = new QRadioButton(TsAnalizer);
        FiltrAFE->setObjectName(QString::fromUtf8("FiltrAFE"));

        horizontalLayout_2->addWidget(FiltrAFE);

        FiltrPAT = new QRadioButton(TsAnalizer);
        FiltrPAT->setObjectName(QString::fromUtf8("FiltrPAT"));

        horizontalLayout_2->addWidget(FiltrPAT);

        FiltrPMT = new QRadioButton(TsAnalizer);
        FiltrPMT->setObjectName(QString::fromUtf8("FiltrPMT"));

        horizontalLayout_2->addWidget(FiltrPMT);


        horizontalLayout->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        console = new QTextBrowser(TsAnalizer);
        console->setObjectName(QString::fromUtf8("console"));

        verticalLayout->addWidget(console);


        retranslateUi(TsAnalizer);

        QMetaObject::connectSlotsByName(TsAnalizer);
    } // setupUi

    void retranslateUi(QDialog *TsAnalizer)
    {
        TsAnalizer->setWindowTitle(QApplication::translate("TsAnalizer", "TsAnalizer", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("TsAnalizer", "Pckt Limit", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("TsAnalizer", "Pckt Size", 0, QApplication::UnicodeUTF8));
        onlydata->setText(QApplication::translate("TsAnalizer", "tylko dane", 0, QApplication::UnicodeUTF8));
        StartButton->setText(QApplication::translate("TsAnalizer", "START", 0, QApplication::UnicodeUTF8));
        BreakButton->setText(QApplication::translate("TsAnalizer", "BREAK", 0, QApplication::UnicodeUTF8));
        ClearButton->setText(QApplication::translate("TsAnalizer", "Clear", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("TsAnalizer", "Source", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("TsAnalizer", "Dest", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("TsAnalizer", "Protocol", 0, QApplication::UnicodeUTF8));
        Multicast->setText(QApplication::translate("TsAnalizer", "Multicast", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("TsAnalizer", "Server", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("TsAnalizer", ":", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("TsAnalizer", "eth", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TsAnalizer", "Filtr:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TsAnalizer", "TS PID", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TsAnalizer", "Filtruj:", 0, QApplication::UnicodeUTF8));
        FiltrALL->setText(QApplication::translate("TsAnalizer", "ALL", 0, QApplication::UnicodeUTF8));
        FiltrAFE->setText(QApplication::translate("TsAnalizer", "AFE", 0, QApplication::UnicodeUTF8));
        FiltrPAT->setText(QApplication::translate("TsAnalizer", "PAT", 0, QApplication::UnicodeUTF8));
        FiltrPMT->setText(QApplication::translate("TsAnalizer", "PMT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TsAnalizer: public Ui_TsAnalizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TSANALIZER_H
