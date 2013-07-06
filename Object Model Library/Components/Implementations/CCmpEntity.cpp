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
  Globals::GetObjectManager()->RegisterComponentType(CID_ENTITY, std::bind(&CCmpEntity::CreateMe), std::bind(&CCmpEntity::DestroyMe, std::placeholders::_1), CHash("Entity"));
  Globals::GetObjectManager()->SubscribeToMessageType(CID_ENTITY, MT_OBJECT_CREATED);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_ENTITY, MT_SPACIAL_REQ);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_ENTITY, MT_SPACIAL_REQ_LOCAL);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_ENTITY, MT_HIDE);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_ENTITY, MT_SHOW);
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
    for(element = node.FirstChild()->ToElement(); element; element = element->NextSiblingElement())
    {
      std::string name = element->Name();
      if(name == "bool")
      {
        std::string nameAttrib = element->Attribute("name");
        if(nameAttrib == "interact")
          mCanInteract = element->Value();
      }//end if - name == bool
      if(name == "position")
      { 
        mPosition.w = 1.0f;//a point in space
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
            CLog::Get()->Write(LOG_ERROR, "Unable to parse XML for CCmpEntity to get position %s", nameAttr.c_str());

        }//end for - looking through position elements 
      }//end if - name == position  
      if(name == "orientation")
      { 
        mOrientation.w = 0.0f; //not a point in space
        for(tinyxml2::XMLElement *posRoot = element->FirstChildElement("float"); posRoot; posRoot = posRoot->NextSiblingElement())
        {
          std::string nameAttr = posRoot->Attribute("name");

          if(nameAttr == "X")
            mOrientation.x = atof(posRoot->FirstChild()->ToText()->Value());
          else if(nameAttr == "Y")
            mOrientation.y = atof(posRoot->FirstChild()->ToText()->Value());
          else if(nameAttr == "Z")
            mOrientation.z = atof(posRoot->FirstChild()->ToText()->Value());
          else
            CLog::Get()->Write(LOG_ERROR, "Unable to parse XML for CCmpEntity to get orientation %s", nameAttr.c_str());

        }//end for - looking through orientation elements 
      }//end if - name == position  
      if(name == "direction")
      { 
        mDirection.w = 0.0f; //not a point in space
        for(tinyxml2::XMLElement *posRoot = element->FirstChildElement("float"); posRoot; posRoot = posRoot->NextSiblingElement())
        {
          std::string nameAttr = posRoot->Attribute("name");

          if(nameAttr == "X")
            mDirection.x = atof(posRoot->FirstChild()->ToText()->Value());
          else if(nameAttr == "Y")
            mDirection.y = atof(posRoot->FirstChild()->ToText()->Value());
          else if(nameAttr == "Z")
            mDirection.z = atof(posRoot->FirstChild()->ToText()->Value());
          else
            CLog::Get()->Write(LOG_ERROR, "Unable to parse XML for CCmpEntity to get direction %s", nameAttr.c_str());
        }//end for - looking through direction elements 
      } //end if - name == direction        
    }//end for - loop through nodes
  }//end try block
  catch(std::exception e)
  {
    CLog::Get()->Write( LOG_ERROR, "Unable to parse XML for CCmpEntity Init! %s", e.what());
    return false;
  }//end catch block
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
  case MT_SPACIAL_REQ_LOCAL:
    { 

      SSpacialInfo pos = SSpacialInfo(GetPosition(), GetDirection(), GetOrientation() ); 
      Globals::GetObjectManager()->PostMessage(this->GetObjectId(), CComponentMessage(MT_SPACIAL, &pos));
      return MR_TRUE;
    }
  case MT_SPACIAL_REQ:
    { 
      SSpacialInfo pos = SSpacialInfo(GetPosition(), GetDirection(), GetOrientation() ); 
      Globals::GetObjectManager()->BroadcastMessage(CComponentMessage(MT_SPACIAL, &pos));
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
    case MT_CALLBACK_INFO:
    {
      //something outside wants to know positional information
      
      typedef std::function< bool ( int, SSpacialInfo * ) > callback_t;
      SSpacialInfo sinfo(mPosition, mDirection, mOrientation);
      //we are passed a callback
      callback_t * callback = (callback_t *) msg.mpData;
      //call the callback passed in
      (*callback)(sizeof(sinfo), &sinfo);
      //mExternalCallback(sizeof(SSpacialInfo), &sinfo); 
    }
  }
  return MR_IGNORED;
}

EComponentTypeId CCmpEntity::GetComponentTypeId(void)
{
  return CID_ENTITY;
}

