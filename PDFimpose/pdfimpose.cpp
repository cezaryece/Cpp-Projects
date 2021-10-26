#include "pdfimpose.h"
#include "ui_pdfimpose.h"

#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QToolButton>
#include <QPushButton>
#include <QGroupBox>
#include <QPixmap>
#include <QVBoxLayout>
#include "itoa.h"


PDFimpose::PDFimpose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PDFimpose)
{
    ui->setupUi(this);
    connect(ui->actionOpen_PDF, SIGNAL(triggered()), this, SLOT(OpenPDF()));
    ui->statusBar->showMessage("Startuję", 1000);
}

PDFimpose::~PDFimpose()
{
    delete ui;
}

void PDFimpose::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PDFimpose::load(QString filename) {
    QImage image;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QToolButton *pageView;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    PDF = Poppler::Document::load(filename);
    if (PDF == NULL) {
        ui->statusBar->showMessage("Error openning PDF", 2000);
        exit(1);
    }
    char temp[4];
    ui->statusBar->showMessage("Stron: " + QString(itoa(PDF->numPages(),temp)));
    verticalLayoutWidget = new QWidget(ui->scrollAreaWidgetContents);
            verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
            verticalLayoutWidget->setGeometry(QRect(10, 10, 571, 311));
            verticalLayout = new QVBoxLayout(verticalLayoutWidget);
            verticalLayout->setSpacing(0);
            verticalLayout->setContentsMargins(2, 2, 2, 2);
            verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
            verticalLayout->setContentsMargins(0, 0, 0, 0);
    for (int pagenum=0; pagenum < PDF->numPages(); pagenum++) {
        image = PDF->page(pagenum)->renderToImage().scaledToHeight(50,Qt::FastTransformation);
        groupBox = new QGroupBox(verticalLayoutWidget);
                groupBox->setObjectName(QString::fromUtf8("groupBox"));
                pageView = new QToolButton(groupBox);
                pageView->setObjectName(QString::fromUtf8("graphicsView"));
                pageView->setGeometry(QRect(10, 20, 101, 131));
                pageView->setIcon(QPixmap::fromImage(image));
                pushButton = new QPushButton(groupBox);
                pushButton->setObjectName(QString::fromUtf8("pushButton"));
                pushButton->setGeometry(QRect(10, 150, 31, 22));
                pushButton_3 = new QPushButton(groupBox);
                pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
                pushButton_3->setGeometry(QRect(40, 150, 31, 22));
                pushButton_4 = new QPushButton(groupBox);
                pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
                pushButton_4->setGeometry(QRect(70, 150, 41, 22));
    }
    ui->scrollAreaWidgetContents->update();
}

//slots
void PDFimpose::OpenPDF() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."), QString(), tr("PDF-Files (*.pdf);;All Files (*)"),0,QFileDialog::DontUseNativeDialog);
//    QString fn("x.pdf");
    if (!fn.isEmpty())
        load(fn);
}

void PDFimpose::ExportPDF() {

}

void PDFimpose::InfoPDF() {

}

