#ifndef LOG_H
#define LOG_H

#include <Windows.h>
#include "MemManager.h"
#include <fstream>


const int LOG_APP=1;
const int LOG_CLIENT=2;
const int LOG_SERVER=4;
const int LOG_USER=8;

#define MAX_LOG_STRINGS 256

class CLog  
{
protected:
	CLog();

	std::ofstream appLog;
	std::ofstream clientLog;
	std::ofstream serverLog;

	std::string logStrings[MAX_LOG_STRINGS];
	bool LoadStrings();

public:
	static CLog &Get();

	bool Init();
	void Shutdown();

	void Write(int target, const char *msg, ...);
	void Write(int target, unsigned long msgID, ...);
};

#endif