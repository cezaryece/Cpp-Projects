#include "task.h"
#include <QCoreApplication>
#include <QTimer>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Task *task = new Task(&a);
	QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
	QTimer::singleShot(0, task, SLOT(run()));
	return a.exec();
}
