#ifndef __CMESSAGE_H
#define __CMESSAGE_H

#include "pal.h"

class CComponentMessage
{
public:
	CComponentMessage()																	{}
	CComponentMessage(EMessageType type) : mType(type)									{}
	CComponentMessage(EMessageType type, void *data) : mType(type), mpData(data)			{}

public:
	EMessageType	mType;
	void*			mpData;
};

#endif //__CMESSAGE_H