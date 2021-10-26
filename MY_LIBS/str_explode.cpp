#include "str_explode.h"
#include <string>
#include <vector>
#include "unspace.h"

void str_explode(std::string what, std::string separator, vector<string> * Sarray) {

    uint separator_position = what.find(separator);
    if (separator_position != string::npos) {
        what.erase(separator_position,separator.length());
        Sarray.push_back(unspace(what.substr(0,separator_position)));
        Sarray.push_back(unspace(what.substr(separator_position)));
    }
    else {
        Sarray.push_back(unspace(what));
        Sarray.push_back("");
    }
}
