#ifndef __CMESSAGE_H
#define __CMESSAGE_H

#include "pal.h"
#include "ComponentStructs.h"
#include "glm\glm\glm.hpp"
#include <functional>

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
  SSpacialInfo() {}
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

typedef std::function< bool ( int, SSpacialInfo ) > SpacialCallback_t;

struct SSpacialCallbackInfo
{
  SSpacialCallbackInfo(){}
  SSpacialCallbackInfo(SpacialCallback_t callback) : mCallback(callback){}
  
  SpacialCallback_t mCallback;
};

#endif //__CMESSAGE_H