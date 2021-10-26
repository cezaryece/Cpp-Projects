#ifndef LISTFORM_H
#define LISTFORM_H

#include "ui_listform.h"
#include "mainwindow.h"

class ListForm : public QWidget, private Ui::ListForm
{
	Q_OBJECT
	
public:
	explicit ListForm(MainWindow* const parent, focused f);
	void updateNewsList(bool reinit=false);
	void updateProgList(bool reinit=false);
protected:
	MainWindow * const mw;
	void changeEvent(QEvent *e);
	QList<News> getNewsFromDB();
	QList<Prog> getProgFromDB();
	void createContextMenus();
	int getSelectedItemID(bool news = true);
	QString getSelectedItemTITLE(bool news = true);
	void selectItemID(int itemID, bool news = true);
private slots:
	void newsDodajFilm();
	void newsKolejkujFilm();
	void newsEdytuj();
	void progEdytuj();
	void progZmienZablokowany(bool zablokuj);
	void showNewsPreview();
	void showProgPreview();
	void displayNewsContextMenu(const QPoint &pos);
	void displayProgContextMenu(const QPoint &pos);
	void on_progList_itemSelectionChanged();
	void on_newsList_itemSelectionChanged();
signals:
	void editNews(int);
	void dodajFilm4News(int);
	void editProg(int);
};

#endif // LISTFORM_H
