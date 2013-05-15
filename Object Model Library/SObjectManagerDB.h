#ifndef __SOBJECTMANAGERDB_H
#define __SOBJECTMANAGERDB_H

#include <set>
#include <map>
#include "pal.h"
#include "Component System/IComponent.h"


class IComponent;

typedef std::map<CObjectIdHash, IComponent*> CComponentMap;
typedef IComponent* (*ComponentCreationMethod)(void);
typedef bool (*ComponentDestructionMethod)(IComponent *);

struct SComponentTypeInfo
{
	ComponentCreationMethod     mCreationMethod;
	ComponentDestructionMethod  mDestructionMethod;
	CHash                       mTypeHash;
}; 

struct SObjectManagerDB
{
	
	// Static component type data
	SComponentTypeInfo					mComponentTypeInfo[NUM_COMPONENT_TYPE_IDS];
	std::set<EComponentTypeId>			mSet_InterfaceType_to_CmpType[NUM_INTERFACE_IDS];
	
	// Dynamic component data
	std::map<CObjectIdHash, IComponent*>	mMap_CmpType_to_Cmp[NUM_COMPONENT_TYPE_IDS];
	
	// Message data
	std::set<EComponentTypeId>			mSet_MsgType_to_CmpType[NUM_MESSAGE_TYPES];
};

#endif //__SOBJECTMANAGERDB_H