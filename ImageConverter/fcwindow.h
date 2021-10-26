#ifndef FCWINDOW_H
#define FCWINDOW_H

#include <QtGui>
#include <QDialog>
#include <QStringList>

namespace Ui
{
    class FCWindow;
}

class FCWindow : public QDialog
{
    Q_OBJECT

public:
    FCWindow(QWidget *parent = 0);
    ~FCWindow();

private:
    Ui::FCWindow *ui;
    QString dir;
    QStringList typyplikow;
    void policzpliki(QDir,QStringList);
    void konwertujpliki(QDir,QStringList);

private slots:
    void on_checkBox_resize_stateChanged(int );
    void on_pushButton_wybierz_clicked();
    void on_pushButton_OK_clicked();
    void on_pushButton_Cancel_clicked();
};

#endif // FCWINDOW_H
