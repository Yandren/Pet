#ifndef CLog_H
#define CLog_H

#include <Windows.h>
#include <fstream>

const int GEN_CLog = 1;
const int VID_CLog = 2;
const int AUDIO_CLog = 3;

class CLog
{
public:
	CLog();
	~CLog();
	static CLog &Get();

	bool Init();
	void Shutdown();

	void Write(int target, const char *msg, ...);

protected:

	std::ofstream generalCLog;
	std::ofstream videoCLog;
	std::ofstream audioCLog;
};


#endif