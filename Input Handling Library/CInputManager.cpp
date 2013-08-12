#include "CInputManager.h"
#include "Globals.h"
#include "CPlayerInputHandler.h"
#include "CObjectManager.h"
#include "CGameStateManager.h"
#include "glfw\include\GLFW\glfw3.h"
#include <queue>
#include "tinyxml2\tinyxml2.h"



bool 
  CInputManager::Init( GLFWwindow * window, std::string fileName /*IConfig * config*/)
{
  //used for inserting into maps
  typedef std::pair<EInputType, IInputHandler *> handlerInit;

  //Load up our input config file
  tinyxml2::XMLError err = tinyxml2::XML_NO_ERROR;
  CLog::Get()->Write( LOG_GENERAL, "Loading input from config");
  tinyxml2::XMLDocument doc;
  if( Utilities::pathExists(fileName.c_str()))
    err = doc.LoadFile(fileName.c_str());

  if(doc.Error() || err != tinyxml2::XML_NO_ERROR)
  {
   CLog::Get()->Write( LOG_ERROR, "Can't load input config from XML doc");
    return false;
    }
  //cycle through the kinds of input we're configuring
 
  //travel the nodes, find input handler nodes
  tinyxml2::XMLNode *playerInput = doc.FirstChildElement("inputconfig")->FirstChildElement("playerInput");
  tinyxml2::XMLNode *networkInput = doc.FirstChildElement("inputconfig")->FirstChildElement("networkInput");

  //load our player input (from config, too)
  IInputHandler * temp = new CPlayerInputHandler(window);
  temp->init(playerInput, Globals::GetGameStateManager() );
  //assign our handler for what kind of input
  mInputHandlers.insert( handlerInit(INPUT_PLAYER_KEY, temp));
  mInputHandlers.insert( handlerInit(INPUT_PLAYER_MOUSE, temp));


  //float currentTick = Globals::GetTimer()->get_ticks();

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
  int inputQueueSize = mInputHandlers[INPUT_GENERIC]->mIncomingInput.size();
  std::queue< SInput_t *> * input = &mInputHandlers[INPUT_GENERIC]->mIncomingInput;

  //Get the valid input contexts from the game state  
  IGameState * state = Globals::GetGameStateManager()->getCurrentState();
  std::vector<IInputContext *> contexts = state->flattenContexts();

  //cycle through input queue and give each to correct handler
  for(int i = 0; i < inputQueueSize; i++)
  {
    //give the handler of the correct type its input
    mInputHandlers[input->front()->type]->processInput(window, input->front(), contexts);
    input->pop();
  }


  return true;
}