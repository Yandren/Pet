#include "CLog.h"

#include "Globals.h"


CLog::CLog(){}

CLog::~CLog(){}

CLog &CLog::Get()
{
	static CLog CLog;
	return CLog;
}

bool CLog::Init()
{
	char * base = const_cast<char*>(Globals::BASE_DIR);
  std::string gen = base; gen.append("generalLog.txt");
  std::string vid = base; vid.append("videoLog.txt");
  std::string aud = base; aud.append("audioLog.txt");
  std::string err = base; err.append("errorLog.txt");

	try
	{
    generalCLog.open(gen);
	  videoCLog.open(vid);
	  audioCLog.open(aud);
	  errorCLog.open(err);
	}
	catch(std::exception e){
		return false;
	}
	return true;
}

void CLog::Shutdown()
{
	generalCLog.close();
	videoCLog.close();
	audioCLog.close();
	errorCLog.close();
}

void CLog::Write(int target, const char *msg, ...)
{
	va_list args; va_start(args,msg);// get additional params
	char szBuf[1024];
	vsprintf_s(szBuf,msg,args);

	switch(target){
	case  LOG_GENERAL:
		generalCLog<< szBuf <<"\n";
		generalCLog.flush();
		break;
	case  LOG_VIDEO:
		videoCLog<<szBuf<<"\n";
		videoCLog.flush();
		break;
	case LOG_AUDIO:
		audioCLog<<szBuf<<"\n";
		audioCLog.flush();
		break;
	case LOG_ERROR:
		errorCLog << szBuf<<"\n";
		errorCLog.flush();
    generalCLog<< "--ERROR-- " << szBuf <<"\n";
		generalCLog.flush();
    break;
		//also write errors in the general log
	default:
		generalCLog<<szBuf<<"\n";
		generalCLog.flush();
		break;

	}

}
