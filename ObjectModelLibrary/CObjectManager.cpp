#include "types.h"
#include "CObjectManager.h"
#include "ComponentSystem/ComponentIterators.h"
#include "tinyxml2.h"
#include <assert.h>
#include "ComponentSystem/CComponentMessage.h"


// All the component classes
#include "CCmpEntity.h"
#include "CCmpPhysics.h"
#include "CCmpRenderable.h"
#include "CCmpPlayer.h"




CObjectManager::CObjectManager() : mDB(NULL)
{
}

CObjectManager::~CObjectManager()
{
	DeInit();
}

bool CObjectManager::Init()
{
	try{
	  if (mDB != NULL)
	  {
	  	delete mDB;
	  }
	  mDB = new SObjectManagerDB();

  	  RegisterAllComponentTypes();

	  return true;}
	catch(std::exception e){
		return false;
	}
}

void CObjectManager::DeInit(void)
{
	if (mDB != NULL)
	{
		DestroyAllComponents();

		// Now get rid of the database
		delete mDB;
		mDB = NULL;
	}
}

bool CObjectManager::LoadObjectsFromFile(const char *fileName)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	LoadObjects(&doc);


	return true;
}

bool CObjectManager::LoadObjects(tinyxml2::XMLNode *docRoot)
{
	//travel the nodes, find objects, create them where needed
	tinyxml2::XMLElement *objectsRoot = docRoot->FirstChildElement("Objects");
	
	for (tinyxml2::XMLNode *cur = objectsRoot->FirstChild(); cur = cur->NextSibling(); cur == NULL)
	{
		if (cur->FirstChild()->ToText()->Value() != "Object")
		{
			return false;
		}
		CObjectIdHash oId = CreateObject(cur);
		
		PostMessage(oId, MT_OBJECT_CREATED);
	}
	return true;
}

void CObjectManager::DestroyAllComponents()
{
	for (int32_t cmpType = 0 ; cmpType < NUM_COMPONENT_TYPE_IDS ; ++cmpType)
	{
		for (CComponentByTypeIterator iter(static_cast<EComponentTypeId>(cmpType)) ; !iter.IsDone() ; ++iter)
		{
			IComponent *pCmp = iter.GetComponent();
			// Deinit and delete each component
			pCmp->Deinit();
			mDB->mComponentTypeInfo[cmpType].mDestructionMethod(pCmp);
		}

		// Clear the map
		mDB->mComponentTypeToComponentMap[cmpType].clear();
	}
}

CComponentByTypeIterator CObjectManager::GetComponentsByComponentTypeId(EComponentTypeId type)
{
	CComponentByTypeIterator iter(type);
	return iter;
}

CComponentByInterfaceIterator CObjectManager::GetComponentsByInterfaceId(EInterfaceId iid)
{
	CComponentByInterfaceIterator iter(iid);
	return iter;
}

CComponentByObjectIterator CObjectManager::GetComponentsByObjectId(CObjectIdHash oid)
{
	CComponentByObjectIterator iter(oid);
	return iter;
}

// This method calls the static method RegisterComponentType() in each component class. This method
// in turn sets up everything necessary for the component in question.
void CObjectManager::RegisterAllComponentTypes()
{
	CCmpEntity::RegisterComponentType();
	CCmpRenderable::RegisterComponentType();
	CCmpPhysics::RegisterComponentType();
	CCmpPlayer::RegisterComponentType();
}

void CObjectManager::RegisterInterfaceWithComponent(EInterfaceId iid, EComponentTypeId cid)
{
	mDB->mInterfaceTypeToComponentTypes[iid].insert(cid);
}

void CObjectManager::RegisterComponentType(EComponentTypeId cmpID, ComponentCreationMethod pCreationFn, ComponentDestructionMethod pDestructionFn, CHash typeHash)
{
	mDB->mComponentTypeInfo[cmpID].mCreationMethod = pCreationFn;
	mDB->mComponentTypeInfo[cmpID].mDestructionMethod = pDestructionFn;
	mDB->mComponentTypeInfo[cmpID].mTypeHash = typeHash;
}

IComponent *CObjectManager::QueryInterface(CObjectIdHash oId, EInterfaceId iid)
{
	std::set<EComponentTypeId> &cmpTypeSet = mDB->mInterfaceTypeToComponentTypes[iid];
	std::set<EComponentTypeId>::iterator cmpTypeSetIter;

	for (cmpTypeSetIter = cmpTypeSet.begin() ; cmpTypeSetIter != cmpTypeSet.end() ; ++cmpTypeSetIter)
	{
		EComponentTypeId cmpType = (*cmpTypeSetIter);
		CComponentMap &cmpMap = mDB->mComponentTypeToComponentMap[cmpType];
		CComponentMap::iterator cmpMapIter = cmpMap.find(oId);
		if (cmpMapIter != cmpMap.end())
		{ // We found our component
			return (*cmpMapIter).second;
		}
	}
	return NULL;
}

IComponent *CObjectManager::CreateComponent(CObjectIdHash oId, tinyxml2::XMLNode *node)
{
	//grab the name of component from XML Node
	CHash cmpName = CHash(node->FirstChildElement("Component")->Attribute("name"));
	// Get the component type from the node
	EComponentTypeId cTypeId = GetComponentTypeFromHash(cmpName);

	if (cTypeId == CID_INVALID)
	{ // Don't know this one
		return NULL;
	}

	// Call the component creation method
	assert(mDB->mComponentTypeInfo[cTypeId].mCreationMethod);
	IComponent *pCmp = mDB->mComponentTypeInfo[cTypeId].mCreationMethod();

	if (pCmp != NULL)
	{
		pCmp->SetObjectId(oId);
		pCmp->Init(oId, *node);
	}
	return pCmp;
}

CObjectIdHash CObjectManager::CreateObject(tinyxml2::XMLNode *node)
{
	return CreateObject(node, node->FirstChildElement("Object")->Value());
}

CObjectIdHash CObjectManager::CreateObject(tinyxml2::XMLNode *node, CObjectIdHash oId)
{
	assert(node->Value() == "Object");

	if (ObjectExists(oId))
	{
		return CHash();
	}

	// Create all the components, and add them to the db
	for (tinyxml2::XMLNode *child = node->FirstChild() ; child != NULL ; child = child->NextSibling())
	{
		IComponent *cmp = CreateComponent(oId, child);
		AddComponentToDb(oId, cmp);
	}
	return oId;
}

EComponentTypeId CObjectManager::GetComponentTypeFromHash(CHash typeName) const
{
	for (int32_t i = 0 ; i < NUM_COMPONENT_TYPE_IDS ; ++i)
	{
		if (mDB->mComponentTypeInfo[i].mTypeHash == typeName)
		{
			return static_cast<EComponentTypeId>(i);
		}
	}
	return CID_INVALID;
}

bool CObjectManager::ObjectExists(CObjectIdHash oId) const
{
	for (int32_t cmpType = 0 ; cmpType < NUM_COMPONENT_TYPE_IDS ; ++cmpType)
	{
		CComponentMap &cmpMap = mDB->mComponentTypeToComponentMap[cmpType];
		CComponentMap::iterator cmpMapIter = cmpMap.find(oId);
		if (cmpMapIter != cmpMap.end())
		{ // We found a component belonging to this object, so the object exists.
			return true;
		}
	}
	return false;
}

bool CObjectManager::AddComponentToDb(CObjectIdHash oId, IComponent *pCmp)
{ // Inserts pComp with the key oId, and returns whether the insert was successful
	return (mDB->mComponentTypeToComponentMap[pCmp->GetComponentTypeId()].insert(CComponentMap::value_type(oId, pCmp))).second;
}

bool CObjectManager::IsInterfaceImplementedByComponent(EInterfaceId iId, IComponent *pCmp) const
{
	if (mDB->mInterfaceTypeToComponentTypes[iId].find(pCmp->GetComponentTypeId()) == mDB->mInterfaceTypeToComponentTypes[iId].end())
	{
		return false;
	}
	return true;
}

void CObjectManager::SubscribeToMessageType(EComponentTypeId ctid, EMessageType mtid)
{
	mDB->mMessageTypeToComponentTypes[mtid].insert(ctid);
}

void CObjectManager::PostMessage(CObjectIdHash oid, const CComponentMessage &msg)
{
	PostMessage( oid, *const_cast<CComponentMessage *>(&msg));
}

void CObjectManager::PostMessage(CObjectIdHash oid, CComponentMessage &msg)
{
	std::set<EComponentTypeId>	&cmpSet = mDB->mMessageTypeToComponentTypes[msg.mType];
	std::set<EComponentTypeId>::iterator cmpSetIter;

	// Find the component types that subscribe to this message
	for (cmpSetIter = cmpSet.begin() ; cmpSetIter != cmpSet.end() ; ++cmpSetIter)
	{
		EComponentTypeId	ctid = (*cmpSetIter); // Found one

		// Go through the components of this component type and send message
		for (CComponentByTypeIterator ci =  GetComponentsByComponentTypeId(ctid) ; !ci.IsDone() ; ++ci)
		{
			IComponent *pCmp = ci.GetComponent();
			if (pCmp->GetObjectId() == oid)
			{
				pCmp->HandleMessage(msg);
			}
		}
	}
}

void CObjectManager::BroadcastMessage(const CComponentMessage &msg)
{
	BroadcastMessage(*const_cast<CComponentMessage *>(&msg));
}

void CObjectManager::BroadcastMessage(CComponentMessage &msg)
{
	std::set<EComponentTypeId>	&cmpSet = mDB->mMessageTypeToComponentTypes[msg.mType];
	std::set<EComponentTypeId>::iterator cmpSetIter;

	// Find the component types that subscribe to this message
	for (cmpSetIter = cmpSet.begin() ; cmpSetIter != cmpSet.end() ; ++cmpSetIter)
	{
		EComponentTypeId	ctid = (*cmpSetIter); // Found one

		// Go through the components of this component type and send message
		for (CComponentByTypeIterator ci =  GetComponentsByComponentTypeId(ctid) ; !ci.IsDone() ; ++ci)
		{
			ci.GetComponent()->HandleMessage(msg);
		}
	}
}



