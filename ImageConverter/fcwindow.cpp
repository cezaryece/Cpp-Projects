#include "fcwindow.h"
#include "ui_fcwindow.h"

#include <QtGui>
int* licznikplikow;

//funkcja zliczająca typy plików z danej listy
void licz(QStringList pliki,QStringList listatypowplikow, int* licznik)
{
    for(int i=0;i<pliki.size();i++)
    {
        int typ = listatypowplikow.indexOf("*." + pliki.at(i).right(3).toLower());
        if (typ >= 0)
        {
            licznik[typ]++;
        }
    }
}

FCWindow::FCWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::FCWindow)
{
    QString znaleziono;
    ui->setupUi(this);
    typyplikow << "*.jpg" << "*.tif" << "*.bmp" << "*.png" << "*.cpt";
    dir = QDir::currentPath();
    ui->lineEdit_dir->setText(dir);
    licznikplikow = new int[typyplikow.size()];
    for (int i=0;i<typyplikow.size();i++)
    {
        licznikplikow[i]=0;
        qDebug() << licznikplikow[i];
    }
    policzpliki(dir,typyplikow);
    for (int i=0;i<typyplikow.size();i++)
        znaleziono += " " + typyplikow.at(i) + " " + QString::number(licznikplikow[i]) + "|";
    ui->znaleziono->setText(znaleziono);
}

FCWindow::~FCWindow()
{
    delete ui;
}
void FCWindow::policzpliki(QDir directory,QStringList listatypowplikow)
{
    QStringList katalogi;
    QStringList pliki;

    katalogi = directory.entryList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for (int i=0;i<katalogi.size();i++)
    {
        directory.cd(directory.absolutePath() + "/" + katalogi.at(i));
        policzpliki(directory,listatypowplikow);
        directory.cdUp();
    }
    directory.setNameFilters(listatypowplikow);
    pliki = directory.entryList(QDir::Files | QDir::NoSymLinks);
    if (pliki.size()>0) licz(pliki,listatypowplikow,licznikplikow);
}
void FCWindow::konwertujpliki(QDir dir,QStringList filtry)
{
}

void FCWindow::on_pushButton_wybierz_clicked()
{
   QString curDir;
   QString znaleziono;

   if (ui->lineEdit_dir->text()=="") curDir=QDir::currentPath();
   else curDir = ui->lineEdit_dir->text();
   dir = QFileDialog::getExistingDirectory (this,"Wybierz katalog z obrazami",curDir,QFileDialog::ShowDirsOnly);
   if (!dir.isEmpty())
   {
        ui->lineEdit_dir->setText(dir);
        policzpliki(dir,typyplikow);
        for (int i=0;i<typyplikow.size();i++)
        {
           znaleziono += " " + typyplikow.at(i) + " " + QString::number(licznikplikow[i]) + "|";
           licznikplikow[i]=0;
        }
        ui->znaleziono->setText(znaleziono);
    }
}

void FCWindow::on_checkBox_resize_stateChanged(int )
{
    if (ui->checkBox_resize->isChecked())
        ui->lineEdit_size->setDisabled(true);
    else
        ui->lineEdit_size->setEnabled(true);
}

void FCWindow::on_pushButton_OK_clicked()
{
}
void FCWindow::on_pushButton_Cancel_clicked()
{
}
