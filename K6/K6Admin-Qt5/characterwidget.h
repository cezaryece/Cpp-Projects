#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QFont>
#include <QWidget>
#include <QMouseEvent>

class CharacterWidget : public QWidget
{
	Q_OBJECT
	
public:
	CharacterWidget(QWidget *parent = 0);
	QSize sizeHint() const;
	
public slots:
	
signals:
	void characterSelected(const QString &character);
	
protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	
private:
	QFont displayFont;
	int columns;
	int lastKey;
	int squareSize;
	int w,h;
	QList<QChar> charList;
};

#endif // CHARACTERWIDGET_H
