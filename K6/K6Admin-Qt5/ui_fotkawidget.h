/********************************************************************************
** Form generated from reading UI file 'fotkawidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOTKAWIDGET_H
#define UI_FOTKAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FotkaWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *fotkaView;
    QVBoxLayout *verticalLayout;
    QLabel *fileNameLabel;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *selectCheckBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *up;
    QPushButton *down;
    QPushButton *first;
    QPushButton *last;

    void setupUi(QWidget *FotkaWidget)
    {
        if (FotkaWidget->objectName().isEmpty())
            FotkaWidget->setObjectName(QStringLiteral("FotkaWidget"));
        FotkaWidget->resize(301, 75);
        FotkaWidget->setMinimumSize(QSize(0, 75));
        FotkaWidget->setMaximumSize(QSize(16777215, 75));
        horizontalLayout = new QHBoxLayout(FotkaWidget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fotkaView = new QLabel(FotkaWidget);
        fotkaView->setObjectName(QStringLiteral("fotkaView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fotkaView->sizePolicy().hasHeightForWidth());
        fotkaView->setSizePolicy(sizePolicy);
        fotkaView->setMinimumSize(QSize(90, 72));
        fotkaView->setMaximumSize(QSize(90, 72));
        fotkaView->setBaseSize(QSize(90, 72));

        horizontalLayout->addWidget(fotkaView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        fileNameLabel = new QLabel(FotkaWidget);
        fileNameLabel->setObjectName(QStringLiteral("fileNameLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fileNameLabel->sizePolicy().hasHeightForWidth());
        fileNameLabel->setSizePolicy(sizePolicy1);
        fileNameLabel->setTextFormat(Qt::PlainText);

        verticalLayout->addWidget(fileNameLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        selectCheckBox = new QCheckBox(FotkaWidget);
        selectCheckBox->setObjectName(QStringLiteral("selectCheckBox"));
        sizePolicy.setHeightForWidth(selectCheckBox->sizePolicy().hasHeightForWidth());
        selectCheckBox->setSizePolicy(sizePolicy);
        selectCheckBox->setMinimumSize(QSize(14, 0));
        selectCheckBox->setMaximumSize(QSize(14, 30));
        selectCheckBox->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(selectCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        up = new QPushButton(FotkaWidget);
        up->setObjectName(QStringLiteral("up"));
        up->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/arrow-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        up->setIcon(icon);
        up->setFlat(true);

        horizontalLayout_2->addWidget(up);

        down = new QPushButton(FotkaWidget);
        down->setObjectName(QStringLiteral("down"));
        down->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/arrow-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        down->setIcon(icon1);
        down->setFlat(true);

        horizontalLayout_2->addWidget(down);

        first = new QPushButton(FotkaWidget);
        first->setObjectName(QStringLiteral("first"));
        first->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/arrow-up-double.png"), QSize(), QIcon::Normal, QIcon::Off);
        first->setIcon(icon2);
        first->setFlat(true);

        horizontalLayout_2->addWidget(first);

        last = new QPushButton(FotkaWidget);
        last->setObjectName(QStringLiteral("last"));
        last->setMaximumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/arrow-down-double.png"), QSize(), QIcon::Normal, QIcon::Off);
        last->setIcon(icon3);
        last->setFlat(true);

        horizontalLayout_2->addWidget(last);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(FotkaWidget);

        QMetaObject::connectSlotsByName(FotkaWidget);
    } // setupUi

    void retranslateUi(QWidget *FotkaWidget)
    {
        FotkaWidget->setWindowTitle(QApplication::translate("FotkaWidget", "Form", 0));
        fotkaView->setText(QString());
        fileNameLabel->setText(QApplication::translate("FotkaWidget", "filename", 0));
#ifndef QT_NO_TOOLTIP
        selectCheckBox->setToolTip(QApplication::translate("FotkaWidget", "wybierz", 0));
#endif // QT_NO_TOOLTIP
        selectCheckBox->setText(QString());
#ifndef QT_NO_TOOLTIP
        up->setToolTip(QApplication::translate("FotkaWidget", "wy\305\274ej", 0));
#endif // QT_NO_TOOLTIP
        up->setText(QString());
#ifndef QT_NO_TOOLTIP
        down->setToolTip(QApplication::translate("FotkaWidget", "ni\305\274ej", 0));
#endif // QT_NO_TOOLTIP
        down->setText(QString());
#ifndef QT_NO_TOOLTIP
        first->setToolTip(QApplication::translate("FotkaWidget", "na sam\304\205 g\303\263r\304\231", 0));
#endif // QT_NO_TOOLTIP
        first->setText(QString());
#ifndef QT_NO_TOOLTIP
        last->setToolTip(QApplication::translate("FotkaWidget", "na sam d\303\263\305\202", 0));
#endif // QT_NO_TOOLTIP
        last->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FotkaWidget: public Ui_FotkaWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOTKAWIDGET_H
