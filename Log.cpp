#include "Log.h"

Log::Log(){}

Log::~Log(){}

Log &Log::Get()
{
	static Log log;
	return log;
}

bool Log::Init()
{
	generalLog.open("genlog.txt");
	videoLog.open("vidlog.txt");
	audioLog.open("audiolog.txt");

	return true;
}

void Log::Shutdown()
{
	generalLog.close();
	videoLog.close();
	audioLog.close();
}

void Log::Write(int target, const char *msg, ...)
{
	va_list args; va_start(args,msg);// get additional params
	char szBuf[1024];
	vsprintf_s(szBuf,msg,args);

	switch(target){
	case GEN_LOG:
		generalLog<< szBuf <<"\n";
		generalLog.flush();
		break;
	case VID_LOG:
		videoLog<<szBuf<<"\n";
		videoLog.flush();
		break;
	case AUDIO_LOG:
		audioLog<<szBuf<<"\n";
		audioLog.flush();
		break;
	default:
		generalLog<<szBuf<<"\n";
		generalLog.flush();
		break;

	}

}
