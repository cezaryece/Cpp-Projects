#ifndef PDFIMPOSE_H
#define PDFIMPOSE_H

#include <QMainWindow>
#include <QString>

#include <poppler-qt4.h>

namespace Ui {
    class PDFimpose;
}

class PDFimpose : public QMainWindow {
    Q_OBJECT
public:
    PDFimpose(QWidget *parent = 0);
    ~PDFimpose();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PDFimpose *ui;
    Poppler::Document *PDF;
    void load(QString);

private slots:
    void OpenPDF();
    void InfoPDF();
    void ExportPDF();
};

#endif // PDFIMPOSE_H
