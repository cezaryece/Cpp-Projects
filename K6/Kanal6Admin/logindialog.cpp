#include "logindialog.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>
#include <QCryptographicHash>

LoginDialog::LoginDialog(MainWindow * parent) :
	QDialog((QWidget*) parent), mw(parent)
{
	setupUi(this);
}

void LoginDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
		break;
		default:
		break;
	}
}

void LoginDialog::on_loginButton_clicked()
{
	QSqlQuery myQuery;
	QString sql("SELECT id, prawa FROM users WHERE login=? AND password=? LIMIT 1");
	myQuery.prepare(sql);
	myQuery.addBindValue(loginLE->text());
	QString pass = QCryptographicHash::hash(QByteArray(passLE->text().toStdString().c_str()),QCryptographicHash::Md5).toHex();
	myQuery.addBindValue(pass);
	if (myQuery.exec())
	{
		if (myQuery.first())
		{
			int id = myQuery.value(0).toInt();
			if (id > 0)
			{
				uint prawa = myQuery.value(1).toUInt();
				if (mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "_k6_news_all" << "_k6_news_user" << "_k6prog_edit" << "k6_flv", prawa))
				{
					mw->loginID = id;
					mw->prawaID = prawa;
					accept();
				}
				else
					QMessageBox::critical(this,QString::fromUtf8("Błąd uprawnień!!!"),QString::fromUtf8("Nie masz uprawnień do edycji"), QMessageBox::Retry);
			}
		}
		else
			QMessageBox::critical(this,QString::fromUtf8("Błąd logowania!!!"),QString::fromUtf8("Nieprawidłowy login lub hasło"), QMessageBox::Retry);
	}
	else
	{
        queryError(myQuery,this);
		exit(1);
	}
}
