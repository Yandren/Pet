#ifndef __SOBJECTMANAGERDB_H
#define __SOBJECTMANAGERDB_H

#include <set>
#include <map>
#include "pal.h"
#include "Component System/IComponent.h"
#include <functional>


/************************************
*
* Forward Declarations
*
*************************************/
class IComponent;


//callback
//create/destroy callbacks for components
typedef std::function<IComponent* (void)> ComponentCreationMethod;
typedef std::function<bool (IComponent *)> ComponentDestructionMethod;

//typedefs to make maptypes a little more readable
typedef std::map<CComponentIdHash, IComponent*> CCmpIDtoCmpMap;
typedef std::map<CObjectIdHash, IComponent*> CObjIDtoCmpMap;
typedef std::map<CObjectIdHash, ExternalComponentInfoCallback > CObjIDtoCallbackMap;


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
  //an array of object->component mappings, indexed into via component type IDS
	CObjIDtoCmpMap	mMap_ObjID_to_Cmp[NUM_COMPONENT_TYPE_IDS];
	//an array of object->callback mappings, indexed into via Interface type IDs
  CObjIDtoCallbackMap mMapCallbackToObjectWithCmp[NUM_INTERFACE_IDS];
	// Message data
	std::set<EComponentTypeId>			mSet_MsgType_to_CmpType[NUM_MESSAGE_TYPES];
};

#endif //__SOBJECTMANAGERDB_H