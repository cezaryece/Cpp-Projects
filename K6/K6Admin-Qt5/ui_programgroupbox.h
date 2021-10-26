/********************************************************************************
** Form generated from reading UI file 'programgroupbox.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMGROUPBOX_H
#define UI_PROGRAMGROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_programGroupBox
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *plikGroup;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *openAviButton;
    QLabel *nazwa_pliku;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *convertButton;
    QCheckBox *wideCheckBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *MP4label;
    QProgressBar *mp4ProgressBar;
    QHBoxLayout *horizontalLayout_5;
    QLabel *OGVlabel;
    QProgressBar *ogvProgressBar;
    QHBoxLayout *horizontalLayout_8;
    QLabel *WEBMlabel;
    QProgressBar *webmProgressBar;
    QSpacerItem *verticalSpacer;
    QTextBrowser *console;
    QHBoxLayout *horizontalLayout;
    QGroupBox *videoGroupBox;
    QVBoxLayout *verticalLayout_3;
    QWidget *videoPlayer;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QLCDNumber *totalTimeMin;
    QLabel *label_4;
    QLCDNumber *totalTimeSec;
    QPushButton *stopklatkaButton;
    QGroupBox *daneGroup;
    QVBoxLayout *verticalLayout_4;
    QLabel *tytulLabel;
    QLineEdit *tytulLineEdit;
    QLabel *label_3;
    QPlainTextEdit *opis;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *charTableButton;
    QLabel *cykleLabel;
    QComboBox *cykleCombo;
    QPushButton *katButton;
    QGroupBox *stopklatkaBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *stopKlatkaLabel;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QGroupBox *programGroupBox)
    {
        if (programGroupBox->objectName().isEmpty())
            programGroupBox->setObjectName(QStringLiteral("programGroupBox"));
        programGroupBox->resize(860, 640);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(programGroupBox->sizePolicy().hasHeightForWidth());
        programGroupBox->setSizePolicy(sizePolicy);
        programGroupBox->setMinimumSize(QSize(860, 640));
        programGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        programGroupBox->setFlat(true);
        verticalLayout = new QVBoxLayout(programGroupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(3, 0, 3, 0);
        plikGroup = new QGroupBox(programGroupBox);
        plikGroup->setObjectName(QStringLiteral("plikGroup"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plikGroup->sizePolicy().hasHeightForWidth());
        plikGroup->setSizePolicy(sizePolicy1);
        verticalLayout_7 = new QVBoxLayout(plikGroup);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(3, 0, 3, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(3);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        openAviButton = new QPushButton(plikGroup);
        openAviButton->setObjectName(QStringLiteral("openAviButton"));
        sizePolicy.setHeightForWidth(openAviButton->sizePolicy().hasHeightForWidth());
        openAviButton->setSizePolicy(sizePolicy);
        openAviButton->setMaximumSize(QSize(16777215, 22));

        horizontalLayout_9->addWidget(openAviButton);

        nazwa_pliku = new QLabel(plikGroup);
        nazwa_pliku->setObjectName(QStringLiteral("nazwa_pliku"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nazwa_pliku->sizePolicy().hasHeightForWidth());
        nazwa_pliku->setSizePolicy(sizePolicy2);

        horizontalLayout_9->addWidget(nazwa_pliku);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(3);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        convertButton = new QPushButton(plikGroup);
        convertButton->setObjectName(QStringLiteral("convertButton"));
        sizePolicy.setHeightForWidth(convertButton->sizePolicy().hasHeightForWidth());
        convertButton->setSizePolicy(sizePolicy);
        convertButton->setMaximumSize(QSize(16777215, 22));

        horizontalLayout_10->addWidget(convertButton);

        wideCheckBox = new QCheckBox(plikGroup);
        wideCheckBox->setObjectName(QStringLiteral("wideCheckBox"));

        horizontalLayout_10->addWidget(wideCheckBox);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        MP4label = new QLabel(plikGroup);
        MP4label->setObjectName(QStringLiteral("MP4label"));
        MP4label->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(MP4label);

        mp4ProgressBar = new QProgressBar(plikGroup);
        mp4ProgressBar->setObjectName(QStringLiteral("mp4ProgressBar"));
        sizePolicy1.setHeightForWidth(mp4ProgressBar->sizePolicy().hasHeightForWidth());
        mp4ProgressBar->setSizePolicy(sizePolicy1);
        mp4ProgressBar->setMinimumSize(QSize(50, 0));
        mp4ProgressBar->setMaximumSize(QSize(16777215, 16777215));
        mp4ProgressBar->setValue(0);
        mp4ProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(mp4ProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        OGVlabel = new QLabel(plikGroup);
        OGVlabel->setObjectName(QStringLiteral("OGVlabel"));
        OGVlabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_5->addWidget(OGVlabel);

        ogvProgressBar = new QProgressBar(plikGroup);
        ogvProgressBar->setObjectName(QStringLiteral("ogvProgressBar"));
        ogvProgressBar->setValue(0);
        ogvProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(ogvProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        WEBMlabel = new QLabel(plikGroup);
        WEBMlabel->setObjectName(QStringLiteral("WEBMlabel"));
        WEBMlabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_8->addWidget(WEBMlabel);

        webmProgressBar = new QProgressBar(plikGroup);
        webmProgressBar->setObjectName(QStringLiteral("webmProgressBar"));
        webmProgressBar->setValue(0);
        webmProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(webmProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_11->addLayout(verticalLayout_2);

        console = new QTextBrowser(plikGroup);
        console->setObjectName(QStringLiteral("console"));
        sizePolicy1.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy1);
        console->setMinimumSize(QSize(0, 60));
        console->setOpenLinks(false);

        horizontalLayout_11->addWidget(console);


        verticalLayout_7->addLayout(horizontalLayout_11);


        verticalLayout->addWidget(plikGroup);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        videoGroupBox = new QGroupBox(programGroupBox);
        videoGroupBox->setObjectName(QStringLiteral("videoGroupBox"));
        sizePolicy1.setHeightForWidth(videoGroupBox->sizePolicy().hasHeightForWidth());
        videoGroupBox->setSizePolicy(sizePolicy1);
        videoGroupBox->setMinimumSize(QSize(360, 369));
        videoGroupBox->setMaximumSize(QSize(999, 369));
        videoGroupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        verticalLayout_3 = new QVBoxLayout(videoGroupBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 0, 3, 0);
        videoPlayer = new QWidget(videoGroupBox);
        videoPlayer->setObjectName(QStringLiteral("videoPlayer"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(videoPlayer->sizePolicy().hasHeightForWidth());
        videoPlayer->setSizePolicy(sizePolicy3);
        videoPlayer->setMinimumSize(QSize(400, 226));
        videoPlayer->setBaseSize(QSize(0, 0));
        videoPlayer->setAutoFillBackground(true);

        verticalLayout_3->addWidget(videoPlayer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        startButton = new QPushButton(videoGroupBox);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy4);
        startButton->setMaximumSize(QSize(30, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon);

        horizontalLayout_6->addWidget(startButton);

        pauseButton = new QPushButton(videoGroupBox);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setMinimumSize(QSize(20, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon1);

        horizontalLayout_6->addWidget(pauseButton);

        totalTimeMin = new QLCDNumber(videoGroupBox);
        totalTimeMin->setObjectName(QStringLiteral("totalTimeMin"));
        totalTimeMin->setMaximumSize(QSize(16777215, 28));
        totalTimeMin->setFrameShape(QFrame::WinPanel);
        totalTimeMin->setFrameShadow(QFrame::Raised);
        totalTimeMin->setSmallDecimalPoint(false);
        totalTimeMin->setDigitCount(3);

        horizontalLayout_6->addWidget(totalTimeMin);

        label_4 = new QLabel(videoGroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy4.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy4);

        horizontalLayout_6->addWidget(label_4);

        totalTimeSec = new QLCDNumber(videoGroupBox);
        totalTimeSec->setObjectName(QStringLiteral("totalTimeSec"));
        totalTimeSec->setMaximumSize(QSize(16777215, 28));
        totalTimeSec->setFrameShape(QFrame::WinPanel);
        totalTimeSec->setFrameShadow(QFrame::Raised);
        totalTimeSec->setDigitCount(2);

        horizontalLayout_6->addWidget(totalTimeSec);

        stopklatkaButton = new QPushButton(videoGroupBox);
        stopklatkaButton->setObjectName(QStringLiteral("stopklatkaButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/insert-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopklatkaButton->setIcon(icon2);

        horizontalLayout_6->addWidget(stopklatkaButton);


        verticalLayout_5->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_5);


        verticalLayout_3->addLayout(horizontalLayout_7);


        horizontalLayout->addWidget(videoGroupBox);

        daneGroup = new QGroupBox(programGroupBox);
        daneGroup->setObjectName(QStringLiteral("daneGroup"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(daneGroup->sizePolicy().hasHeightForWidth());
        daneGroup->setSizePolicy(sizePolicy5);
        daneGroup->setMinimumSize(QSize(0, 280));
        verticalLayout_4 = new QVBoxLayout(daneGroup);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, 0, 3, 0);
        tytulLabel = new QLabel(daneGroup);
        tytulLabel->setObjectName(QStringLiteral("tytulLabel"));

        verticalLayout_4->addWidget(tytulLabel);

        tytulLineEdit = new QLineEdit(daneGroup);
        tytulLineEdit->setObjectName(QStringLiteral("tytulLineEdit"));
        sizePolicy1.setHeightForWidth(tytulLineEdit->sizePolicy().hasHeightForWidth());
        tytulLineEdit->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(tytulLineEdit);

        label_3 = new QLabel(daneGroup);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);

        opis = new QPlainTextEdit(daneGroup);
        opis->setObjectName(QStringLiteral("opis"));
        sizePolicy5.setHeightForWidth(opis->sizePolicy().hasHeightForWidth());
        opis->setSizePolicy(sizePolicy5);
        opis->setMinimumSize(QSize(0, 0));

        verticalLayout_4->addWidget(opis);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        charTableButton = new QToolButton(daneGroup);
        charTableButton->setObjectName(QStringLiteral("charTableButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/character-set.png"), QSize(), QIcon::Normal, QIcon::Off);
        charTableButton->setIcon(icon3);

        horizontalLayout_2->addWidget(charTableButton);

        cykleLabel = new QLabel(daneGroup);
        cykleLabel->setObjectName(QStringLiteral("cykleLabel"));
        cykleLabel->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_2->addWidget(cykleLabel);

        cykleCombo = new QComboBox(daneGroup);
        cykleCombo->setObjectName(QStringLiteral("cykleCombo"));
        cykleCombo->setEditable(true);

        horizontalLayout_2->addWidget(cykleCombo);

        katButton = new QPushButton(daneGroup);
        katButton->setObjectName(QStringLiteral("katButton"));

        horizontalLayout_2->addWidget(katButton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        stopklatkaBox = new QGroupBox(daneGroup);
        stopklatkaBox->setObjectName(QStringLiteral("stopklatkaBox"));
        stopklatkaBox->setMinimumSize(QSize(0, 92));
        stopklatkaBox->setMaximumSize(QSize(16777215, 92));
        stopklatkaBox->setBaseSize(QSize(0, 90));
        horizontalLayout_3 = new QHBoxLayout(stopklatkaBox);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 0, 2, 0);
        stopKlatkaLabel = new QLabel(stopklatkaBox);
        stopKlatkaLabel->setObjectName(QStringLiteral("stopKlatkaLabel"));
        stopKlatkaLabel->setMinimumSize(QSize(140, 72));
        stopKlatkaLabel->setMaximumSize(QSize(16777215, 72));
        stopKlatkaLabel->setBaseSize(QSize(0, 72));

        horizontalLayout_3->addWidget(stopKlatkaLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_4->addWidget(stopklatkaBox);


        horizontalLayout->addWidget(daneGroup, 0, Qt::AlignTop);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(programGroupBox);

        QMetaObject::connectSlotsByName(programGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *programGroupBox)
    {
        programGroupBox->setWindowTitle(QApplication::translate("programGroupBox", "GroupBox", 0));
        programGroupBox->setTitle(QString());
        plikGroup->setTitle(QApplication::translate("programGroupBox", "Plik", 0));
        openAviButton->setText(QApplication::translate("programGroupBox", "Otw\303\263rz z dysku", 0));
        nazwa_pliku->setText(QApplication::translate("programGroupBox", "Brak pliku", 0));
        convertButton->setText(QApplication::translate("programGroupBox", "Konwertuj video", 0));
        wideCheckBox->setText(QApplication::translate("programGroupBox", "16:9", 0));
        MP4label->setText(QApplication::translate("programGroupBox", "MP4", 0));
        OGVlabel->setText(QApplication::translate("programGroupBox", "OGV", 0));
        WEBMlabel->setText(QApplication::translate("programGroupBox", "WEBM", 0));
        videoGroupBox->setTitle(QApplication::translate("programGroupBox", "Odtwarzacz", 0));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("programGroupBox", "Play", 0));
#endif // QT_NO_TOOLTIP
        startButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pauseButton->setToolTip(QApplication::translate("programGroupBox", "Pause", 0));
#endif // QT_NO_TOOLTIP
        pauseButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        totalTimeMin->setToolTip(QApplication::translate("programGroupBox", "Czas ca\305\202kowity [min]", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("programGroupBox", ":", 0));
#ifndef QT_NO_TOOLTIP
        totalTimeSec->setToolTip(QApplication::translate("programGroupBox", "Czas ca\305\202kowity [sec]", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        stopklatkaButton->setToolTip(QApplication::translate("programGroupBox", "Zapisz stopklatk\304\231", 0));
#endif // QT_NO_TOOLTIP
        stopklatkaButton->setText(QString());
        daneGroup->setTitle(QApplication::translate("programGroupBox", "Dane do bazy", 0));
        tytulLabel->setText(QApplication::translate("programGroupBox", "Tytu\305\202", 0));
        tytulLineEdit->setPlaceholderText(QApplication::translate("programGroupBox", "Podaj tytu\305\202 programu", 0));
        label_3->setText(QApplication::translate("programGroupBox", "Opis", 0));
        charTableButton->setText(QApplication::translate("programGroupBox", "...", 0));
        cykleLabel->setText(QApplication::translate("programGroupBox", "Z cyklu:", 0));
#ifndef QT_NO_TOOLTIP
        cykleCombo->setToolTip(QApplication::translate("programGroupBox", "Wybierz lub wpisz tytu\305\202 nowego cyklu", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        cykleCombo->setAccessibleName(QApplication::translate("programGroupBox", "Wybierz lub wpisz tytu\305\202 nowego cyklu", 0));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        cykleCombo->setAccessibleDescription(QApplication::translate("programGroupBox", "Wybierz lub wpisz tytu\305\202 nowego cyklu", 0));
#endif // QT_NO_ACCESSIBILITY
        katButton->setText(QApplication::translate("programGroupBox", "KATEGORIE", 0));
        stopklatkaBox->setTitle(QApplication::translate("programGroupBox", "Stopklatka", 0));
        stopKlatkaLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class programGroupBox: public Ui_programGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMGROUPBOX_H
