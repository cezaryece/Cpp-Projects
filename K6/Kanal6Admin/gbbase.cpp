#include "gbbase.h"
GbBase::GbBase(MainWindow *parent) :
	QGroupBox((QWidget*) parent), mw(parent), con(0), openAVI(0), convertAVI(0), mp4L(0), ogvL(0), webmL(0), converting(false)
{
}
