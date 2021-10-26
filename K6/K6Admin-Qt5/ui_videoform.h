/********************************************************************************
** Form generated from reading UI file 'videoform.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOFORM_H
#define UI_VIDEOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *videoGroupBox;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *openAviButton;
    QLabel *aviLabel;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *convertButton;
    QCheckBox *wideCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *MP4label;
    QProgressBar *mp4ProgressBar;
    QHBoxLayout *horizontalLayout_9;
    QLabel *OGVlabel;
    QProgressBar *ogvProgressBar;
    QHBoxLayout *horizontalLayout_14;
    QLabel *WEBMlabel;
    QProgressBar *webmProgressBar;
    QTextBrowser *console;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QWidget *videoPlayer;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QLCDNumber *totalTimeMin;
    QLabel *label_4;
    QLCDNumber *totalTimeSec;
    QPushButton *stopklatkaButton;
    QGroupBox *fotkiGroupBox;
    QVBoxLayout *verticalLayout_10;
    QScrollArea *scrollArea_2;
    QWidget *fotkiScroll;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *fotkiList;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *fotkiDelSel;
    QPushButton *fotkiDelAll;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QWidget *VideoForm)
    {
        if (VideoForm->objectName().isEmpty())
            VideoForm->setObjectName(QStringLiteral("VideoForm"));
        VideoForm->resize(830, 560);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VideoForm->sizePolicy().hasHeightForWidth());
        VideoForm->setSizePolicy(sizePolicy);
        VideoForm->setMinimumSize(QSize(830, 560));
        verticalLayout = new QVBoxLayout(VideoForm);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        videoGroupBox = new QGroupBox(VideoForm);
        videoGroupBox->setObjectName(QStringLiteral("videoGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(videoGroupBox->sizePolicy().hasHeightForWidth());
        videoGroupBox->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(videoGroupBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(videoGroupBox);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 816, 529));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        openAviButton = new QPushButton(scrollAreaWidgetContents);
        openAviButton->setObjectName(QStringLiteral("openAviButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(openAviButton->sizePolicy().hasHeightForWidth());
        openAviButton->setSizePolicy(sizePolicy2);
        openAviButton->setMinimumSize(QSize(0, 24));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/win/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        openAviButton->setIcon(icon);

        horizontalLayout_5->addWidget(openAviButton);

        aviLabel = new QLabel(scrollAreaWidgetContents);
        aviLabel->setObjectName(QStringLiteral("aviLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(aviLabel->sizePolicy().hasHeightForWidth());
        aviLabel->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(aviLabel);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(3);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        convertButton = new QPushButton(scrollAreaWidgetContents);
        convertButton->setObjectName(QStringLiteral("convertButton"));
        sizePolicy2.setHeightForWidth(convertButton->sizePolicy().hasHeightForWidth());
        convertButton->setSizePolicy(sizePolicy2);
        convertButton->setMinimumSize(QSize(0, 24));

        horizontalLayout_3->addWidget(convertButton);

        wideCheckBox = new QCheckBox(scrollAreaWidgetContents);
        wideCheckBox->setObjectName(QStringLiteral("wideCheckBox"));

        horizontalLayout_3->addWidget(wideCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(3);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        MP4label = new QLabel(scrollAreaWidgetContents);
        MP4label->setObjectName(QStringLiteral("MP4label"));
        MP4label->setMinimumSize(QSize(80, 0));

        horizontalLayout_13->addWidget(MP4label);

        mp4ProgressBar = new QProgressBar(scrollAreaWidgetContents);
        mp4ProgressBar->setObjectName(QStringLiteral("mp4ProgressBar"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(mp4ProgressBar->sizePolicy().hasHeightForWidth());
        mp4ProgressBar->setSizePolicy(sizePolicy4);
        mp4ProgressBar->setMinimumSize(QSize(50, 0));
        mp4ProgressBar->setMaximumSize(QSize(16777215, 16777215));
        mp4ProgressBar->setValue(0);
        mp4ProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(mp4ProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(3);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        OGVlabel = new QLabel(scrollAreaWidgetContents);
        OGVlabel->setObjectName(QStringLiteral("OGVlabel"));
        OGVlabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_9->addWidget(OGVlabel);

        ogvProgressBar = new QProgressBar(scrollAreaWidgetContents);
        ogvProgressBar->setObjectName(QStringLiteral("ogvProgressBar"));
        ogvProgressBar->setValue(0);
        ogvProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(ogvProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(3);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        WEBMlabel = new QLabel(scrollAreaWidgetContents);
        WEBMlabel->setObjectName(QStringLiteral("WEBMlabel"));
        WEBMlabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_14->addWidget(WEBMlabel);

        webmProgressBar = new QProgressBar(scrollAreaWidgetContents);
        webmProgressBar->setObjectName(QStringLiteral("webmProgressBar"));
        webmProgressBar->setValue(0);
        webmProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(webmProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_14);


        horizontalLayout_15->addLayout(verticalLayout_2);

        console = new QTextBrowser(scrollAreaWidgetContents);
        console->setObjectName(QStringLiteral("console"));
        sizePolicy1.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy1);
        console->setMinimumSize(QSize(0, 108));
        console->setMaximumSize(QSize(16777215, 0));
        console->setOpenLinks(false);

        horizontalLayout_15->addWidget(console, 0, Qt::AlignTop);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        videoPlayer = new QWidget(scrollAreaWidgetContents);
        videoPlayer->setObjectName(QStringLiteral("videoPlayer"));
        sizePolicy1.setHeightForWidth(videoPlayer->sizePolicy().hasHeightForWidth());
        videoPlayer->setSizePolicy(sizePolicy1);
        videoPlayer->setMinimumSize(QSize(400, 226));
        videoPlayer->setMaximumSize(QSize(9999, 9999));
        videoPlayer->setBaseSize(QSize(0, 0));
        videoPlayer->setLayoutDirection(Qt::LeftToRight);
        videoPlayer->setAutoFillBackground(true);

        verticalLayout_5->addWidget(videoPlayer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        startButton = new QPushButton(scrollAreaWidgetContents);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy5);
        startButton->setMinimumSize(QSize(0, 20));
        startButton->setMaximumSize(QSize(30, 20));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon1);

        horizontalLayout_6->addWidget(startButton);

        pauseButton = new QPushButton(scrollAreaWidgetContents);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setMinimumSize(QSize(20, 20));
        pauseButton->setMaximumSize(QSize(16777215, 20));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon2);

        horizontalLayout_6->addWidget(pauseButton);

        totalTimeMin = new QLCDNumber(scrollAreaWidgetContents);
        totalTimeMin->setObjectName(QStringLiteral("totalTimeMin"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(totalTimeMin->sizePolicy().hasHeightForWidth());
        totalTimeMin->setSizePolicy(sizePolicy6);
        totalTimeMin->setMinimumSize(QSize(0, 20));
        totalTimeMin->setMaximumSize(QSize(16777215, 20));
        totalTimeMin->setFrameShape(QFrame::WinPanel);
        totalTimeMin->setFrameShadow(QFrame::Raised);
        totalTimeMin->setSmallDecimalPoint(false);
        totalTimeMin->setDigitCount(3);

        horizontalLayout_6->addWidget(totalTimeMin);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);
        label_4->setMinimumSize(QSize(0, 20));
        label_4->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_6->addWidget(label_4);

        totalTimeSec = new QLCDNumber(scrollAreaWidgetContents);
        totalTimeSec->setObjectName(QStringLiteral("totalTimeSec"));
        sizePolicy6.setHeightForWidth(totalTimeSec->sizePolicy().hasHeightForWidth());
        totalTimeSec->setSizePolicy(sizePolicy6);
        totalTimeSec->setMinimumSize(QSize(0, 20));
        totalTimeSec->setMaximumSize(QSize(16777215, 20));
        totalTimeSec->setFrameShape(QFrame::WinPanel);
        totalTimeSec->setFrameShadow(QFrame::Raised);
        totalTimeSec->setDigitCount(2);

        horizontalLayout_6->addWidget(totalTimeSec);

        stopklatkaButton = new QPushButton(scrollAreaWidgetContents);
        stopklatkaButton->setObjectName(QStringLiteral("stopklatkaButton"));
        stopklatkaButton->setMinimumSize(QSize(0, 20));
        stopklatkaButton->setMaximumSize(QSize(16777215, 20));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/insert-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopklatkaButton->setIcon(icon3);

        horizontalLayout_6->addWidget(stopklatkaButton);


        verticalLayout_5->addLayout(horizontalLayout_6);


        horizontalLayout->addLayout(verticalLayout_5);

        fotkiGroupBox = new QGroupBox(scrollAreaWidgetContents);
        fotkiGroupBox->setObjectName(QStringLiteral("fotkiGroupBox"));
        fotkiGroupBox->setMaximumSize(QSize(220, 16777215));
        verticalLayout_10 = new QVBoxLayout(fotkiGroupBox);
        verticalLayout_10->setSpacing(3);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(3, 3, 3, 3);
        scrollArea_2 = new QScrollArea(fotkiGroupBox);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        sizePolicy1.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy1);
        scrollArea_2->setWidgetResizable(true);
        fotkiScroll = new QWidget();
        fotkiScroll->setObjectName(QStringLiteral("fotkiScroll"));
        fotkiScroll->setGeometry(QRect(0, 0, 206, 330));
        verticalLayout_9 = new QVBoxLayout(fotkiScroll);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        fotkiList = new QVBoxLayout();
        fotkiList->setSpacing(3);
        fotkiList->setObjectName(QStringLiteral("fotkiList"));
        fotkiList->setSizeConstraint(QLayout::SetMinimumSize);
        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        fotkiList->addItem(verticalSpacer_3);


        verticalLayout_9->addLayout(fotkiList);

        scrollArea_2->setWidget(fotkiScroll);

        verticalLayout_10->addWidget(scrollArea_2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(3);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        fotkiDelSel = new QPushButton(fotkiGroupBox);
        fotkiDelSel->setObjectName(QStringLiteral("fotkiDelSel"));

        horizontalLayout_10->addWidget(fotkiDelSel);

        fotkiDelAll = new QPushButton(fotkiGroupBox);
        fotkiDelAll->setObjectName(QStringLiteral("fotkiDelAll"));

        horizontalLayout_10->addWidget(fotkiDelAll);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);


        verticalLayout_10->addLayout(horizontalLayout_10);


        horizontalLayout->addWidget(fotkiGroupBox);


        horizontalLayout_7->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(horizontalLayout_7);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        verticalLayout->addWidget(videoGroupBox);


        retranslateUi(VideoForm);

        QMetaObject::connectSlotsByName(VideoForm);
    } // setupUi

    void retranslateUi(QWidget *VideoForm)
    {
        VideoForm->setWindowTitle(QApplication::translate("VideoForm", "Form", 0));
        videoGroupBox->setTitle(QApplication::translate("VideoForm", "Video / Foto", 0));
        openAviButton->setText(QApplication::translate("VideoForm", "Wybierz plik video", 0));
        aviLabel->setText(QApplication::translate("VideoForm", "Plik", 0));
#ifndef QT_NO_TOOLTIP
        convertButton->setToolTip(QApplication::translate("VideoForm", "Nie musisz przygotowywa\304\207 plik\303\263w video na stron\304\231 na swoim komputerze. Je\305\233li tego nie zrobisz serwer sam je przygotuje, ale nie nast\304\205pi to natychmiast.", 0));
#endif // QT_NO_TOOLTIP
        convertButton->setText(QApplication::translate("VideoForm", "Przygotuj pliki video", 0));
        wideCheckBox->setText(QApplication::translate("VideoForm", "16:9", 0));
        MP4label->setText(QApplication::translate("VideoForm", "MP4", 0));
        OGVlabel->setText(QApplication::translate("VideoForm", "OGV", 0));
        WEBMlabel->setText(QApplication::translate("VideoForm", "WEBM", 0));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("VideoForm", "Play", 0));
#endif // QT_NO_TOOLTIP
        startButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pauseButton->setToolTip(QApplication::translate("VideoForm", "Pause", 0));
#endif // QT_NO_TOOLTIP
        pauseButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        totalTimeMin->setToolTip(QApplication::translate("VideoForm", "Czas ca\305\202kowity [min]", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("VideoForm", ":", 0));
#ifndef QT_NO_TOOLTIP
        totalTimeSec->setToolTip(QApplication::translate("VideoForm", "Czas ca\305\202kowity [sec]", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        stopklatkaButton->setToolTip(QApplication::translate("VideoForm", "Zapisz stopklatk\304\231", 0));
#endif // QT_NO_TOOLTIP
        stopklatkaButton->setText(QString());
        fotkiGroupBox->setTitle(QApplication::translate("VideoForm", "Fotki:", 0));
        fotkiDelSel->setText(QApplication::translate("VideoForm", "Skasuj", 0));
        fotkiDelAll->setText(QApplication::translate("VideoForm", "Wyczy\305\233\304\207", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoForm: public Ui_VideoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOFORM_H
