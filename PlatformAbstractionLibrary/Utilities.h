#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>

#ifdef WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif



using namespace std;


void tokenize(const string &str, vector<string> &tokens, const string &delimiters = " ");
string getCWD();

#endif