#include "CGameStateManager.h"
#include "pal.h"
#include "CGenericGameState.h"

CGameStateManager::CGameStateManager()
{ 
  pushState("Uninitialized");
}

void CGameStateManager::update()
{
  CLog::Get()->Write( LOG_GENERAL, "Updating gamestate");
};

bool CGameStateManager::Init()
{
  //mGameStates.push_back(Loading);

  return true;
};

float
  CGameStateManager::setInputTime(float time)
{
  return (mPreviousInputTick = time);
}

float
  CGameStateManager::getPreviousInputTime()
{
  return mPreviousInputTick;
}

void CGameStateManager::DeInit()
{
  for(uint32_t i = 0; i < mCurrentGameStates.size(); i++)
  {
    delete mCurrentGameStates.back();
    mCurrentGameStates.pop_back();
  }
};

void CGameStateManager::pushState(std::string name)
{
  if(encounteredState(name)) //we know that state already!
    mCurrentGameStates.push_back(mEncounteredStates.at(name));
  else
  { //add the previously unknown state in case something wants to add things to it while it's not on the stack
    IGameState *state = new CGenericGameState(name.c_str());
    mEncounteredStates.insert(std::pair<std::string,IGameState*>(name, state));
    mCurrentGameStates.push_back(state);
  }
}

void CGameStateManager::pushState(IGameState * state)
{

  if(encounteredState(state->name))
  {
    if( mEncounteredStates.at(state->name) != state )// Hmm, replace the state (allows for easier replacement of FUBAR'd states)
    {
      mEncounteredStates.at(state->name) = state;
      mCurrentGameStates.push_back(state);
    }
    else //the state is the same as the ones we've seen before
    {
      mCurrentGameStates.push_back(state);
    }
  }
  else //we need to create the state in our mappings in case we want to alter what that state means without it being on the stack
  {
    mEncounteredStates.insert(std::pair<std::string,IGameState*>(state->name, state));  
    mCurrentGameStates.push_back(state);
  }
}

void
CGameStateManager::addEncounteredState(std::string name)
{ //just force add a generic game state
  IGameState * gamestate = new CGenericGameState(name);
  mEncounteredStates.insert(std::pair<std::string, IGameState *>(name, gamestate));
}

IGameState *
  CGameStateManager::popState()
{
  IGameState * retval = mCurrentGameStates.front();
  mCurrentGameStates.pop_back(); 
  return retval;
}
/*
void CGameStateManager::handle_input(int key, int action)
{	
CLog::Get()->Write( LOG_GENERAL, "Gamestate handling input; key %d action: %d", key, action);

if(key == GLFW_KEY_RIGHT ||
key == GLFW_KEY_LEFT  ||
key == GLFW_KEY_UP    ||
key == GLFW_KEY_DOWN )
{
CLog::Get()->Write( LOG_GENERAL, "Arrow keys pressed; camera move!");

float currentTick = Globals::GetTimer()->get_ticks();
Globals::GetVideoManager()->mScene->mCamera->moveCam(key, currentTick - Globals::GetGameStateManager()->getPreviousInputTime() );
Globals::GetGameStateManager()->setInputTime(currentTick);
}
};
*/