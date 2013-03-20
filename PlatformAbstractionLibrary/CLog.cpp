#include "CLog.h"

CLog::CLog(){}

CLog::~CLog(){}

CLog &CLog::Get()
{
	static CLog CLog;
	return CLog;
}

bool CLog::Init()
{
	generalCLog.open("genCLog.txt");
	videoCLog.open("vidCLog.txt");
	audioCLog.open("audioCLog.txt");

	return true;
}

void CLog::Shutdown()
{
	generalCLog.close();
	videoCLog.close();
	audioCLog.close();
}

void CLog::Write(int target, const char *msg, ...)
{
	va_list args; va_start(args,msg);// get additional params
	char szBuf[1024];
	vsprintf_s(szBuf,msg,args);

	switch(target){
	case GEN_CLog:
		generalCLog<< szBuf <<"\n";
		generalCLog.flush();
		break;
	case VID_CLog:
		videoCLog<<szBuf<<"\n";
		videoCLog.flush();
		break;
	case AUDIO_CLog:
		audioCLog<<szBuf<<"\n";
		audioCLog.flush();
		break;
	default:
		generalCLog<<szBuf<<"\n";
		generalCLog.flush();
		break;

	}

}
