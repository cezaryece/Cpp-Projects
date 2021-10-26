#ifndef PROGRAMGROUPBOX_H
#define PROGRAMGROUPBOX_H

#include "ui_programgroupbox.h"
#include "mainwindow.h"
#include "gbbase.h"

class ProgramGroupBox : public GbBase, private Ui::programGroupBox
{
	Q_OBJECT
	
public:
	explicit ProgramGroupBox(MainWindow *parent, Prog program = Prog());
	~ProgramGroupBox() { mw->mp4PBar = mw->ogvPBar = mw->webmPBar =0; mw->aviTime = 0; 	if (m_charTable != 0) delete m_charTable; }
	virtual bool save();
	virtual bool walidacja();
	virtual bool isNews() { return false; }
private:
	Prog currProg;
	QString stopKlatkaName;
	int totalTime;
	void setVideo(QString fileName);
	CharTable * m_charTable;
private slots:
	void on_openAviButton_clicked();
	void on_convertButton_clicked();
	void on_stopklatkaButton_clicked();
	void on_pauseButton_clicked();
	void on_startButton_clicked();
	void totalTimeChanged();
	void on_tytulLineEdit_textChanged(const QString &arg1);
	void ftpFinished(int res);
	void restartVideo();
	void on_charTableButton_clicked();
	void closeCharTable();
	void menuChange();
	void on_wideCheckBox_toggled(bool checked);
	void on_aviNoSaveCheckBox_toggled(bool checked);
};

#endif // PROGRAMGROUPBOX_H
