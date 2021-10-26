#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include "config.h"

void DiskStats(QString path, disk *dsk);
int CheckFreeSpace(QString path, unsigned long long min, bool print = false);

int deleteFiles();
bool deleteDirTree(QString subDirPath);

void sleep(int sec);


#endif // TOOLS_H
