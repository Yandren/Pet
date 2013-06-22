#include "CCInputManager.h"

#include "Globals.h"
#include "CPlayerInputHandler.h"
#include "CObjectManager.h"

bool 
  CInputManager::Init( CObjectManager * objMan/*IConfig * config*/)
{
  //get this stuff from the config class in the future
  mPlayerInputHandler = new CPlayerInputHandler();
  float currentTick = Globals::GetTimer()->get_ticks();

  if(!mPlayerInputHandler)
    return false;

  return true;
}

bool 
  CInputManager::DeInit()
{
  delete mPlayerInputHandler;
  return true;

}

