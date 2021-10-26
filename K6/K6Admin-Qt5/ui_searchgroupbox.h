/********************************************************************************
** Form generated from reading UI file 'searchgroupbox.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHGROUPBOX_H
#define UI_SEARCHGROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchGroupBox
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *anyRadio;
    QRadioButton *allRadio;
    QRadioButton *exactRadio;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *szukajLineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QRadioButton *allfilesRadio;
    QCheckBox *videoCheckBox;
    QCheckBox *audioCheckBox;
    QCheckBox *textCheckBox;
    QCheckBox *fotoCheckBox;
    QCheckBox *dirCheckBox;
    QCheckBox *customCheckBox;
    QLineEdit *extLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *txtCheckBox;
    QPushButton *SzukajButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget;
    QButtonGroup *buttonGroup;

    void setupUi(QGroupBox *SearchGroupBox)
    {
        if (SearchGroupBox->objectName().isEmpty())
            SearchGroupBox->setObjectName(QStringLiteral("SearchGroupBox"));
        SearchGroupBox->resize(579, 746);
        SearchGroupBox->setFlat(true);
        verticalLayout = new QVBoxLayout(SearchGroupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(SearchGroupBox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        anyRadio = new QRadioButton(groupBox);
        buttonGroup = new QButtonGroup(SearchGroupBox);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(anyRadio);
        anyRadio->setObjectName(QStringLiteral("anyRadio"));
        anyRadio->setChecked(true);

        horizontalLayout_3->addWidget(anyRadio);

        allRadio = new QRadioButton(groupBox);
        buttonGroup->addButton(allRadio);
        allRadio->setObjectName(QStringLiteral("allRadio"));

        horizontalLayout_3->addWidget(allRadio);

        exactRadio = new QRadioButton(groupBox);
        buttonGroup->addButton(exactRadio);
        exactRadio->setObjectName(QStringLiteral("exactRadio"));

        horizontalLayout_3->addWidget(exactRadio);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        szukajLineEdit = new QLineEdit(groupBox);
        szukajLineEdit->setObjectName(QStringLiteral("szukajLineEdit"));

        horizontalLayout_4->addWidget(szukajLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        allfilesRadio = new QRadioButton(groupBox);
        allfilesRadio->setObjectName(QStringLiteral("allfilesRadio"));
        allfilesRadio->setChecked(true);

        horizontalLayout->addWidget(allfilesRadio);

        videoCheckBox = new QCheckBox(groupBox);
        videoCheckBox->setObjectName(QStringLiteral("videoCheckBox"));

        horizontalLayout->addWidget(videoCheckBox);

        audioCheckBox = new QCheckBox(groupBox);
        audioCheckBox->setObjectName(QStringLiteral("audioCheckBox"));

        horizontalLayout->addWidget(audioCheckBox);

        textCheckBox = new QCheckBox(groupBox);
        textCheckBox->setObjectName(QStringLiteral("textCheckBox"));

        horizontalLayout->addWidget(textCheckBox);

        fotoCheckBox = new QCheckBox(groupBox);
        fotoCheckBox->setObjectName(QStringLiteral("fotoCheckBox"));

        horizontalLayout->addWidget(fotoCheckBox);

        dirCheckBox = new QCheckBox(groupBox);
        dirCheckBox->setObjectName(QStringLiteral("dirCheckBox"));

        horizontalLayout->addWidget(dirCheckBox);

        customCheckBox = new QCheckBox(groupBox);
        customCheckBox->setObjectName(QStringLiteral("customCheckBox"));

        horizontalLayout->addWidget(customCheckBox);

        extLineEdit = new QLineEdit(groupBox);
        extLineEdit->setObjectName(QStringLiteral("extLineEdit"));

        horizontalLayout->addWidget(extLineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        txtCheckBox = new QCheckBox(groupBox);
        txtCheckBox->setObjectName(QStringLiteral("txtCheckBox"));

        horizontalLayout_2->addWidget(txtCheckBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        SzukajButton = new QPushButton(groupBox);
        SzukajButton->setObjectName(QStringLiteral("SzukajButton"));

        verticalLayout_2->addWidget(SzukajButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SearchGroupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        listWidget = new QListWidget(groupBox_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_3->addWidget(listWidget);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(SearchGroupBox);

        QMetaObject::connectSlotsByName(SearchGroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *SearchGroupBox)
    {
        SearchGroupBox->setWindowTitle(QApplication::translate("SearchGroupBox", "Szukanie plik\303\263w", 0));
        SearchGroupBox->setTitle(QString());
        groupBox->setTitle(QApplication::translate("SearchGroupBox", "Zapytanie", 0));
        anyRadio->setText(QApplication::translate("SearchGroupBox", "kt\303\263rekolwiek", 0));
        allRadio->setText(QApplication::translate("SearchGroupBox", "wszystkie", 0));
        exactRadio->setText(QApplication::translate("SearchGroupBox", "dok\305\202adna fraza", 0));
        label->setText(QApplication::translate("SearchGroupBox", "szukaj:", 0));
        label_2->setText(QApplication::translate("SearchGroupBox", "pliki:", 0));
        allfilesRadio->setText(QApplication::translate("SearchGroupBox", "wszystkie", 0));
        videoCheckBox->setText(QApplication::translate("SearchGroupBox", "video", 0));
        audioCheckBox->setText(QApplication::translate("SearchGroupBox", "audio", 0));
        textCheckBox->setText(QApplication::translate("SearchGroupBox", "text", 0));
        fotoCheckBox->setText(QApplication::translate("SearchGroupBox", "foto", 0));
        dirCheckBox->setText(QApplication::translate("SearchGroupBox", "katalogi", 0));
        customCheckBox->setText(QApplication::translate("SearchGroupBox", "typu:", 0));
        txtCheckBox->setText(QApplication::translate("SearchGroupBox", "Szukaj w tekstach i tytu\305\202ach news\303\263w i program\303\263w", 0));
#ifndef QT_NO_TOOLTIP
        SzukajButton->setToolTip(QApplication::translate("SearchGroupBox", "Esc przerywa szukanie", 0));
#endif // QT_NO_TOOLTIP
        SzukajButton->setText(QApplication::translate("SearchGroupBox", "Szukaj", 0));
        groupBox_2->setTitle(QApplication::translate("SearchGroupBox", "Wyniki", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchGroupBox: public Ui_SearchGroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHGROUPBOX_H
