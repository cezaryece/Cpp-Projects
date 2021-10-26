/********************************************************************************
** Form generated from reading UI file 'newsgroupbox.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSGROUPBOX_H
#define UI_NEWSGROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newsGroupBox
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *tytulLabel;
    QLineEdit *tytulLineEdit;
    QLabel *miastoLabel;
    QComboBox *miastoComboBox;
    QPushButton *katButton;
    QGroupBox *datyGroupBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDateEdit *dataEdit;
    QFrame *line;
    QCheckBox *waznyCheckBox;
    QDateTimeEdit *waznyDataCzasEdit;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *lastMinuteCheckBox;
    QFrame *line_5;
    QCheckBox *acceptCheckBox;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *imprezaGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *imprezaNazwaLineEdit;
    QDateEdit *imprezaDataEdit;
    QCheckBox *patronatCheckBox;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *autorLabel;
    QLineEdit *autorLineEdit;
    QGroupBox *trescGroup;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *boldButton;
    QToolButton *italicButton;
    QToolButton *underlineButton;
    QFrame *line_2;
    QToolButton *leftButton;
    QToolButton *centerButton;
    QToolButton *rightButton;
    QToolButton *justifyButton;
    QFrame *line_3;
    QToolButton *colorButton;
    QComboBox *comboStyle;
    QFrame *line_4;
    QToolButton *charTableButton;
    QSpacerItem *horizontalSpacer_8;
    QTextEdit *textEdit;
    QGroupBox *videoGroupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *openAviButton;
    QLabel *aviLabel;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *aviNoSaveCheckBox;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *convertButton;
    QCheckBox *wideCheckBox;
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
    QGroupBox *playerGroup;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *playerLayout;
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
    QPushButton *zdyskuButton;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QGroupBox *newsGroupBox)
    {
        if (newsGroupBox->objectName().isEmpty())
            newsGroupBox->setObjectName(QStringLiteral("newsGroupBox"));
        newsGroupBox->resize(830, 762);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newsGroupBox->sizePolicy().hasHeightForWidth());
        newsGroupBox->setSizePolicy(sizePolicy);
        newsGroupBox->setMinimumSize(QSize(830, 560));
        newsGroupBox->setMaximumSize(QSize(16777215, 9999));
        newsGroupBox->setFlat(true);
        verticalLayout = new QVBoxLayout(newsGroupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(newsGroupBox);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 822, 737));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(3);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tytulLabel = new QLabel(scrollAreaWidgetContents);
        tytulLabel->setObjectName(QStringLiteral("tytulLabel"));

        horizontalLayout->addWidget(tytulLabel);

        tytulLineEdit = new QLineEdit(scrollAreaWidgetContents);
        tytulLineEdit->setObjectName(QStringLiteral("tytulLineEdit"));

        horizontalLayout->addWidget(tytulLineEdit);

        miastoLabel = new QLabel(scrollAreaWidgetContents);
        miastoLabel->setObjectName(QStringLiteral("miastoLabel"));

        horizontalLayout->addWidget(miastoLabel);

        miastoComboBox = new QComboBox(scrollAreaWidgetContents);
        miastoComboBox->setObjectName(QStringLiteral("miastoComboBox"));
        miastoComboBox->setEditable(true);

        horizontalLayout->addWidget(miastoComboBox);

        katButton = new QPushButton(scrollAreaWidgetContents);
        katButton->setObjectName(QStringLiteral("katButton"));

        horizontalLayout->addWidget(katButton);


        verticalLayout_6->addLayout(horizontalLayout);

        datyGroupBox = new QGroupBox(scrollAreaWidgetContents);
        datyGroupBox->setObjectName(QStringLiteral("datyGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(datyGroupBox->sizePolicy().hasHeightForWidth());
        datyGroupBox->setSizePolicy(sizePolicy1);
        verticalLayout_7 = new QVBoxLayout(datyGroupBox);
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(datyGroupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        dataEdit = new QDateEdit(datyGroupBox);
        dataEdit->setObjectName(QStringLiteral("dataEdit"));
        dataEdit->setCalendarPopup(true);

        horizontalLayout_2->addWidget(dataEdit);

        line = new QFrame(datyGroupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        waznyCheckBox = new QCheckBox(datyGroupBox);
        waznyCheckBox->setObjectName(QStringLiteral("waznyCheckBox"));

        horizontalLayout_2->addWidget(waznyCheckBox);

        waznyDataCzasEdit = new QDateTimeEdit(datyGroupBox);
        waznyDataCzasEdit->setObjectName(QStringLiteral("waznyDataCzasEdit"));
        waznyDataCzasEdit->setCalendarPopup(true);

        horizontalLayout_2->addWidget(waznyDataCzasEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(3);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        lastMinuteCheckBox = new QCheckBox(datyGroupBox);
        lastMinuteCheckBox->setObjectName(QStringLiteral("lastMinuteCheckBox"));

        horizontalLayout_12->addWidget(lastMinuteCheckBox);

        line_5 = new QFrame(datyGroupBox);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_12->addWidget(line_5);

        acceptCheckBox = new QCheckBox(datyGroupBox);
        acceptCheckBox->setObjectName(QStringLiteral("acceptCheckBox"));

        horizontalLayout_12->addWidget(acceptCheckBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_4);


        verticalLayout_7->addLayout(horizontalLayout_12);


        verticalLayout_6->addWidget(datyGroupBox);

        imprezaGroupBox = new QGroupBox(scrollAreaWidgetContents);
        imprezaGroupBox->setObjectName(QStringLiteral("imprezaGroupBox"));
        sizePolicy1.setHeightForWidth(imprezaGroupBox->sizePolicy().hasHeightForWidth());
        imprezaGroupBox->setSizePolicy(sizePolicy1);
        imprezaGroupBox->setCheckable(true);
        imprezaGroupBox->setChecked(false);
        horizontalLayout_4 = new QHBoxLayout(imprezaGroupBox);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(3, 3, 3, 3);
        imprezaNazwaLineEdit = new QLineEdit(imprezaGroupBox);
        imprezaNazwaLineEdit->setObjectName(QStringLiteral("imprezaNazwaLineEdit"));

        horizontalLayout_4->addWidget(imprezaNazwaLineEdit);

        imprezaDataEdit = new QDateEdit(imprezaGroupBox);
        imprezaDataEdit->setObjectName(QStringLiteral("imprezaDataEdit"));
        imprezaDataEdit->setCalendarPopup(true);

        horizontalLayout_4->addWidget(imprezaDataEdit);

        patronatCheckBox = new QCheckBox(imprezaGroupBox);
        patronatCheckBox->setObjectName(QStringLiteral("patronatCheckBox"));

        horizontalLayout_4->addWidget(patronatCheckBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_6->addWidget(imprezaGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        autorLabel = new QLabel(scrollAreaWidgetContents);
        autorLabel->setObjectName(QStringLiteral("autorLabel"));

        horizontalLayout_3->addWidget(autorLabel);

        autorLineEdit = new QLineEdit(scrollAreaWidgetContents);
        autorLineEdit->setObjectName(QStringLiteral("autorLineEdit"));

        horizontalLayout_3->addWidget(autorLineEdit);


        verticalLayout_6->addLayout(horizontalLayout_3);


        horizontalLayout_11->addLayout(verticalLayout_6);

        trescGroup = new QGroupBox(scrollAreaWidgetContents);
        trescGroup->setObjectName(QStringLiteral("trescGroup"));
        sizePolicy1.setHeightForWidth(trescGroup->sizePolicy().hasHeightForWidth());
        trescGroup->setSizePolicy(sizePolicy1);
        verticalLayout_8 = new QVBoxLayout(trescGroup);
        verticalLayout_8->setSpacing(3);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(3, 0, 3, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(3);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        boldButton = new QToolButton(trescGroup);
        boldButton->setObjectName(QStringLiteral("boldButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/textbold.png"), QSize(), QIcon::Normal, QIcon::Off);
        boldButton->setIcon(icon);
        boldButton->setCheckable(true);

        horizontalLayout_8->addWidget(boldButton);

        italicButton = new QToolButton(trescGroup);
        italicButton->setObjectName(QStringLiteral("italicButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/textitalic.png"), QSize(), QIcon::Normal, QIcon::Off);
        italicButton->setIcon(icon1);
        italicButton->setCheckable(true);

        horizontalLayout_8->addWidget(italicButton);

        underlineButton = new QToolButton(trescGroup);
        underlineButton->setObjectName(QStringLiteral("underlineButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/textunder.png"), QSize(), QIcon::Normal, QIcon::Off);
        underlineButton->setIcon(icon2);
        underlineButton->setCheckable(true);

        horizontalLayout_8->addWidget(underlineButton);

        line_2 = new QFrame(trescGroup);
        line_2->setObjectName(QStringLiteral("line_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy2);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line_2);

        leftButton = new QToolButton(trescGroup);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/textleft.png"), QSize(), QIcon::Normal, QIcon::Off);
        leftButton->setIcon(icon3);
        leftButton->setCheckable(true);

        horizontalLayout_8->addWidget(leftButton);

        centerButton = new QToolButton(trescGroup);
        centerButton->setObjectName(QStringLiteral("centerButton"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/textcenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        centerButton->setIcon(icon4);
        centerButton->setCheckable(true);

        horizontalLayout_8->addWidget(centerButton);

        rightButton = new QToolButton(trescGroup);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/textright.png"), QSize(), QIcon::Normal, QIcon::Off);
        rightButton->setIcon(icon5);
        rightButton->setCheckable(true);

        horizontalLayout_8->addWidget(rightButton);

        justifyButton = new QToolButton(trescGroup);
        justifyButton->setObjectName(QStringLiteral("justifyButton"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/textjustify.png"), QSize(), QIcon::Normal, QIcon::Off);
        justifyButton->setIcon(icon6);
        justifyButton->setCheckable(true);

        horizontalLayout_8->addWidget(justifyButton);

        line_3 = new QFrame(trescGroup);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line_3);

        colorButton = new QToolButton(trescGroup);
        colorButton->setObjectName(QStringLiteral("colorButton"));

        horizontalLayout_8->addWidget(colorButton);

        comboStyle = new QComboBox(trescGroup);
        comboStyle->setObjectName(QStringLiteral("comboStyle"));

        horizontalLayout_8->addWidget(comboStyle);

        line_4 = new QFrame(trescGroup);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line_4);

        charTableButton = new QToolButton(trescGroup);
        charTableButton->setObjectName(QStringLiteral("charTableButton"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/character-set.png"), QSize(), QIcon::Normal, QIcon::Off);
        charTableButton->setIcon(icon7);
        charTableButton->setCheckable(true);

        horizontalLayout_8->addWidget(charTableButton);

        horizontalSpacer_8 = new QSpacerItem(20, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_8->addLayout(horizontalLayout_8);

        textEdit = new QTextEdit(trescGroup);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy3);
        textEdit->setMinimumSize(QSize(0, 20));
        textEdit->setMaximumSize(QSize(16777215, 180));

        verticalLayout_8->addWidget(textEdit);


        horizontalLayout_11->addWidget(trescGroup);


        verticalLayout_4->addLayout(horizontalLayout_11);

        videoGroupBox = new QGroupBox(scrollAreaWidgetContents);
        videoGroupBox->setObjectName(QStringLiteral("videoGroupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(videoGroupBox->sizePolicy().hasHeightForWidth());
        videoGroupBox->setSizePolicy(sizePolicy4);
        verticalLayout_3 = new QVBoxLayout(videoGroupBox);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 0, 3, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        openAviButton = new QPushButton(videoGroupBox);
        openAviButton->setObjectName(QStringLiteral("openAviButton"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(openAviButton->sizePolicy().hasHeightForWidth());
        openAviButton->setSizePolicy(sizePolicy5);
        openAviButton->setMinimumSize(QSize(0, 24));

        horizontalLayout_5->addWidget(openAviButton);

        aviLabel = new QLabel(videoGroupBox);
        aviLabel->setObjectName(QStringLiteral("aviLabel"));

        horizontalLayout_5->addWidget(aviLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        aviNoSaveCheckBox = new QCheckBox(videoGroupBox);
        aviNoSaveCheckBox->setObjectName(QStringLiteral("aviNoSaveCheckBox"));

        horizontalLayout_5->addWidget(aviNoSaveCheckBox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(3);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        convertButton = new QPushButton(videoGroupBox);
        convertButton->setObjectName(QStringLiteral("convertButton"));
        sizePolicy5.setHeightForWidth(convertButton->sizePolicy().hasHeightForWidth());
        convertButton->setSizePolicy(sizePolicy5);
        convertButton->setMinimumSize(QSize(0, 24));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/win/video-x-mng.png"), QSize(), QIcon::Normal, QIcon::Off);
        convertButton->setIcon(icon8);

        horizontalLayout_16->addWidget(convertButton);

        wideCheckBox = new QCheckBox(videoGroupBox);
        wideCheckBox->setObjectName(QStringLiteral("wideCheckBox"));

        horizontalLayout_16->addWidget(wideCheckBox);


        verticalLayout_2->addLayout(horizontalLayout_16);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(3);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        MP4label = new QLabel(videoGroupBox);
        MP4label->setObjectName(QStringLiteral("MP4label"));
        MP4label->setMinimumSize(QSize(80, 0));

        horizontalLayout_13->addWidget(MP4label);

        mp4ProgressBar = new QProgressBar(videoGroupBox);
        mp4ProgressBar->setObjectName(QStringLiteral("mp4ProgressBar"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(mp4ProgressBar->sizePolicy().hasHeightForWidth());
        mp4ProgressBar->setSizePolicy(sizePolicy6);
        mp4ProgressBar->setMinimumSize(QSize(50, 0));
        mp4ProgressBar->setMaximumSize(QSize(16777215, 16777215));
        mp4ProgressBar->setValue(0);
        mp4ProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(mp4ProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(3);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        OGVlabel = new QLabel(videoGroupBox);
        OGVlabel->setObjectName(QStringLiteral("OGVlabel"));
        OGVlabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_9->addWidget(OGVlabel);

        ogvProgressBar = new QProgressBar(videoGroupBox);
        ogvProgressBar->setObjectName(QStringLiteral("ogvProgressBar"));
        ogvProgressBar->setValue(0);
        ogvProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(ogvProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(3);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        WEBMlabel = new QLabel(videoGroupBox);
        WEBMlabel->setObjectName(QStringLiteral("WEBMlabel"));
        WEBMlabel->setMinimumSize(QSize(80, 0));

        horizontalLayout_14->addWidget(WEBMlabel);

        webmProgressBar = new QProgressBar(videoGroupBox);
        webmProgressBar->setObjectName(QStringLiteral("webmProgressBar"));
        webmProgressBar->setValue(0);
        webmProgressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(webmProgressBar);


        verticalLayout_2->addLayout(horizontalLayout_14);


        horizontalLayout_15->addLayout(verticalLayout_2);

        console = new QTextBrowser(videoGroupBox);
        console->setObjectName(QStringLiteral("console"));
        sizePolicy6.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy6);
        console->setMinimumSize(QSize(0, 100));
        console->setMaximumSize(QSize(16777215, 100));
        console->setOpenLinks(false);

        horizontalLayout_15->addWidget(console);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        playerGroup = new QGroupBox(videoGroupBox);
        playerGroup->setObjectName(QStringLiteral("playerGroup"));
        sizePolicy4.setHeightForWidth(playerGroup->sizePolicy().hasHeightForWidth());
        playerGroup->setSizePolicy(sizePolicy4);
        verticalLayout_5 = new QVBoxLayout(playerGroup);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        playerLayout = new QHBoxLayout();
        playerLayout->setSpacing(3);
        playerLayout->setObjectName(QStringLiteral("playerLayout"));
        startButton = new QPushButton(playerGroup);
        startButton->setObjectName(QStringLiteral("startButton"));
        sizePolicy1.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy1);
        startButton->setMinimumSize(QSize(24, 24));
        startButton->setMaximumSize(QSize(24, 24));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon9);
        startButton->setFlat(false);

        playerLayout->addWidget(startButton);

        pauseButton = new QPushButton(playerGroup);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setMinimumSize(QSize(24, 24));
        pauseButton->setMaximumSize(QSize(24, 24));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon10);
        pauseButton->setFlat(false);

        playerLayout->addWidget(pauseButton);

        totalTimeMin = new QLCDNumber(playerGroup);
        totalTimeMin->setObjectName(QStringLiteral("totalTimeMin"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(totalTimeMin->sizePolicy().hasHeightForWidth());
        totalTimeMin->setSizePolicy(sizePolicy7);
        totalTimeMin->setFrameShape(QFrame::WinPanel);
        totalTimeMin->setFrameShadow(QFrame::Raised);
        totalTimeMin->setSmallDecimalPoint(false);
        totalTimeMin->setDigitCount(3);

        playerLayout->addWidget(totalTimeMin);

        label_4 = new QLabel(playerGroup);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        playerLayout->addWidget(label_4);

        totalTimeSec = new QLCDNumber(playerGroup);
        totalTimeSec->setObjectName(QStringLiteral("totalTimeSec"));
        sizePolicy7.setHeightForWidth(totalTimeSec->sizePolicy().hasHeightForWidth());
        totalTimeSec->setSizePolicy(sizePolicy7);
        totalTimeSec->setFrameShape(QFrame::WinPanel);
        totalTimeSec->setFrameShadow(QFrame::Raised);
        totalTimeSec->setDigitCount(2);

        playerLayout->addWidget(totalTimeSec);

        stopklatkaButton = new QPushButton(playerGroup);
        stopklatkaButton->setObjectName(QStringLiteral("stopklatkaButton"));
        stopklatkaButton->setMinimumSize(QSize(24, 24));
        stopklatkaButton->setMaximumSize(QSize(24, 24));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/insert-image.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopklatkaButton->setIcon(icon11);
        stopklatkaButton->setFlat(false);

        playerLayout->addWidget(stopklatkaButton);


        verticalLayout_5->addLayout(playerLayout);


        horizontalLayout_7->addWidget(playerGroup);

        fotkiGroupBox = new QGroupBox(videoGroupBox);
        fotkiGroupBox->setObjectName(QStringLiteral("fotkiGroupBox"));
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(fotkiGroupBox->sizePolicy().hasHeightForWidth());
        fotkiGroupBox->setSizePolicy(sizePolicy8);
        fotkiGroupBox->setMinimumSize(QSize(250, 0));
        fotkiGroupBox->setMaximumSize(QSize(250, 16777215));
        verticalLayout_10 = new QVBoxLayout(fotkiGroupBox);
        verticalLayout_10->setSpacing(3);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(3, 0, 3, 0);
        scrollArea_2 = new QScrollArea(fotkiGroupBox);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        fotkiScroll = new QWidget();
        fotkiScroll->setObjectName(QStringLiteral("fotkiScroll"));
        fotkiScroll->setGeometry(QRect(0, 0, 236, 275));
        verticalLayout_9 = new QVBoxLayout(fotkiScroll);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        fotkiList = new QVBoxLayout();
        fotkiList->setSpacing(3);
        fotkiList->setObjectName(QStringLiteral("fotkiList"));
        fotkiList->setSizeConstraint(QLayout::SetMinimumSize);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

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

        zdyskuButton = new QPushButton(fotkiGroupBox);
        zdyskuButton->setObjectName(QStringLiteral("zdyskuButton"));

        horizontalLayout_10->addWidget(zdyskuButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);


        verticalLayout_10->addLayout(horizontalLayout_10);


        horizontalLayout_7->addWidget(fotkiGroupBox);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_4->addWidget(videoGroupBox);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(newsGroupBox);

        QMetaObject::connectSlotsByName(newsGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *newsGroupBox)
    {
        newsGroupBox->setWindowTitle(QApplication::translate("newsGroupBox", "GroupBox", 0));
        newsGroupBox->setTitle(QString());
        tytulLabel->setText(QApplication::translate("newsGroupBox", "Tytu\305\202: ", 0));
        tytulLineEdit->setPlaceholderText(QApplication::translate("newsGroupBox", "Podaj tytu\305\202", 0));
        miastoLabel->setText(QApplication::translate("newsGroupBox", "Miasto", 0));
#ifndef QT_NO_TOOLTIP
        miastoComboBox->setToolTip(QApplication::translate("newsGroupBox", "Wybierz miasto z listy lub wpisz r\304\231cznie.", 0));
#endif // QT_NO_TOOLTIP
        katButton->setText(QApplication::translate("newsGroupBox", "KATEGORIE", 0));
        datyGroupBox->setTitle(QApplication::translate("newsGroupBox", "Daty", 0));
        label->setText(QApplication::translate("newsGroupBox", "Data:", 0));
#ifndef QT_NO_TOOLTIP
        waznyCheckBox->setToolTip(QApplication::translate("newsGroupBox", "W\304\205\305\274ny promuje newsa przez okreslony czas.", 0));
#endif // QT_NO_TOOLTIP
        waznyCheckBox->setText(QApplication::translate("newsGroupBox", "Wyr\303\263\305\274nij a\305\274 do:", 0));
#ifndef QT_NO_TOOLTIP
        lastMinuteCheckBox->setToolTip(QApplication::translate("newsGroupBox", "Infomacja b\304\231dzie pokazana w okienku \"W nast\304\231pnych Faktach Dnia\" do godz. 17 nastepnego dnia, kiedy przekszta\305\202ci si\304\231 w zwyk\305\202ego newsa.", 0));
#endif // QT_NO_TOOLTIP
        lastMinuteCheckBox->setText(QApplication::translate("newsGroupBox", "Last Minute", 0));
#ifndef QT_NO_TOOLTIP
        acceptCheckBox->setToolTip(QApplication::translate("newsGroupBox", "Tylko informacje z akceptacja wy\305\233wietlaj\304\205 si\304\231 na stronie.", 0));
#endif // QT_NO_TOOLTIP
        acceptCheckBox->setText(QApplication::translate("newsGroupBox", "Akceptuj", 0));
        imprezaGroupBox->setTitle(QApplication::translate("newsGroupBox", "Impreza / Patronat", 0));
        imprezaNazwaLineEdit->setPlaceholderText(QApplication::translate("newsGroupBox", "Nazwa imprezy", 0));
        patronatCheckBox->setText(QApplication::translate("newsGroupBox", "Patronat K6", 0));
        autorLabel->setText(QApplication::translate("newsGroupBox", "Autor:", 0));
        autorLineEdit->setPlaceholderText(QApplication::translate("newsGroupBox", "Podaj autora newsa", 0));
        trescGroup->setTitle(QApplication::translate("newsGroupBox", "Tre\305\233\304\207", 0));
        boldButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        italicButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        underlineButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        leftButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        centerButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        rightButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        justifyButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        colorButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        charTableButton->setText(QApplication::translate("newsGroupBox", "...", 0));
        videoGroupBox->setTitle(QApplication::translate("newsGroupBox", "Video / Foto", 0));
        openAviButton->setText(QApplication::translate("newsGroupBox", "Wybierz plik video", 0));
        aviLabel->setText(QApplication::translate("newsGroupBox", "Plik", 0));
#ifndef QT_NO_TOOLTIP
        aviNoSaveCheckBox->setToolTip(QApplication::translate("newsGroupBox", "Plik nie b\304\231dzie zapisany w bazie dancyh. Natomiast mo\305\274esz z niego zrobi\304\207 stopklatki i zapisa\304\207 do galerii.", 0));
#endif // QT_NO_TOOLTIP
        aviNoSaveCheckBox->setText(QApplication::translate("newsGroupBox", "nie zapisuj pliku w bazie", 0));
#ifndef QT_NO_TOOLTIP
        convertButton->setToolTip(QApplication::translate("newsGroupBox", "Nie musisz przygotowywa\304\207 plik\303\263w video na stron\304\231 na swoim komputerze. Je\305\233li tego nie zrobisz serwer sam je przygotuje, ale nie nast\304\205pi to natychmiast.", 0));
#endif // QT_NO_TOOLTIP
        convertButton->setText(QApplication::translate("newsGroupBox", "Przygotuj pliki video", 0));
        wideCheckBox->setText(QApplication::translate("newsGroupBox", "16:9", 0));
        MP4label->setText(QApplication::translate("newsGroupBox", "MP4", 0));
        OGVlabel->setText(QApplication::translate("newsGroupBox", "OGV", 0));
        WEBMlabel->setText(QApplication::translate("newsGroupBox", "WEBM", 0));
        playerGroup->setTitle(QApplication::translate("newsGroupBox", "Player", 0));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("newsGroupBox", "Play", 0));
#endif // QT_NO_TOOLTIP
        startButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pauseButton->setToolTip(QApplication::translate("newsGroupBox", "Pause", 0));
#endif // QT_NO_TOOLTIP
        pauseButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        totalTimeMin->setToolTip(QApplication::translate("newsGroupBox", "Czas ca\305\202kowity [min]", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("newsGroupBox", ":", 0));
#ifndef QT_NO_TOOLTIP
        totalTimeSec->setToolTip(QApplication::translate("newsGroupBox", "Czas ca\305\202kowity [sec]", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        stopklatkaButton->setToolTip(QApplication::translate("newsGroupBox", "Zapisz stopklatk\304\231", 0));
#endif // QT_NO_TOOLTIP
        stopklatkaButton->setText(QString());
        fotkiGroupBox->setTitle(QApplication::translate("newsGroupBox", "Fotki:", 0));
#ifndef QT_NO_TOOLTIP
        fotkiDelSel->setToolTip(QApplication::translate("newsGroupBox", "Kasowanie zaznaczonych fotek.", 0));
#endif // QT_NO_TOOLTIP
        fotkiDelSel->setText(QApplication::translate("newsGroupBox", "Skasuj", 0));
#ifndef QT_NO_TOOLTIP
        fotkiDelAll->setToolTip(QApplication::translate("newsGroupBox", "Kasuje wszystkie fotki.", 0));
#endif // QT_NO_TOOLTIP
        fotkiDelAll->setText(QApplication::translate("newsGroupBox", "Wyczy\305\233\304\207", 0));
#ifndef QT_NO_TOOLTIP
        zdyskuButton->setToolTip(QApplication::translate("newsGroupBox", "Dodaj fotk\304\231 z pliku JPG na dysku.", 0));
#endif // QT_NO_TOOLTIP
        zdyskuButton->setText(QApplication::translate("newsGroupBox", "Z dysku", 0));
    } // retranslateUi

};

namespace Ui {
    class newsGroupBox: public Ui_newsGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSGROUPBOX_H
