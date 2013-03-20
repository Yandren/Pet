#include "Utilities.h"


void tokenize(const string &str, vector<string> &tokens, const string &delimiters) {
    
	// Skip delimiters at beginning
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first non-delimiter
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
       // Found a piece of a token, add it to the vector
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next non-delimiter
        pos = str.find_first_of(delimiters, lastPos);
    }
}



string getCWD(){

	char CurrentPath[FILENAME_MAX];
	return GetCurrentDir(CurrentPath, (sizeof(CurrentPath) / sizeof(char)));

}