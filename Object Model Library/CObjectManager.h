#ifndef __ObjectMANAGER_H
#define __ObjectMANAGER_H

#include "types.h"
#include <set>
#include <map>
#include "pal.h"
#include "Component System/IComponent.h"
#include "SObjectManagerDB.h"



//forward declarations
class IComponent;
class CComponentMessage;
class CComponentByInterfaceIterator;
class CComponentByTypeIterator;
class CComponentByObjectIterator;
class CPostMessageIterator;
class CBroadcastMessageIterator;
struct SObjectManagerDB;


//function pointers for Intefaces
typedef IComponent* (*ComponentCreationMethod)(void);
typedef bool (*ComponentDestructionMethod)(IComponent *);

class CObjectManager
{

public:
	CObjectManager();
	~CObjectManager();

	bool Init(void);
	void DeInit(void);

	bool	LoadObjectsFromFile(const char *fileName);

	// If an interface is registered with an object, returns a pointer to the component
	// that implements it
	IComponent *QueryInterface(CObjectIdHash, EInterfaceId);
	IComponent *CreateComponent(CObjectIdHash, tinyxml2::XMLNode *);

	// Creates an object, using the value of the node as the object id
	CObjectIdHash	CreateObject(tinyxml2::XMLNode *);

	void		DestroyAllComponents();

	// The following methods get iterators that iterate over all the components that fulfill the criteria passed in.
	CComponentByInterfaceIterator	GetComponentsByInterfaceId(EInterfaceId);
	CComponentByTypeIterator		GetComponentsByComponentTypeId(EComponentTypeId);
	CComponentByObjectIterator		GetComponentsByObjectId(CObjectIdHash);

	// This needs to be called once for each component type. This sets up the class factory that creates a component instance
	void			RegisterComponentType(EComponentTypeId, ComponentCreationMethod, ComponentDestructionMethod, CHash typeHash);
	// This lets the object manager know that the given component type implements the interface of the given interface type
	void			RegisterInterfaceWithComponent(EInterfaceId, EComponentTypeId);

	// Sets up a subscription to a particular message type for the given component type. Whenever the message gets sent, it will
	// go out to any components of the types that have subscribed to the message type.
	void			SubscribeToMessageType(EComponentTypeId, EMessageType);
	// Sends a message to all subscribing components of one object (passed in).
	void			PostMessage(CObjectIdHash oid, const CComponentMessage &msg);
	void			PostMessage(CObjectIdHash, CComponentMessage &);
	// Sends a message to all subscribing components of all objects
	void			BroadcastMessage(const CComponentMessage &msg);
	void			BroadcastMessage(CComponentMessage &);

	EComponentTypeId	GetComponentTypeFromHash(CHash typeName) const;
	// Goes through all the interfaces implemented by the component and finds out if the interface id passed in is one of them.
	bool			IsInterfaceImplementedByComponent(EInterfaceId, IComponent *) const;

private:
  //parses the TinyXml node passed in for objects (and their components) to create
	bool	    LoadObjects(tinyxml2::XMLNode *);

	void		  RegisterAllComponentTypes(void);
	bool		  AddComponentToDb(CObjectIdHash, IComponent*);

	// Creates an object from the tinyXMl node passed in, using the object id passed in
	CObjectIdHash	CreateObject(tinyxml2::XMLNode *, CObjectIdHash);

	// Checks for the existence of an object (one or more component instances with the given object id)
	bool		ObjectExists(CObjectIdHash oId) const;

	// Removes the component from the database. Does not delete the component.
	bool		RemoveComponentFromDb(CObjectIdHash oId, IComponent* pCmp);
private:
	SObjectManagerDB	*mDB;

	friend CComponentByTypeIterator;
	friend CComponentByInterfaceIterator;
	friend CComponentByObjectIterator;
	friend CPostMessageIterator;
	friend CBroadcastMessageIterator;
};

#endif //__ObjectMANAGER_H