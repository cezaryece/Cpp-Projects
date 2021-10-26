#include "str_replace.h"
#include <string>
#include <cstring>

//zamiania fragmentów tekstu jak w PHP str_replace

typedef std::string::size_type Pos;
const Pos EoS = std::string::npos;


char* str_replace_once(char* what, char* to, char* str)
{
	if (!str || !what)
		return 0;
	if (!to)
		to = (char*)"";
	std::string sstr(str);
	std::string swhat(what);
	Pos pos = sstr.find(swhat);
	if (pos != EoS)
	{
		sstr.replace(pos,swhat.length(),to);
		return strcpy(str,sstr.c_str());
	}
	return 0;
}

char* str_replace(char* what, char* to,char* str)
{
	char* p = str;
	while ( (p=str_replace_once(what,to,p)) != 0 ) ;
	return str;
}

std::string string_replace_once(std::string swhat, std::string to, std::string sstr)
{
	if (sstr=="" || swhat=="")
		return 0;
	Pos pos = sstr.find(swhat);
	if (pos != EoS)
	{
		sstr.replace(pos,swhat.length(),to);
		return sstr;
	}
	return "";
}

std::string string_replace(std::string what, std::string to, std::string str)
{
	std::string p;
	p = str;
	while ((p=string_replace_once(what,to,p)) != "") str = p;
	return str;
}
