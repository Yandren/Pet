#include "CPlayerInputHandler.h"
#include "glfw\include\GLFW\glfw3.h"
#include "Component System\CComponentMessage.h"
#include "Component System\ComponentStructs.h"
#include "CObjectManager.h"
#include "Globals.h"




bool CPlayerInputHandler::processInput(GLFWwindow* window, CTimer * time)
{
  mTimeTaken = time->get_ticks();

  //update the state of our input signals
  glfwPollEvents();
  mTimeTaken = time->get_ticks();

  //Callback fun! Index into the mappings based on key, then the map there by action to get callback
  for(float i = 0; i < mActiveInputs.size(); i++)
  {
     SKeyboardKey_t * keybrdKey = dynamic_cast<SKeyboardKey_t*>(mActiveInputs.at(i));
    //if there's a callback, do it.
    
    if( keybrdKey != NULL  )//&& executeCallbackForKey(window, keybrdKey))
      CLog::Get()->Write(LOG_GENERAL, "called keyboard input callback");
    else 
    {
      //code here to deal with non-callback related things 
      CLog::Get()->Write(LOG_ERROR, "somehow failed to execute key callback for key %s, action %d", mActiveInputs[i]->getIdentifier(), action);
    }
  }

  return true;
}

bool
  CPlayerInputHandler::executeCallbackForKey(GLFWwindow* window, SKeyboardKey_t* key)
{
  if(glfwGetKey(window, key->getValue()) == key->state)
  {
    CComponentMessage msg(MT_KEYBOARD_INPUT, &key);
    Globals::GetObjectManager()->BroadcastMessage(
    /*
    if(mActionCallbackMap[key][key->state].type != PLAYER)
    {
      //set up the message to be sent
      CComponentMessage msg(MT_KEYBOARD_INPUT, &key);
      mActionCallbackMap[*key][key->state].callback(&msg);
      return true;
    } */
    else
    {
      CLog::Get()->Write(LOG_GENERAL, "Passing on executing callback - %s doesn't have the type we handle %d", key->getIdentifier(), mActionCallbackMap[key][key->state].type);
      return false;
    }
  }
  else
  {
    CLog::Get()->Write(LOG_ERROR, " GetKey() is failing, can't execture callback");
    return false;
  }
}

bool
  CPlayerInputHandler::configureKeys(/*IConfig * config*/)
{
  CLog::Get()->Write(LOG_ERROR, "Configure Keys TBI!");
  return false;
}

bool
  CPlayerInputHandler::pollInputList(GLFWwindow* window, CTimer * time)
{


  //update our state information
  CLog::Get()->Write(LOG_GENERAL,"Polling input list");
  for(float i = 0; i < mActiveInputs.size(); i++)
  {
    mActiveInputs.at(i)->state = glfwGetKey(window, mActiveInputs[i]->getValue());
  }

  return true;
}