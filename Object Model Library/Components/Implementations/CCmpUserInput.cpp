#include "CCmpUserInput.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"
#include "CInputManager.h"
#include "Player/CPlayerInputHandler.h"
#include "Player/PlayerInput_types.h"
#include <map>
#include <functional>

void 
  CCmpUserInput::RegisterComponentType()
{
  ICmpInput::RegisterInterface(CID_INPUT);
  Globals::GetObjectManager()->RegisterComponentType(CID_INPUT, std::bind(&CCmpUserInput::CreateMe), std::bind(&CCmpUserInput::DestroyMe, std::placeholders::_1), CHash("UserInput"));
  Globals::GetObjectManager()->SubscribeToMessageType(CID_INPUT, MT_OBJECT_CREATED);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_INPUT, MT_KEYBOARD_INPUT);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_INPUT, MT_MOUSE_INPUT);
}


IComponent *
  CCmpUserInput::CreateMe()
{
  return new CCmpUserInput;
}

bool 
  CCmpUserInput::DestroyMe(IComponent *pComponent)
{
  delete pComponent;
  return true;
}

bool 
  CCmpUserInput::Init(CObjectIdHash oid, tinyxml2::XMLNode &node)
{
  //register keys->broadcast messages, based on XML file
  //Globals::GetInputManager()->playerInputHandler->registerCallback(
  //Globals::GetObjectManager()->BroadcastMessage
  CLog::Get()->Write(LOG_GENERAL,"TODO! Write a configurable keyboard thing in CCmpUserInput");

    // Get XML info
  try
  {
    tinyxml2::XMLElement * element = NULL;
    for(element = node.FirstChildElement(); element; element = element->NextSiblingElement()) 
    {
      std::string name = element->Name();
      if(name == "key")
      {
        //map the characters we'll load up from our XML to in-game constants
        IInputHandler * inputHandler = Globals::GetInputManager()->mInputHandlers[INPUT_PLAYER_KEY];

        SInput_t * key = new SKeyboardKey_t(element->Attribute("name"));
        int state = 0;
        if(element->Attribute("state") != NULL)
          state = atoi(element->Attribute("state"));
        
        CLog::Get()->Write(LOG_GENERAL,"working on input for %s", key->getIdentifier());
        
        CLog::Get()->Write(LOG_ERROR,"TODO! Writing the init for certain common actions");

        //TODO: write more generalized code to allow for customization.
        // currently, you define key mappings here in objects - ideally
        // you'd define them in one config to a generalized "Intent" (i.e. "hero action 1")
        // which is then mapped to the object, but I just want to get this working for now






        //THIS is where we register some script handle with our input handling
        //TODO:
        //create a scriptComponent
        //  -> scriptManager will get script filename from XML, return a handle/register a message/give a callback

      } //end if - name == key

    } //end for
  } // end try block
  catch(std::exception e)
  {
    CLog::Get()->Write( LOG_ERROR, "Unable to parse XML for CCmpEntity Init! %s", e.what());
    return false;
  }//end catch
  return true;
}

void 
  CCmpUserInput::Deinit(void)
{

}

EMessageResult 
  CCmpUserInput::HandleMessage(const CComponentMessage &msg)
{
  CLog::Get()->Write( LOG_GENERAL, "Handling message to User Input component");
  switch (msg.mType)
  {
  case MT_OBJECT_CREATED:
    {

    }

  }
  return MR_IGNORED;
}

EComponentTypeId 
  CCmpUserInput::GetComponentTypeId(void)
{
  return CID_INPUT;
}
