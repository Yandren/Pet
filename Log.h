#ifndef LOG_H
#define LOG_H

#include <Windows.h>
#include <fstream>

const int GEN_LOG = 1;
const int VID_LOG = 2;
const int AUDIO_LOG = 3;

class Log
{
public:
	Log();
	~Log();
	static Log &Get();

	bool Init();
	void Shutdown();

	void Write(int target, const char *msg, ...);

protected:

	std::ofstream generalLog;
	std::ofstream videoLog;
	std::ofstream audioLog;
};


#endif