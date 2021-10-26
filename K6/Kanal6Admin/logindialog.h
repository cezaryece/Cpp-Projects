#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "ui_logindialog.h"
#include "mainwindow.h"

class LoginDialog : public QDialog, private Ui::LoginDialog
{
	Q_OBJECT
	
public:
	explicit LoginDialog(MainWindow * parent);
	
protected:
	void changeEvent(QEvent *e);
	MainWindow * mw;
private slots:
	void on_loginButton_clicked();
};

#endif // LOGINDIALOG_H
