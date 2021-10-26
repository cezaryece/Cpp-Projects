/********************************************************************************
** Form generated from reading UI file 'listform.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTFORM_H
#define UI_LISTFORM_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *informacjeBox;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *newsList;
    QGroupBox *programyBox;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *progList;
    QHBoxLayout *horizontalLayout_2;
    QWebView *preView;

    void setupUi(QWidget *ListForm)
    {
        if (ListForm->objectName().isEmpty())
            ListForm->setObjectName(QStringLiteral("ListForm"));
        ListForm->resize(953, 795);
        verticalLayout_2 = new QVBoxLayout(ListForm);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        informacjeBox = new QGroupBox(ListForm);
        informacjeBox->setObjectName(QStringLiteral("informacjeBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(informacjeBox->sizePolicy().hasHeightForWidth());
        informacjeBox->setSizePolicy(sizePolicy);
        informacjeBox->setMinimumSize(QSize(0, 180));
        verticalLayout_3 = new QVBoxLayout(informacjeBox);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        newsList = new QTableWidget(informacjeBox);
        newsList->setObjectName(QStringLiteral("newsList"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(newsList->sizePolicy().hasHeightForWidth());
        newsList->setSizePolicy(sizePolicy1);
        newsList->setMinimumSize(QSize(0, 9));
        newsList->setLineWidth(0);
        newsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        newsList->setTabKeyNavigation(false);
        newsList->setProperty("showDropIndicator", QVariant(false));
        newsList->setAlternatingRowColors(true);
        newsList->setSelectionMode(QAbstractItemView::SingleSelection);
        newsList->setSelectionBehavior(QAbstractItemView::SelectRows);
        newsList->setShowGrid(false);
        newsList->setGridStyle(Qt::NoPen);
        newsList->setSortingEnabled(true);
        newsList->setCornerButtonEnabled(false);

        verticalLayout_3->addWidget(newsList);


        horizontalLayout->addWidget(informacjeBox);

        programyBox = new QGroupBox(ListForm);
        programyBox->setObjectName(QStringLiteral("programyBox"));
        sizePolicy.setHeightForWidth(programyBox->sizePolicy().hasHeightForWidth());
        programyBox->setSizePolicy(sizePolicy);
        programyBox->setMinimumSize(QSize(0, 100));
        verticalLayout_4 = new QVBoxLayout(programyBox);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        progList = new QTableWidget(programyBox);
        progList->setObjectName(QStringLiteral("progList"));
        sizePolicy1.setHeightForWidth(progList->sizePolicy().hasHeightForWidth());
        progList->setSizePolicy(sizePolicy1);
        progList->setLineWidth(0);
        progList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        progList->setTabKeyNavigation(false);
        progList->setProperty("showDropIndicator", QVariant(false));
        progList->setAlternatingRowColors(true);
        progList->setSelectionMode(QAbstractItemView::SingleSelection);
        progList->setSelectionBehavior(QAbstractItemView::SelectRows);
        progList->setShowGrid(false);
        progList->setGridStyle(Qt::NoPen);
        progList->setSortingEnabled(true);
        progList->setCornerButtonEnabled(false);

        verticalLayout_4->addWidget(progList);


        horizontalLayout->addWidget(programyBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        preView = new QWebView(ListForm);
        preView->setObjectName(QStringLiteral("preView"));
        sizePolicy.setHeightForWidth(preView->sizePolicy().hasHeightForWidth());
        preView->setSizePolicy(sizePolicy);
        preView->setMinimumSize(QSize(505, 0));
        preView->setMaximumSize(QSize(505, 600));
        preView->setUrl(QUrl(QStringLiteral("about:blank")));

        horizontalLayout_2->addWidget(preView);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ListForm);

        QMetaObject::connectSlotsByName(ListForm);
    } // setupUi

    void retranslateUi(QWidget *ListForm)
    {
        ListForm->setWindowTitle(QApplication::translate("ListForm", "Form", 0));
        informacjeBox->setTitle(QApplication::translate("ListForm", "Informacje", 0));
        programyBox->setTitle(QApplication::translate("ListForm", "Programy", 0));
    } // retranslateUi

};

namespace Ui {
    class ListForm: public Ui_ListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTFORM_H
