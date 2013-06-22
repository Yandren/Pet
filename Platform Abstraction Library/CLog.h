#ifndef CLog_H
#define CLog_H

#include <Windows.h>
#include <fstream>


enum ELogType 
{
  LOG_GENERAL,
  LOG_VIDEO,
  LOG_AUDIO,
  LOG_ERROR
};

class CLog
{
public:
	CLog();
	~CLog();
	static CLog* Get();

	bool Init();
	void DeInit();

	void Write(int target, const char *msg, ...);

protected:

	std::ofstream generalCLog;
	std::ofstream videoCLog;
	std::ofstream audioCLog;
	std::ofstream errorCLog;
};


#endif