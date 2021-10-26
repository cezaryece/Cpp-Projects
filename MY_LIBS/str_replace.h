#ifndef STR_REPLACE_H
#define STR_REPLACE_H


//zamiania fragmentów tekstu jak w PHP str_replace

# include <string>

char* str_replace(char* what, char* to, char* str);
std::string string_replace(std::string what, std::string to, std::string str);

#endif // STR_REPLACE_H
