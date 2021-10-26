#include "fotkawidget.h"
#include <QPixmap>
#include <QFileInfo>

FotkaWidget::FotkaWidget(QString fn, QWidget *parent) :
	QWidget(parent), fotkaName(fn)
{
	setupUi(this);
	QFileInfo fi(fotkaName);
	QString fName = fi.baseName();
	fileNameLabel->setText(fName);
    QPixmap pix = QPixmap(fotkaName,"JPG");
    fotkaView->setPixmap(pix.scaledToWidth(90));
	connect(up,SIGNAL(clicked()),this, SLOT(fotkaUp()));
	connect(down,SIGNAL(clicked()),this, SLOT(fotkaDown()));
	connect(first,SIGNAL(clicked()),this, SLOT(fotkaFirst()));
	connect(last,SIGNAL(clicked()),this, SLOT(fotkaLast()));
}
