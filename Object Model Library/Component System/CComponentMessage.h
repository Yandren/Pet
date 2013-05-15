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


//Below are the types of structures we're using to pass info via messages

struct SPositionInfo
{
  SPositionInfo() {};
  SPositionInfo(float x, float y, float z) : x_pos(x), y_pos(y), z_pos(z) {};
	float x_pos;
	float y_pos;
	float z_pos;
};

#endif //__CMESSAGE_H