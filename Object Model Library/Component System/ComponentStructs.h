#ifndef __COMPONENTSTRUCTS_H
#define __COMPONENTSTRUCTS_H

//#include "IComponent.h"
#include <functional>
#include "types.h"

//callbacks for components to call whenever an external source wants
//some kind of data
//(e.g. - video manager wants data from camera object
//  to calculate with, etc)
typedef std::function<bool (int, void *)> ExternalComponentInfoCallback;


struct EventInfo
{
  //Constructors
	EventInfo() {}
	EventInfo(CHash eventName) : mEventName(eventName) {}
	EventInfo(CHash eventName, CObjectIdHash targetId)  : mEventName(eventName), mTargetId(targetId) {}
	EventInfo(CHash eventName, CObjectIdHash targetId, CObjectIdHash actorId)  : mEventName(eventName), mTargetId(targetId), mActorId(actorId) {}
	//member variables
  CHash		      mEventName;		
	CObjectIdHash	mTargetId;		// The object that was affected by this event
	CObjectIdHash	mActorId;		// The object that caused this event
};

// All the component types available to the game. Any new component type needs a corresponding enum value in here
enum EComponentTypeId
{
	CID_ENTITY = 0,
	CID_PLAYER,
	CID_RENDERABLE,
	CID_PHYSICS,
  CID_INPUT,
	NUM_COMPONENT_TYPE_IDS,
	CID_INVALID
};

// All the interface types available to the game. Any new interface type needs a corresponding enum value in here
enum EInterfaceId
{
	IID_ENTITY = 0,
	IID_PLAYER,
	IID_RENDERABLE,
	IID_PHYSICS,
  IID_INPUT,
	NUM_INTERFACE_IDS
};

//Messaging enums
enum EMessageType
{
	MT_UPDATE,
  MT_CALLBACK_INFO,
	MT_OBJECT_CREATED,
	MT_ALL_OBJECTS_CREATED,
	MT_COMMAND,
	MT_EXAMINE_INVENTORY,
	MT_SET_INVENTORY_ITEM_POS,
	MT_BE_PICKED_UP,
	MT_PICK_UP,
	MT_PICK_UP_SUCCESSFUL,
	MT_HIDE,
	MT_SHOW,
	MT_EVENT,
	MT_INIT_RENDER,
  MT_RENDER,
  MT_SPACIAL_REQ,
  MT_SPACIAL_REQ_LOCAL,
  MT_SPACIAL,
	MT_FRUSTUM_CULL,
	MT_EXPLICIT_CULL,
	MT_CLEAR_CULL_FLAG,
  MT_KEYBOARD_INPUT,
  MT_MOUSE_INPUT,
  MT_AI_INPUT,
  MT_NETWORK_INPUT,
	NUM_MESSAGE_TYPES
};

enum EMessageResult
{
	MR_FALSE,
	MR_TRUE,
	MR_IGNORED,
	MR_ERROR
};

#endif //__COMPONENTSTRUCTS_H