#ifndef __INPUTMANAGER_H
#define __INPUTMANAGER_H

#include "IInputHandler.h"
#include <map>

class    CObjectManager;
struct   GLFWwindow;

class CInputManager
{
public:
  //Constructors/Destructors
  ~CInputManager(){DeInit();}
  //methods
  bool        Init(GLFWwindow * window, std::string fileName/*IConfig * config*/);
  bool        DeInit();
  static      CInputManager * getInstance()
   { static CInputManager * inMan = new CInputManager(); return inMan;}

  bool        createInputMapping(SInput_t * input, std::string name);
  bool        processStoredInput(GLFWwindow * window);

  //members
  //map our input handlers to the types of input they handle
  std::map< EInputType, IInputHandler *> mInputHandlers;


private:
  //Constructor - singleton
    CInputManager(){};

};
#endif