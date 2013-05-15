#ifndef __COMPONENTSTRUCTS_H
#define __COMPONENTSTRUCTS_H

#include "IComponent.h"

struct EventInfo
{
	EventInfo() {}
	EventInfo(CHash eventName) : mEventName(eventName) {}
	EventInfo(CHash eventName, CObjectIdHash targetId)  : mEventName(eventName), mTargetId(targetId) {}
	EventInfo(CHash eventName, CObjectIdHash targetId, CObjectIdHash actorId)  : mEventName(eventName), mTargetId(targetId), mActorId(actorId) {}
	CHash		mEventName;		
	CObjectIdHash	mTargetId;		// The object that was affected by this event
	CObjectIdHash	mActorId;		// The object that caused this event
};


#endif //__COMPONENTSTRUCTS_H