#include "chartable.h"
#include "characterwidget.h"
#include <QHBoxLayout>
#include <QScrollArea>

CharTable::CharTable(QWidget *parent) :
	QDialog(parent)
{
	//setupUi(this);
	QScrollArea *scrollArea = new QScrollArea;
	CharacterWidget *characterWidget = new CharacterWidget;
	scrollArea->setWidget(characterWidget);
	scrollArea->resize(characterWidget->sizeHint().width(),characterWidget->sizeHint().height());

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(scrollArea,1);
	setLayout(mainLayout);
	
	connect(characterWidget, SIGNAL(characterSelected(QString)), this, SLOT(insertCharacter(QString)));
	
	setWindowTitle(QString::fromUtf8("Tablica znaków"));
	resize(scrollArea->sizeHint().width()+40, scrollArea->sizeHint().height());
	setMaximumSize(size());
	setMinimumSize(size());
	setSizeGripEnabled(false);
}

void CharTable::insertCharacter(const QString &character)
{
	emit pushText(character);
}
