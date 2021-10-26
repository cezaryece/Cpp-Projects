#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>

class FileUtils
{
public:
    static bool removeDir(const QString &dirName);
	static bool removeFiles(const QString &dirName, const QString &ext);
};

#endif // FILEUTILS_H
