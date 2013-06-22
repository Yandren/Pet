#include "types.h"
#include "CObjectManager.h"
#include "Component System/ComponentIterators.h"
#include "tinyxml2.h"
#include <assert.h>
#include "Component System/CComponentMessage.h"


// All the component classes
#include "CCmpEntity.h"
#include "CCmpPhysics.h"
#include "CCmpRenderable.h"
#include "CCmpPlayer.h"
#include "CCmpUserInput.h"


//A few constant strings we'll be searching for, hashed
const CHash OBJ = CHash("object");
const CHash OBJS = CHash("objects");
const CHash OBJFILE = CHash("objectsfile");
const CHash COMPONENT = CHash("component");




CObjectManager::CObjectManager() : mDB(NULL)
{
}

CObjectManager::~CObjectManager()
{
  DeInit();
}

bool CObjectManager::Init()
{
  CLog::Get()->Write( LOG_GENERAL, "Object Manager Init");
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
  tinyxml2::XMLError err;
  CLog::Get()->Write( LOG_GENERAL, "Loading objects from file");
  tinyxml2::XMLDocument doc;
  if( Utilities::pathExists(fileName))
    err = doc.LoadFile(fileName);

  if(doc.Error() || err != 0)
    return false;

  return LoadObjects(&doc);
}

bool CObjectManager::LoadObjects(tinyxml2::XMLNode *docRoot)
{
  CLog::Get()->Write( LOG_GENERAL, "Loading Objects from XML doc");

  //travel the nodes, find objects, create them where needed
  tinyxml2::XMLElement *objectsRoot = docRoot->FirstChildElement("objectsfile")->FirstChildElement("objects");

  if(!objectsRoot){
    CLog::Get()->Write( LOG_GENERAL, "Failed to load objects, no \'objects\' root");
    return false;
  }

  for (tinyxml2::XMLElement *cur = objectsRoot->FirstChildElement("object"); cur != NULL; cur = cur->NextSiblingElement("object"))
  {
    std::string valStr = cur->Value();

    if (valStr.compare("object") != 0)
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
    mDB->mMap_ObjID_to_Cmp[cmpType].clear();
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
  //TODO - this is fucking gross, make this happen dynamically without having to keep track manually
  //Maybe parse this from the XML file based on naming convention
  //or even do some weird template compiler magic shit
  //anything but this
  //for the love of all that is holy
  //anything
  CCmpEntity::RegisterComponentType();
  CCmpRenderable::RegisterComponentType();
  CCmpPhysics::RegisterComponentType();
  CCmpPlayer::RegisterComponentType();
  CCmpUserInput::RegisterComponentType();
}

void CObjectManager::RegisterInterfaceWithComponent(EInterfaceId iid, EComponentTypeId cid)
{
  mDB->mSet_InterfaceType_to_CmpType[iid].insert(cid);
}

void CObjectManager::RegisterComponentType(EComponentTypeId cmpID, ComponentCreationMethod pCreationFn, ComponentDestructionMethod pDestructionFn, CHash typeHash)
{
  mDB->mComponentTypeInfo[cmpID].mCreationMethod = pCreationFn;
  mDB->mComponentTypeInfo[cmpID].mDestructionMethod = pDestructionFn;
  mDB->mComponentTypeInfo[cmpID].mTypeHash = typeHash;
}

IComponent *CObjectManager::QueryInterface(CObjectIdHash oId, EInterfaceId iid)
{
  std::set<EComponentTypeId> &cmpTypeSet = mDB->mSet_InterfaceType_to_CmpType[iid];
  std::set<EComponentTypeId>::iterator cmpTypeSetIter;

  for (cmpTypeSetIter = cmpTypeSet.begin() ; cmpTypeSetIter != cmpTypeSet.end() ; ++cmpTypeSetIter)
  {
    EComponentTypeId cmpType = (*cmpTypeSetIter);
    CCmpIDtoCmpMap &cmpMap = mDB->mMap_ObjID_to_Cmp[cmpType];
    CCmpIDtoCmpMap::iterator cmpMapIter = cmpMap.find(oId);
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
  const char * name = node->ToElement()->Attribute("name");
  CLog::Get()->Write( LOG_GENERAL, "Creating component %s", name);

  CHash cmpNameHash = CHash(name);
  // Get the component type from the node
  EComponentTypeId cTypeId = GetComponentTypeFromHash(cmpNameHash);

  if (cTypeId == CID_INVALID)
  { // Don't know this one
    CLog::Get()->Write( LOG_ERROR, "CID_INVALID given hash of component name %s", name);
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
  std::string objType = node->ToElement()->Attribute("name");
  return CreateObject(node, CHash(objType.c_str()));
}

CObjectIdHash CObjectManager::CreateObject(tinyxml2::XMLNode *node, CObjectIdHash oId)
{
  std::string nodeVal = node->Value();
  std::string objType = node->ToElement()->Attribute("name");
  assert(nodeVal == "object");

  CLog::Get()->Write( LOG_GENERAL, "CreateObject: %s", objType.c_str());

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
    CCmpIDtoCmpMap &cmpMap = mDB->mMap_ObjID_to_Cmp[cmpType];
    CCmpIDtoCmpMap::iterator cmpMapIter = cmpMap.find(oId);
    if (cmpMapIter != cmpMap.end())
    { // We found a component belonging to this object, so the object exists.
      return true;
    }
  }
  return false;
}

bool CObjectManager::AddComponentToDb(CObjectIdHash oId, IComponent *pCmp)
{ // Inserts pComp with the key oId, and returns whether the insert was successful
  if(pCmp)
    return (mDB->mMap_ObjID_to_Cmp[pCmp->GetComponentTypeId()].insert(CCmpIDtoCmpMap::value_type(oId, pCmp))).second;
  else
  {
    CLog::Get()->Write(LOG_ERROR,"No component created, cannot add to Database");
    return false;
  }
}

bool CObjectManager::IsInterfaceImplementedByComponent(EInterfaceId iId, IComponent *pCmp) const
{
  if (mDB->mSet_InterfaceType_to_CmpType[iId].find(pCmp->GetComponentTypeId()) == mDB->mSet_InterfaceType_to_CmpType[iId].end())
  {
    return false;
  }
  return true;
}

void CObjectManager::SubscribeToMessageType(EComponentTypeId ctid, EMessageType mtid)
{
  mDB->mSet_MsgType_to_CmpType[mtid].insert(ctid);
}

void CObjectManager::PostMessage(CObjectIdHash oid, const CComponentMessage &msg)
{
  PostMessage( oid, *const_cast<CComponentMessage *>(&msg));
}

void CObjectManager::PostMessage(CObjectIdHash oid, CComponentMessage &msg)
{
  CLog::Get()->Write( LOG_GENERAL, "PostMessage Type %d", msg.mType);
  std::set<EComponentTypeId>	&cmpSet = mDB->mSet_MsgType_to_CmpType[msg.mType];
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
  CLog::Get()->Write( LOG_GENERAL, "BroadcastMessage Type %d", msg.mType);
  std::set<EComponentTypeId>	&cmpSet = mDB->mSet_MsgType_to_CmpType[msg.mType];
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


bool
  CObjectManager::addCallbackForComponent(CObjectIdHash oId, EInterfaceId cmpInterface, ComponentCallbackToExternal func)
{
  //readability
  std::pair<CObjectIdHash, ComponentCallbackToExternal> map = std::pair<CObjectIdHash, ComponentCallbackToExternal>(oId, func);
  IComponent *component = this->QueryInterface(oId, cmpInterface);

  //add to DB
  mDB->mMapCallbackToObjectWithCmp[cmpInterface].insert(map);
  //check for problems
  if( &((mDB->mMapCallbackToObjectWithCmp[cmpInterface])[oId]) != &func) 
  {
    CLog::Get()->Write( LOG_ERROR, "Error registering callback in database for component"); 
    return false;
  }
  //add to actual component
  component->addExternalCallback(func);
  return true;
}




