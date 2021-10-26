#ifndef CHARTABLE_H
#define CHARTABLE_H

class CharacterWidget;
class QScrollArea;


#include "ui_chartable.h"
class CharTable : public QDialog, private Ui::CharTable
{
	Q_OBJECT
	
public:
	explicit CharTable(QWidget *parent = 0);
public slots:
	void insertCharacter(const QString &character);
signals:
	void pushText(QString);
};

#endif // CHARTABLE_H
