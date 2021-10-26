#ifndef GBBASE_H
#define GBBASE_H

#include <QGroupBox>
class MainWindow;
class QTextBrowser;
class QPushButton;
class QLabel;


class GbBase : public QGroupBox
{
	Q_OBJECT
public:
	explicit GbBase(MainWindow *parent);
	virtual bool save() { return false; }
	virtual bool walidacja() { return false; }
	virtual bool isNews() { return false; }
	virtual void ftpFinished(int) {}
protected:
	MainWindow * mw;
public:
	QTextBrowser * con;
	QPushButton *openAVI, * convertAVI;
	QLabel *mp4L, *ogvL, *webmL;
	bool converting;
signals:
	void finished();
};

#endif // GBBASE_H
