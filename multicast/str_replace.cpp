#include "str_replace.h"
#include <string>

//zamiania fragmentów tekstu jak w PHP str_replace

typedef std::string::size_type Pos;
const Pos EoS = std::string::npos;

char* str_replace_once(const char* what, const char* to, char* str)
{
    if (!str || !what)
        return 0;
    if (!to)
        to = "";
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

char* str_replace(const char* what, const char* to,char* str)
{
    char* p = str;
    while ((p=str_replace_once(what,to,p)) != 0)
        ;
    return str;
}
