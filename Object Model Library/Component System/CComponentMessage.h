#ifndef __CMESSAGE_H
#define __CMESSAGE_H

#include "pal.h"
#include "ComponentStructs.h"
#include "glm\glm\glm.hpp"

class CComponentMessage
{
public:
	CComponentMessage(){}
	CComponentMessage(EMessageType type) : mType(type){}
	CComponentMessage(EMessageType type, void *data) : mType(type), mpData(data){}

public:
	EMessageType	mType;
	void*			mpData;
};


//Below are the types of structures we're using to pass info via messages

struct SSpacialInfo
{
  SSpacialInfo() {};
  SSpacialInfo(glm::vec4 position,
               glm::vec4 direction,
               glm::vec4 orientation)
               : mPosition(position),
                 mDirection(direction),
                 mOrientation(orientation) {};
  glm::vec4 mPosition;
  glm::vec4 mDirection;
  glm::vec4 mOrientation;
};
#endif //__CMESSAGE_H