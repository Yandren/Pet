#include "Log.h"

CLog::CLog()
{

}

CLog &CLog::Get()
{
	static CLog log;
	return log;
}

bool CLog::Init()
{
	appLog.open("applog.txt");
	clientLog.open("clntlog.txt");
	serverLog.open("srvrlog.txt");
	//user errors get logged to client

	//load the strings file
	if(!LoadStrings())return false;

	return true;
}

void CLog::Shutdown()
{
	appLog.close();
	clientLog.close();
	serverLog.close();
}

void CLog::Write(int target, const char *msg, ...)
{
	va_list args; va_start(args,msg);// get additional params
	char szBuf[1024];
	vsprintf_s(szBuf,msg,args);

	if(target&LOG_APP)
	{
		appLog<<szBuf<<"\n";
		appLog.flush();
	}
	if(target&LOG_CLIENT)
	{
		clientLog<<szBuf<<"\n";
		clientLog.flush();
	}
	if(target&LOG_SERVER)
	{
		serverLog<<szBuf<<"\n";
		serverLog.flush();
	}
	if(target&LOG_USER)
	{

	}
	va_end(args);
}

void CLog::Write(int target, unsigned long msgID, ...)
{
	va_list args; va_start(args, msgID);
	char szBuf[1024];
	vsprintf_s(szBuf,logStrings[msgID].c_str(),args);
	Write(target,szBuf);
	va_end(args);
}


bool CLog::LoadStrings()
{
	std::ifstream in("strings.txt");
	if(!in.is_open())return false;

	unsigned long index=0;

	while(!in.eof())
	{
		char szBuf[1024];
		in.getline(szBuf,1024);
		logStrings[index++]=szBuf;
	}

	return true;
}