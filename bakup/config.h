#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>

class Config
{
public:
	Config();
	Config(string configFilePath);
	string sourceDir, destinationDir, eMail, user, host;
	long long freeGB;
	bool print, verbose, logRename, debug, halt;
	int weeksBeforeDelete;
};

#endif // CONFIG_H
