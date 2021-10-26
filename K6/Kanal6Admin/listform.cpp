#include "listform.h"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QWidget>
#include <QPoint>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


ListForm::ListForm(MainWindow * const parent, focused what) :
	QWidget(parent), mw(parent)
{
	setupUi(this);
	
	createContextMenus();
	
	
	newsList->setColumnCount(7);
	newsList->setColumnHidden(0,true);
	QStringList labels;
	labels << "id" << "Data" << QString::fromUtf8("Tytuł") << "Miasto" << "Film" << "Impreza" << "Akcept";
	newsList->setHorizontalHeaderLabels(labels);
	//newsList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	updateNewsList(what==none);
	
	progList->setColumnCount(5);
	progList->setColumnHidden(0,true);
	progList->setColumnHidden(4,true);
	progList->setHorizontalHeaderLabels(QStringList() << "id" << QString::fromUtf8("Tytuł") << "Cykl" << "Czas" << "cyklid");
	updateProgList((what==none));
	
	if (what == prog)
	{
		newsList->clearFocus();
		progList->setFocus(Qt::OtherFocusReason);
	}
	else if (what == news)
	{
		progList->clearFocus();
		newsList->setFocus(Qt::OtherFocusReason);
	}
	
	mw->m_newsList = newsList;
	if (!mw->m_newsHeaderState.isEmpty())
		newsList->horizontalHeader()->restoreState(mw->m_newsHeaderState);
	mw->m_progList = progList;
	if (!mw->m_progHeaderState.isEmpty())
		progList->horizontalHeader()->restoreState(mw->m_progHeaderState);
	preView->setContextMenuPolicy(Qt::NoContextMenu);
	mw->m_newsHeaderState = newsList->horizontalHeader()->saveState();
	qDebug();
}

void ListForm::updateNewsList(bool reinit)
{
	newsList->blockSignals(true);
	newsList->clearContents();
	newsList->blockSignals(false);
	
	QList<News> infLista = getNewsFromDB();
	if (!infLista.isEmpty())
	{
		newsList->setRowCount(infLista.count());
		int row = 0;
		QTableWidgetItem* item = NULL;
		foreach(News nw, infLista)
		{
			//id
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setData(Qt::UserRole, nw.id);
			newsList->setItem(row,0,item);
			
			//data
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(nw.data);
			item->setToolTip(QString::number(nw.id));
			newsList->setItem(row,1,item);
			
			//tytul
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(nw.tytul);
			newsList->setItem(row,2,item);
			
			//miasto
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(nw.miasto);
			newsList->setItem(row,3,item);
			
			//film
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(nw.film ? "F":"");
			if (!nw.film && !nw.avipath.isEmpty())
				item->setText("x");
			newsList->setItem(row,4,item);
			
			//impreza / patronat
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(nw.impreza ? "I":"");
			if (nw.patronat)
				item->setText("P");
			newsList->setItem(row,5,item);
			
			//akcept
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(nw.acceptID==0 ? "X":"");
			newsList->setItem(row,6,item);
			
			++row;
		}
	}
	newsList->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
	if (reinit)
		newsList->horizontalHeader()->resizeSection(2,150);
	if (mw->lastNewsID > -1)
		selectItemID(mw->lastNewsID);
}

void ListForm::updateProgList(bool reinit)
{
	progList->blockSignals(true);
	progList->clearContents();
	progList->blockSignals(false);
	
	QList<Prog> progLista = getProgFromDB();
	if (!progLista.isEmpty())
	{
		progList->setRowCount(progLista.count());
		int row = 0;
		QTableWidgetItem* item = NULL;
		foreach(Prog program, progLista)
		{
			//id
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setData(Qt::UserRole, program.id);
			progList->setItem(row,0,item);
			
			//tytul
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			QString tytul = program.tytul;
			if (program.zablokowany)
				tytul.prepend("[zablokowany] ");
			item->setText(tytul);
			item->setToolTip(QString::number(program.id) + "\n" + program.opis);
			progList->setItem(row,1,item);
			
			//cykl
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(program.cyklTytul);
			progList->setItem(row,2,item);
			
			//czas
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setText(program.czas);
			progList->setItem(row,3,item);

			//cyklID
			item = new QTableWidgetItem();
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			item->setData(Qt::UserRole, program.cyklID);
			item->setToolTip(QString::number(program.cyklID));
			progList->setItem(row,4,item);
		
			
			if (program.zablokowany)
			{
				for (int i=0; i <=4; ++i)
					progList->item(row, i)->setBackgroundColor(QColor(Qt::red));
			}
			++row;
		}
	}
	if (reinit)
	{
		progList->horizontalHeader()->resizeSection(1,200);
		progList->horizontalHeader()->resizeSection(3,150);
	}
	
	if (mw->lastProgID > -1)
		selectItemID(mw->lastProgID, false);
}

void ListForm::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		retranslateUi(this);
		break;
	default:
		break;
	}
}

QList<News> ListForm::getNewsFromDB()
{
	QList<News> infLista;
	QSqlQuery myQuery;
	if (myQuery.exec("SELECT id, DATE(data), tytul, miasto, film, impreza, impreza_patronat, avipath, userID, acceptID FROM K6_archiwum ORDER BY id DESC"))
	{
		while (myQuery.next())
		{
			News inf;
			inf.id = myQuery.value(0).toInt();
			inf.data = myQuery.value(1).toString();
			inf.tytul = myQuery.value(2).toString();
			inf.miasto = myQuery.value(3).toString();
			inf.film = myQuery.value(4).toBool();
			inf.impreza = myQuery.value(5).toBool();
			inf.patronat = myQuery.value(6).toBool();
			inf.avipath = myQuery.value(7).toString();
			inf.userID = myQuery.value(8).toInt();
			inf.acceptID = myQuery.value(9).toInt();
			infLista.append(inf);
		}
	}
	else
		queryError(myQuery,this);
	
	return infLista;
}

QList<Prog> ListForm::getProgFromDB()
{
	QList<Prog> progLista;
	QSqlQuery myQuery;
	
	QMap<int, QString> cykleMap;
	//cykle
	if (myQuery.exec("SELECT * FROM video_cykle ORDER BY tytul ASC"))
	{
		while (myQuery.next())
			cykleMap.insert(myQuery.value(0).toInt(), myQuery.value(1).toString());
	}
	else
		queryError(myQuery,this);
	
	
	if (myQuery.exec("SELECT * FROM video ORDER BY cyklID, tytul ASC"))
	{
		while (myQuery.next())
		{
			Prog program;
			program.id = myQuery.value(0).toInt();
			program.tytul = myQuery.value(1).toString();
			program.opis = myQuery.value(2).toString();
			program.wide = myQuery.value(3).toBool();
			program.zablokowany = myQuery.value(4).toBool();
			program.cyklID = myQuery.value(5).toInt();
			program.cyklTytul = cykleMap.value(program.cyklID);
			program.katID = myQuery.value(6).toString().split(":",QString::SkipEmptyParts);
			program.czas = myQuery.value(7).toString();
			program.oryginal = myQuery.value(8).toString();
			progLista.append(program);
		}
	}
	else
		queryError(myQuery,this);
	
	return progLista;
}

void ListForm::createContextMenus()
{
	newsList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(newsList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayNewsContextMenu(QPoint)));
	
	progList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(progList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayProgContextMenu(QPoint)));
}

int ListForm::getSelectedItemID(bool news)
{
	QTableWidget * table = news ? newsList : progList;
	int row = table->selectedItems().at(0)->row();
	int ID = table->item(row,0)->data(Qt::UserRole).toInt();
	if (news)
		mw->lastNewsID = ID;
	else
		mw->lastProgID = ID;
	return ID;
}

QString ListForm::getSelectedItemTITLE(bool news)
{
	QTableWidget * table = news ? newsList : progList;
	int row = table->selectedItems().at(0)->row();
	QString TITLE = table->item(row,1)->text();
	return TITLE;
}

void ListForm::selectItemID(int itemID, bool news)
{
	QTableWidget * table = news ? newsList : progList;
	
	int rows = table->rowCount();
	int found = -1;
	for(int i = 0; i < rows; ++i)
	{
		if (table->item(i, 0)->data(Qt::UserRole).toInt() == itemID)
		{
			found = i;
			break;
		}
	}
	if (found > -1)
	{
		table->selectRow(found);
		table->scrollToItem(table->item(found,1));
	}
}

void ListForm::displayNewsContextMenu(const QPoint &pos)
{
	if (!mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "_k6_news_all" << "k6_flv", mw->prawaID))
	{
		int newsID = getSelectedItemID();
		QSqlQuery myQuery("SELECT userID FROM K6_archiwum WHERE id=" + QString::number(newsID) + " LIMIT 1");
		myQuery.exec();
		myQuery.first();
		int userID = myQuery.value(0).toInt();
		if (userID != mw->loginID)
			return;
	}
	QMenu menu(this);
	QAction * _dodajFilm = NULL;
	QAction * _kolejkujFilm = NULL;
	QAction * _edytuj = NULL;
	if (mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "_k6_news_all" << "_k6_news_user", mw->prawaID))
		_edytuj = menu.addAction("Edytuj");
	if (mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "k6_flv", mw->prawaID))
	{
		_dodajFilm = menu.addAction("Konwertuj pliki video");
		_kolejkujFilm = menu.addAction("Dodaj video do kolejki na serwerze");
	}
	
	menu.addSeparator();
	QAction *odswiez = menu.addAction(QString::fromUtf8("Odśwież listy"));
	
	QAction *a = menu.exec(newsList->viewport()->mapToGlobal(pos));
	if (_dodajFilm != NULL && a == _dodajFilm)
		newsDodajFilm();
	else if (_kolejkujFilm != NULL && a == _kolejkujFilm)
		newsKolejkujFilm();
	else if (_edytuj != NULL && a == _edytuj)
		newsEdytuj();
	else if (a == odswiez)
		mw->newListForm(news);
}

void ListForm::newsDodajFilm()
{
	emit dodajFilm4News(getSelectedItemID());
}

void ListForm::newsKolejkujFilm()
{
	QString fileName = QFileDialog::getOpenFileName(this,QString :: fromUtf8("Otwórz plik VIDEO"), mw->lastDir, "Pliki VIDEO (*.avi *.mp4)");
	if (!fileName.isEmpty()) {
		mw->lastDir = QFileInfo(fileName).absolutePath();
		QString sd24Path = QDir::toNativeSeparators(fileName);
		int pathStart = sd24Path.indexOf(QString(QDir::separator() + QString("DS_")));
		sd24Path.remove(0,pathStart);
		sd24Path.replace("\\","/");
		QSqlQuery myQuery;
		if (!myQuery.exec("UPDATE K6_archiwum SET film=0, avipath=\"" + sd24Path + "\" WHERE id="+ QString::number(getSelectedItemID())))
			queryError(myQuery,this);
		else
		{
			int row = newsList->selectedItems().at(0)->row();
			newsList->item(row,4)->setText("x");
		}
	}
}

void ListForm::newsEdytuj()
{
	emit editNews(getSelectedItemID());
}

void ListForm::displayProgContextMenu(const QPoint &pos)
{
	if (mw->sprawdzPrawa(QStringList() << "_admin" << "_k6_accept" << "_k6_news_all" <<  "_k6prog_edit" << "k6_flv", mw->prawaID))
	{
		QMenu menu(this);
		QAction * _edit = menu.addAction("Edytuj"); // there can be more than one
		
		QAction * _block = NULL;
		int progID = getSelectedItemID(false);
		QSqlQuery myQuery("SELECT zablokowany FROM video WHERE id=" + QString::number(progID));
		if (myQuery.exec() && myQuery.first() && myQuery.value(0).toBool())
			_block = menu.addAction("Odblokuj");
		else
			_block = menu.addAction("Zablokuj");
		
		menu.addSeparator();
		QAction *odswiez = menu.addAction(QString::fromUtf8("Odśwież listy"));
		
		QAction *a = menu.exec(progList->viewport()->mapToGlobal(pos));
		if (a == _edit)
			progEdytuj();
		else if (a == _block)
			progZmienZablokowany(a->text() == "Zablokuj");
		else if (a == odswiez)
			mw->newListForm(prog);
	}
}

void ListForm::progEdytuj()
{
	emit editProg(getSelectedItemID(false));
}

void ListForm::progZmienZablokowany(bool zablokuj)
{
	int progID = getSelectedItemID(false);
	if (progID > 0)
	{
		QSqlQuery myQuery(QString("UPDATE video SET zablokowany=%1 WHERE id=").arg(zablokuj ? "1":"0") + QString::number(progID));
		if (!myQuery.exec())
			queryError(myQuery,this);
		else
			updateProgList();
	}
}

void ListForm::showNewsPreview()
{
	preView->load(QUrl(QString("http://www.kanal6.pl/newsID=%1,stronaID=32,preview=1/").arg(QString::number(getSelectedItemID()))));
}

void ListForm::showProgPreview()
{
	preView->load(QUrl(QString("http://www.kanal6.pl/progID=%1,stronaID=34,preview=1/").arg(QString::number(getSelectedItemID(false)))));
}

void ListForm::on_progList_itemSelectionChanged()
{
	if (!newsList->selectedItems().isEmpty())
	{
		newsList->blockSignals(true);
		newsList->clearSelection();
		newsList->blockSignals(false);
		newsList->clearFocus();
		mw->lastNewsID = -1;
	}
	showProgPreview();
}

void ListForm::on_newsList_itemSelectionChanged()
{
	if (!progList->selectedItems().isEmpty())
	{
		progList->blockSignals(true);
		progList->clearSelection();
		progList->blockSignals(false);
		progList->clearFocus();
		mw->lastProgID = -1;
	}
	showNewsPreview();
}
