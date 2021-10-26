/********************************************************************************
** Form generated from reading UI file 'chartable.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTABLE_H
#define UI_CHARTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CharTable
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *CharTable)
    {
        if (CharTable->objectName().isEmpty())
            CharTable->setObjectName(QStringLiteral("CharTable"));
        CharTable->resize(300, 200);
        verticalLayout = new QVBoxLayout(CharTable);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        retranslateUi(CharTable);

        QMetaObject::connectSlotsByName(CharTable);
    } // setupUi

    void retranslateUi(QDialog *CharTable)
    {
        CharTable->setWindowTitle(QApplication::translate("CharTable", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class CharTable: public Ui_CharTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTABLE_H
