/********************************************************************************
** Form generated from reading UI file 'pdfimpose.ui'
**
** Created: Wed Feb 17 12:22:47 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFIMPOSE_H
#define UI_PDFIMPOSE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PDFimpose
{
public:
    QAction *actionOpen_PDF;
    QAction *actionExport_PDF;
    QAction *actionQUIT;
    QAction *actionAbout;
    QAction *actionPDF_Info;
    QWidget *centralWidget;
    QSpinBox *H;
    QSpinBox *V;
    QLabel *label;
    QLabel *label_2;
    QComboBox *PageSize;
    QLabel *label_3;
    QLineEdit *PageWidth;
    QLabel *label_4;
    QLineEdit *PageHeight;
    QComboBox *Units;
    QComboBox *Presets;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *menuPDFimposer;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PDFimpose)
    {
        if (PDFimpose->objectName().isEmpty())
            PDFimpose->setObjectName(QString::fromUtf8("PDFimpose"));
        PDFimpose->resize(609, 487);
        actionOpen_PDF = new QAction(PDFimpose);
        actionOpen_PDF->setObjectName(QString::fromUtf8("actionOpen_PDF"));
        actionExport_PDF = new QAction(PDFimpose);
        actionExport_PDF->setObjectName(QString::fromUtf8("actionExport_PDF"));
        actionQUIT = new QAction(PDFimpose);
        actionQUIT->setObjectName(QString::fromUtf8("actionQUIT"));
        actionAbout = new QAction(PDFimpose);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionPDF_Info = new QAction(PDFimpose);
        actionPDF_Info->setObjectName(QString::fromUtf8("actionPDF_Info"));
        centralWidget = new QWidget(PDFimpose);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        H = new QSpinBox(centralWidget);
        H->setObjectName(QString::fromUtf8("H"));
        H->setGeometry(QRect(30, 0, 41, 24));
        V = new QSpinBox(centralWidget);
        V->setObjectName(QString::fromUtf8("V"));
        V->setGeometry(QRect(90, 0, 41, 24));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 2, 31, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 2, 15, 21));
        PageSize = new QComboBox(centralWidget);
        PageSize->setObjectName(QString::fromUtf8("PageSize"));
        PageSize->setGeometry(QRect(180, 0, 70, 24));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 2, 41, 21));
        PageWidth = new QLineEdit(centralWidget);
        PageWidth->setObjectName(QString::fromUtf8("PageWidth"));
        PageWidth->setGeometry(QRect(260, 1, 60, 24));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, 2, 16, 21));
        PageHeight = new QLineEdit(centralWidget);
        PageHeight->setObjectName(QString::fromUtf8("PageHeight"));
        PageHeight->setGeometry(QRect(326, 2, 60, 24));
        Units = new QComboBox(centralWidget);
        Units->setObjectName(QString::fromUtf8("Units"));
        Units->setGeometry(QRect(385, 2, 70, 24));
        Presets = new QComboBox(centralWidget);
        Presets->setObjectName(QString::fromUtf8("Presets"));
        Presets->setGeometry(QRect(460, 2, 131, 24));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 30, 88, 22));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(100, 30, 88, 22));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(4, 54, 601, 365));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 595, 359));
        scrollArea->setWidget(scrollAreaWidgetContents);
        PDFimpose->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PDFimpose);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 609, 19));
        menuPDFimposer = new QMenu(menuBar);
        menuPDFimposer->setObjectName(QString::fromUtf8("menuPDFimposer"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        PDFimpose->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PDFimpose);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setAutoFillBackground(true);
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        PDFimpose->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PDFimpose);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PDFimpose->setStatusBar(statusBar);
        QWidget::setTabOrder(PageWidth, H);
        QWidget::setTabOrder(H, PageSize);
        QWidget::setTabOrder(PageSize, Units);
        QWidget::setTabOrder(Units, V);
        QWidget::setTabOrder(V, Presets);
        QWidget::setTabOrder(Presets, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton_5);
        QWidget::setTabOrder(pushButton_5, scrollArea);
        QWidget::setTabOrder(scrollArea, PageHeight);

        menuBar->addAction(menuPDFimposer->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuPDFimposer->addAction(actionOpen_PDF);
        menuPDFimposer->addAction(actionPDF_Info);
        menuPDFimposer->addAction(actionExport_PDF);
        menuPDFimposer->addSeparator();
        menuPDFimposer->addAction(actionQUIT);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionOpen_PDF);
        mainToolBar->addAction(actionPDF_Info);
        mainToolBar->addAction(actionExport_PDF);

        retranslateUi(PDFimpose);

        QMetaObject::connectSlotsByName(PDFimpose);
    } // setupUi

    void retranslateUi(QMainWindow *PDFimpose)
    {
        PDFimpose->setWindowTitle(QApplication::translate("PDFimpose", "PDFimpose", 0, QApplication::UnicodeUTF8));
        actionOpen_PDF->setText(QApplication::translate("PDFimpose", "Open PDF...", 0, QApplication::UnicodeUTF8));
        actionExport_PDF->setText(QApplication::translate("PDFimpose", "Export PDF", 0, QApplication::UnicodeUTF8));
        actionQUIT->setText(QApplication::translate("PDFimpose", "Quit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionQUIT->setToolTip(QApplication::translate("PDFimpose", "Quit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAbout->setText(QApplication::translate("PDFimpose", "About", 0, QApplication::UnicodeUTF8));
        actionPDF_Info->setText(QApplication::translate("PDFimpose", "PDF Info", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PDFimpose", "H", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PDFimpose", "V", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PDFimpose", "Page", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PDFimpose", "x", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        Presets->setToolTip(QApplication::translate("PDFimpose", "Presets", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_2->setText(QApplication::translate("PDFimpose", "Rotate All", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("PDFimpose", "Clone All", 0, QApplication::UnicodeUTF8));
        menuPDFimposer->setTitle(QApplication::translate("PDFimpose", "PDFimposer", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("PDFimpose", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PDFimpose: public Ui_PDFimpose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFIMPOSE_H
