#ifndef SEARCHGROUPBOX_H
#define SEARCHGROUPBOX_H

#include <QGroupBox>
#include "ui_searchgroupbox.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql//QSqlError>
#include "mainwindow.h"

typedef enum {
	anyWord,
	allWords,
	exactSentence
} searchwords;


class SearchGroupBox : public QGroupBox, private Ui::SearchGroupBox
{
	Q_OBJECT
	
public:
	explicit SearchGroupBox(MainWindow *parent);
	~SearchGroupBox();
protected:
	MainWindow * mw;
private slots:
	void on_anyRadio_toggled(bool checked);
	void on_allRadio_toggled(bool checked);
	void on_exactRadio_toggled(bool checked);
	void on_allfilesRadio_toggled(bool checked);
	void on_videoCheckBox_clicked(bool checked);
	void on_audioCheckBox_clicked(bool checked);
	void on_textCheckBox_clicked(bool checked);
	void on_fotoCheckBox_clicked(bool checked);
	void on_dirCheckBox_clicked(bool checked);
	void on_SzukajButton_clicked();
	void on_customCheckBox_clicked(bool checked);
	
	void on_txtCheckBox_clicked(bool checked);
	
private:
	searchwords swords;
	bool searchAll;
	bool videoFiles;
	bool audioFiles;
	bool textFiles;
	bool fotoFiles;
	bool searchDirs;
	bool customFiles;
	bool searchInTxt;
	QString customExtension;
	
	QSqlDatabase fdDB;
	
	
	bool checkFilesFilter();
	QString getDirName(long long dirID);
};

#endif // SEARCHGROUPBOX_H
