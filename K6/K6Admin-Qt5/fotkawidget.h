#ifndef FOTKAWIDGET_H
#define FOTKAWIDGET_H

#include "ui_fotkawidget.h"

class FotkaWidget : public QWidget, private Ui::FotkaWidget
{
	Q_OBJECT
	
public:
	explicit FotkaWidget(QString fn, QWidget *parent = 0);
	QString fotkaName;
	bool isSel() { return selectCheckBox->isChecked(); }
signals:
	void fotkaMove(int);
private slots:
	void fotkaUp() { emit fotkaMove(1); }
	void fotkaDown() { emit fotkaMove(2); }
	void fotkaFirst() { emit fotkaMove(0); }
	void fotkaLast() { emit fotkaMove(9); }
};

#endif // FOTKAWIDGET_H
