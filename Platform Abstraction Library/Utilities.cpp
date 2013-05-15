#include "Utilities.h"


void Utilities::tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters) {
    
	// Skip delimiters at beginning
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first non-delimiter
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos) {
       // Found a piece of a token, add it to the vector
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next non-delimiter
        pos = str.find_first_of(delimiters, lastPos);
    }
}



std::string Utilities::getCWD(){

	char CurrentPath[FILENAME_MAX];
	return GetCurrentDir(CurrentPath, (sizeof(CurrentPath) / sizeof(char)));

}

bool Utilities::pathExists(const char *path)
{ return ( AccessPath(path, 0) == 0 ); }