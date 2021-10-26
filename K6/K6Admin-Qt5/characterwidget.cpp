#include "characterwidget.h"
#include <QChar>
#include <QFontDatabase>
#include <QToolTip>
#include <QPainter>
#include <QDebug>

CharacterWidget::CharacterWidget(QWidget *parent)
	: QWidget(parent)
{
	squareSize = 36;
	columns = 10;
	lastKey = -1;
	setMouseTracking(true);
	
	QFontDatabase fontsDB;
	QFont font = fontsDB.font("Trebuchet MS","",16);
	
	displayFont.setFamily(font.family());
	displayFont.setStyleStrategy(QFont::QFont::PreferDefault);
	displayFont.setPointSize(16);
	squareSize = qMax(20, QFontMetrics(displayFont).xHeight() * 3);
	for (uint charcode=0x0020; charcode < 0x007F; ++charcode)
		charList.append(QChar(charcode));
	for (uint charcode=0x2018; charcode <= 0x2027; ++charcode)
		charList.append(QChar(charcode));
	charList.append(QChar(0x2030));
	charList.append(QChar(0x2031));
	for (uint charcode=0x0082; charcode <= 0x024F; ++charcode)
		charList.append(QChar(charcode));
	w = columns*squareSize;
	h = (charList.count() / columns +1)*squareSize;
	resize(sizeHint());
	update();
}

QSize CharacterWidget::sizeHint() const
{
	return QSize(w,h);
}

void CharacterWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint widgetPosition = mapFromGlobal(event->globalPos());
	uint key = (widgetPosition.y()/squareSize)*columns + widgetPosition.x()/squareSize;
	if (key >= (uint) charList.count())
		return;
	
	QString text = QString::fromLatin1("<p>Character: <span style=\"font-size: 24pt; font-family: %1\">").arg(displayFont.family())
			+ charList.at(key)
			+ QString::fromLatin1("</span><p>Value: 0x")
			+ QString::number(charList.at(key).unicode(), 16);
	QToolTip::showText(event->globalPos(), text, this);
}

void CharacterWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		lastKey = (event->y()/squareSize)*columns + event->x()/squareSize;
		if (charList.at(lastKey).category() != QChar::Other_NotAssigned)
			emit characterSelected(QString(charList.at(lastKey)));
		update();
	}
	else
		QWidget::mouseDoubleClickEvent(event);
}
void CharacterWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		lastKey = (event->y()/squareSize)*columns + event->x()/squareSize;
		update();
	}
	else
		QWidget::mousePressEvent(event);
}
void CharacterWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), QBrush(Qt::white));
	painter.setFont(displayFont);
	
	QRect redrawRect = event->rect();
	int beginRow = redrawRect.top()/squareSize;
	int endRow = redrawRect.bottom()/squareSize + 1;
	int beginColumn = 0;
	int endColumn = columns;
	
	painter.setPen(QPen(Qt::gray));
	for (int row = beginRow; row <= endRow; ++row) {
		for (int column = beginColumn; column < endColumn; ++column) {
			painter.drawRect(column*squareSize, row*squareSize, squareSize, squareSize);
		}
	}
	
	QFontMetrics fontMetrics(displayFont);
	painter.setPen(QPen(Qt::black));
	for (int row = beginRow; row <= endRow; ++row) {
		
		for (int column = beginColumn; column < endColumn; ++column) {
			
			int key = row*columns + column;
			if (key >= charList.count())
				return;
			QChar currChar = charList.at(key);
			painter.setClipRect(column*squareSize, row*squareSize, squareSize, squareSize);
			
			if (key == lastKey)
				painter.fillRect(column*squareSize + 1, row*squareSize + 1, squareSize, squareSize, QBrush(Qt::red));
			
			painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(currChar)/2,
							 row*squareSize + 4 + fontMetrics.ascent(),
							 QString(currChar));
		}
	}
}
