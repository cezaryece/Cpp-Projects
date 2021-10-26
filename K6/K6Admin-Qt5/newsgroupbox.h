#ifndef NEWSGROUPBOX_H
#define NEWSGROUPBOX_H

#include "gbbase.h"
#include "ui_newsgroupbox.h"
#include "mainwindow.h"
#include "fotkawidget.h"
#include "chartable.h"

typedef enum {
	aLeft, aCenter, aRight, aJustified
} Align;

class NewsGroupBox : public GbBase, private Ui::newsGroupBox
{
	Q_OBJECT
	
public:
	explicit NewsGroupBox(MainWindow *parent, News news = News());
	~NewsGroupBox();
	virtual bool save();
	virtual bool walidacja();
	virtual bool isNews() { return true; }
	QList<FotkaWidget*> fotkaWidgetsList;
protected:
	News currNews;
	void setupTextEdit();
	int stopklatkaNr;
	void textAlign(Align a);
	void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
	void setupTextActions();
	void colorChanged(const QColor &c);
	void alignmentChanged(Qt::Alignment a);
	void stopKlatkiAppend(QString fname);
	bool saveNews(QString sql);
	CharTable * m_charTable;
private slots:
	void on_tytulLineEdit_textChanged(const QString &arg1);
	void on_miastoComboBox_editTextChanged(const QString &arg1);
	void on_autorLineEdit_textChanged(const QString &arg1);
	void on_imprezaGroupBox_toggled(bool checked);
	void on_imprezaNazwaLineEdit_textChanged(const QString &arg1);
	void on_waznyCheckBox_clicked(bool checked);
	void on_openAviButton_clicked();
	void on_aviNoSaveCheckBox_toggled(bool checked);
	void on_convertButton_clicked();
	void on_startButton_clicked();
	void on_pauseButton_clicked();
	void on_stopklatkaButton_clicked();
	void totalTimeChanged();
	void on_fotkiDelSel_clicked();
	void on_fotkiDelAll_clicked();
	void on_zdyskuButton_clicked();
	void moveFoto(int);
	void ftpFinished(int);
	void restartVideo();
	//text editor
	void on_textEdit_textChanged();
	void textBold();
	void textUnderline();
	void textItalic();
	void textSize(const QString &p);
	void textStyle(int styleIndex);
	void textColor();
	void textAlignL();
	void textAlignR(bool);
	void textAlignC(bool);
	void textAlignJ(bool);
	void currentCharFormatChanged(const QTextCharFormat &format);
	void cursorPositionChanged();
	void fontChanged(const QFont &f);
	void on_charTableButton_clicked();
	void closeCharTable();
	void on_wideCheckBox_clicked(bool checked);
};

#endif // NEWSGROUPBOX_H
