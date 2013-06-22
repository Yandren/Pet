#ifndef __INPUTMANAGER_H
#define __INPUTMANAGER_H

#include "IInputHandler.h"

class CObjectManager;

class CInputManager
{
  public:
   //Constructors/Destructors
   CInputManager(){};
   ~CInputManager(){};
   //methods
   bool Init(CObjectManager * objMan/*IConfig * config*/);
   bool DeInit();

   //members
   IInputHandler * mPlayerInputHandler;

   private:
   

};
#endif