#ifndef __ObjectMANAGER_H
#define __ObjectMANAGER_H

#include "types.h"
#include <set>
#include <map>
#include "pal.h"
#include "Component System/IComponent.h"
#include "SObjectManagerDB.h"
#include <functional>



/************************************
*
* Forward Declarations
*
*************************************/
class IComponent;
class CComponentMessage;
class CComponentByInterfaceIterator;
class CComponentByTypeIterator;
class CComponentByObjectIterator;
class CPostMessageIterator;
class CBroadcastMessageIterator;
struct SObjectManagerDB;


/************************************
*
* Function Pointers
*
*************************************/
typedef std::function<IComponent* (void)> ComponentCreationMethod;
typedef std::function<bool (IComponent *)> ComponentDestructionMethod;

//function pointer to give a specific component's object ID
// to an outside class (e.g. to a manager)
//typedef std::function<void (CObjectIdHash)> CreationCallbackToExternal;

//function pointer to give to DB which will be called by the component
//whenever it needs to pass information outside of the object system
// (e.g. give camera stats to renderer)
typedef std::function<bool (int, void*)> ComponentCallbackToExternal;


class CObjectManager
{

public:
  //Constructors/Destructors
	CObjectManager();
	~CObjectManager();

  //methods
	bool Init(void);
	void DeInit(void);
	bool	LoadObjectsFromFile(const char *fileName);
	// If an interface is registered with an object, returns a pointer to the component
	// that implements it
	IComponent *QueryInterface(CObjectIdHash objId, EInterfaceId iId);
	IComponent *CreateComponent(CObjectIdHash objId, tinyxml2::XMLNode * node);
	// Creates an object, using the value of the node as the object id
	CObjectIdHash	CreateObject(tinyxml2::XMLNode * node);
	void		DestroyAllComponents();

	// The following methods get iterators that iterate over all the components that fulfill the criteria passed in.
	CComponentByInterfaceIterator	GetComponentsByInterfaceId(EInterfaceId iId);
	CComponentByTypeIterator		GetComponentsByComponentTypeId(EComponentTypeId pCmp);
	CComponentByObjectIterator		GetComponentsByObjectId(CObjectIdHash oId);

	// This needs to be called once for each component type. This sets up the class factory that creates a component instance
	void			RegisterComponentType(EComponentTypeId pCmp, ComponentCreationMethod create, ComponentDestructionMethod destroy, CHash typeHash);
	// This lets the object manager know that the given component type implements the interface of the given interface type
	void			RegisterInterfaceWithComponent(EInterfaceId iId, EComponentTypeId cmpId);
	// Sets up a subscription to a particular message type for the given component type. Whenever the message gets sent, it will
	// go out to any components of the types that have subscribed to the message type.
	void			SubscribeToMessageType(EComponentTypeId cmpId, EMessageType msg);
	// Sends a message to all subscribing components of one object (passed in).
	void			PostMessage(CObjectIdHash oId, const CComponentMessage &msg);
	void			PostMessage(CObjectIdHash oId, CComponentMessage &msg);
	// Sends a message to all subscribing components of all objects
	void			BroadcastMessage(const CComponentMessage &msg);
	void			BroadcastMessage(CComponentMessage &);
	EComponentTypeId	GetComponentTypeFromHash(CHash typeName) const;
	// Goes through all the interfaces implemented by the component and finds out if the interface id passed in is one of them.
	bool			IsInterfaceImplementedByComponent(EInterfaceId iID, IComponent * pCmp) const;
  bool      addCallbackForComponent(CObjectIdHash oId, EInterfaceId cmpInterface, ComponentCallbackToExternal func);
  //members

private:
  //methods
  //parses the TinyXml node passed in for objects (and their components) to create
	bool	    LoadObjects(tinyxml2::XMLNode * node);
	void		  RegisterAllComponentTypes(void);
	bool		  AddComponentToDb(CObjectIdHash oId, IComponent* pCmp);
	// Creates an object from the tinyXML node passed in, using the object id passed in
	CObjectIdHash	CreateObject(tinyxml2::XMLNode *, CObjectIdHash);
	// Checks for the existence of an object (one or more component instances with the given object id)
	bool		ObjectExists(CObjectIdHash oId) const;
	// Removes the component from the database. Does not delete the component.
	bool		RemoveComponentFromDb(CObjectIdHash oId, IComponent* pCmp);
  


  //members
	SObjectManagerDB	*mDB;

	friend CComponentByTypeIterator;
	friend CComponentByInterfaceIterator;
	friend CComponentByObjectIterator;
	friend CPostMessageIterator;
	friend CBroadcastMessageIterator;
};

#endif //__ObjectMANAGER_H