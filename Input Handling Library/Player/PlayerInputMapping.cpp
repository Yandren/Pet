#include "PlayerInputMapping.h"
#include "Component System/CComponentMessage.h"
#include "Component System\ComponentStructs.h"
#include "CObjectManager.h"
#include "Globals.h"
#include "tinyxml2\tinyxml2.h"


//TODO: These should be replaced by "Intents", which would be more generalized than this

CIntentToObjectsMapping::CIntentToObjectsMapping(std::string objName)
{
  mObjName = CHash(objName.c_str());
  /*
  tinyxml2::XMLElement * element = NULL;
      for(element = node.FirstChildElement(); element; element = element->NextSiblingElement()) 
    {

    }
    */
}

bool
CIntentToObjectsMapping::evoke()
{
  if(mIntentName.empty())
    return false;

  CComponentMessage msg = CComponentMessage(MT_KEYBOARD_INPUT);
  msg.mpData = &mIntentName;

  if(mObjName != 0)
    Globals::GetObjectManager()->PostMessage(mObjName, msg);
  else
    Globals::GetObjectManager()->BroadcastMessage(msg);

  return true;
}





  CMouseToObjectsMapping::CMouseToObjectsMapping()
  {


  }

  bool
  CMouseToObjectsMapping::evoke()
  {

    //call the physics, send out a message to stuff we've hit.

    return false;
  }

