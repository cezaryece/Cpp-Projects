#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include "ui_videoform.h"
#include "gbbase.h"
#include "fotkawidget.h"
#include "mainwindow.h"

class VideoForm : public GbBase, private Ui::VideoForm
{
	Q_OBJECT
	
public:
	explicit VideoForm(MainWindow *parent);
	~VideoForm()  { mw->mp4PBar = mw->ogvPBar = mw->webmPBar =0; mw->aviTime = 0; }
	virtual bool save();
	virtual bool walidacja();
	virtual bool isNews() { return true; }
	QList<FotkaWidget*> fotkaWidgetsList;
	void setNewsId(int id);
protected:
	int newsID;
	int stopklatkaNr;
	void stopKlatkiAppend(QString fname);
private slots:
	void on_openAviButton_clicked();
	void on_convertButton_clicked();
	void on_startButton_clicked();
	void on_pauseButton_clicked();
	void on_stopklatkaButton_clicked();
	void totalTimeChanged();
	void on_fotkiDelSel_clicked();
	void on_fotkiDelAll_clicked();
	void moveFoto(int);
	void ftpFinished(int);
	void restartVideo();
	void on_wideCheckBox_clicked(bool checked);
};

#endif // VIDEOFORM_H
