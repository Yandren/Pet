#ifndef __ICOMPONENT_H
#define __ICOMPONENT_H

#include "types.h"
#include "pal.h"
#include "IObject.h"

// All the component types available to the game. Any new component type needs a corresponding enum value in here
enum EComponentTypeId
{
	CID_ENTITY = 0,
	CID_PLAYER,
	CID_RENDERABLE,
	CID_PHYSICS,
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
	NUM_INTERFACE_IDS
};

//Messaging enums
enum EMessageType
{
	MT_UPDATE,
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
	MT_RENDER,
	NUM_MESSAGE_TYPES
};

enum EMessageResult
{
	MR_FALSE,
	MR_TRUE,
	MR_IGNORED,
	MR_ERROR
};

// Forward declarations
namespace tinyxml2 {class XMLNode;}
class CComponentMessage;
class ICmpEntity;
class ObjectManager;


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


// The IComponent class. All our component classes inherit from this
class IComponent
{
	friend class CObjectManager;

public:
	IComponent();
	virtual ~IComponent();
	virtual bool    Init(CObjectIdHash, tinyxml2::XMLNode &) = 0;
	virtual void    Deinit(void) = 0;
	CObjectIdHash       GetObjectId(void) const     { return mObjectId; }
	ICmpEntity      *GetEntity() const;
	virtual EMessageResult		HandleMessage(const CComponentMessage &) = 0;
	virtual EComponentTypeId	GetComponentTypeId(void) = 0;
protected:
	void            SetObjectId(CObjectIdHash oId)  { mObjectId = oId; }
	CObjectIdHash       mObjectId;

	
};
#endif //__ICOMPONENT_H