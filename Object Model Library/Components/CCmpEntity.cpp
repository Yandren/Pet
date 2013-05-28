#include "CCmpEntity.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"


CCmpEntity::CCmpEntity()
{
}

CCmpEntity::~CCmpEntity()
{
}

void CCmpEntity::RegisterComponentType()
{
  ICmpEntity::RegisterInterface(CID_ENTITY);
  Globals::GetObjectManager().RegisterComponentType(CID_ENTITY, CCmpEntity::CreateMe, CCmpEntity::DestroyMe, CHash("Entity"));
  Globals::GetObjectManager().SubscribeToMessageType(CID_ENTITY, MT_OBJECT_CREATED);
  Globals::GetObjectManager().SubscribeToMessageType(CID_ENTITY, MT_POSITION_REQ);
  Globals::GetObjectManager().SubscribeToMessageType(CID_ENTITY, MT_POSITION_REQ_LOCAL);
  Globals::GetObjectManager().SubscribeToMessageType(CID_ENTITY, MT_HIDE);
  Globals::GetObjectManager().SubscribeToMessageType(CID_ENTITY, MT_SHOW);
}

IComponent *CCmpEntity::CreateMe()
{
  return new CCmpEntity;
}

bool CCmpEntity::DestroyMe(IComponent *pComponent)
{
  delete pComponent;
  return true;
}

// Virtual IComponent methods
bool CCmpEntity::Init(CObjectIdHash oid, tinyxml2::XMLNode &node)
{
  // Get XML info
  try
  {
    tinyxml2::XMLElement * element = NULL;
    for(element = node.FirstChild()->ToElement(); element; element = element->NextSiblingElement()) {
      std::string name = element->Name();
      if(name == "bool")
      {
        std::string nameAttrib = element->Attribute("name");
        if(nameAttrib == "interact")
          mCanInteract = element->Value();
      }
      if(name == "position")
      { 

        for(tinyxml2::XMLElement *posRoot = element->FirstChildElement("float"); posRoot; posRoot = posRoot->NextSiblingElement())
        {
          std::string nameAttr = posRoot->Attribute("name");
          
          if(nameAttr == "X")
            mPosition.x = atof(posRoot->FirstChild()->ToText()->Value());
          else if(nameAttr == "Y")
            mPosition.y = atof(posRoot->FirstChild()->ToText()->Value());
          else if(nameAttr == "Z")
            mPosition.z = atof(posRoot->FirstChild()->ToText()->Value());
          else
            CLog::Get().Write(LOG_ERROR, "Unable to parse XML for CCmpEntity to get position %s", nameAttr.c_str());
         
        }
      }         
    }
  }
  catch(std::exception e)
  {
    CLog::Get().Write( LOG_ERROR, "Unable to parse XML for CCmpEntity Init! %s", e.what());
    return false;
  }
  return true;
}

void CCmpEntity::Deinit(void)
{

}

EMessageResult CCmpEntity::HandleMessage(const CComponentMessage &msg)
{
  switch (msg.mType)
  {
  case MT_OBJECT_CREATED:
    {
      return MR_TRUE;
    }
  case MT_POSITION_REQ_LOCAL:
    { 

      SPositionInfo pos = SPositionInfo(GetPosition().x, GetPosition().y, GetPosition().z, 1.0 ); 
      Globals::GetObjectManager().PostMessage(this->GetObjectId(), CComponentMessage(MT_POSITION, &pos));
      return MR_TRUE;
    }
  case MT_POSITION_REQ:
    { 
      SPositionInfo pos = SPositionInfo(GetPosition().x, GetPosition().y, GetPosition().z, 1.0 ); 
      Globals::GetObjectManager().BroadcastMessage(CComponentMessage(MT_POSITION, &pos));
      return MR_TRUE;
    }
  case MT_HIDE:
    {
      SetInteract(false);
      return MR_TRUE;
    }
  case MT_SHOW:
    {
      SetInteract(true);
      return MR_TRUE;
    }
  }
  return MR_IGNORED;
}

EComponentTypeId CCmpEntity::GetComponentTypeId(void)
{
  return CID_ENTITY;
}


bool CCmpEntity::CanThisObjectBeSeenBy(CObjectIdHash viewer, bool includeInventoryObject) const
{
  /* ICmpCollectable *pCollectable = static_cast<ICmpCollectable *>(Globals::GetObjectManager().QueryInterface(GetObjectId(), IID_COLLECTABLE));
  if (pCollectable == NULL || !pCollectable->IsCollected())
  { // The object is not collectable or it is collectable but not collected. Check if it's in the same room as the viewer.
  if (GetInteract() == false)
  return false; // Can't be seen by anyone

  ICmpEntity *pViewerEntity = static_cast<ICmpEntity *>(Globals::GetObjectManager().QueryInterface(viewer, IID_ENTITY));
  if (pViewerEntity == NULL)
  {
  return false;
  } 
  if (GetPosition() == pViewerEntity->GetPosition())
  {
  return true;
  }
  }
  if (pCollectable && pCollectable->IsCollected())
  {
  if (pCollectable->GetHolder() == viewer)
  { // This object is collected by the viewer. We're fine
  return includeInventoryObject;
  }
  } */
  return false;
}


