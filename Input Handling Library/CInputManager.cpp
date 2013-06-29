#include "CInputManager.h"
#include "Globals.h"
#include "CPlayerInputHandler.h"
#include "CObjectManager.h"
#include "glfw\include\GLFW\glfw3.h"
#include <queue>



bool 
  CInputManager::Init( GLFWwindow * window/*IConfig * config*/)
{
  //used for inserting into maps
  typedef std::pair<EInputType, IInputHandler *> handlerInit;
  //get this stuff from the config class in the future
  IInputHandler * temp = new CPlayerInputHandler(window);
  mInputHandlers.insert( handlerInit(INPUT_PLAYER, temp));


  float currentTick = Globals::GetTimer()->get_ticks();

  if(mInputHandlers.size() == 0)
    return false;

  return true;
}

bool 
  CInputManager::DeInit()
{
  std::map<EInputType, IInputHandler *>::iterator iter;
  for(iter =  mInputHandlers.begin(); iter != mInputHandlers.end(); iter++)
  {
    delete iter->second;
    mInputHandlers.erase(iter);
  }

  if(mInputHandlers.size() > 0)
    return false;

  return true;
}

bool
CInputManager::processStoredInput(GLFWwindow * window)
{
  //static among handlers, so only one
  int queueSize = mInputHandlers[INPUT_GENERIC]->mIncomingInput.size();
  std::queue< SInput_t *> * input = &mInputHandlers[INPUT_GENERIC]->mIncomingInput;
  //cycle through input queue and give each to correct handler
  for(int i = 0; i < queueSize; i++)
  {
    //give the handler of the correct type its input
    mInputHandlers[input->front()->type]->processInput(window, input->front());
    input->pop();
  }


return true;
}