#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
    #define AccessPath _access
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
    #define AccessPath access 
 #endif



//using namespace std;

namespace Utilities {
void tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters = " ");
std::string getCWD();
bool pathExists(const char *path);
}

#endif