#include "CGameStateManager.h"
#include "pal.h"
#include "CGenericGameState.h"

CGameStateManager::CGameStateManager()
{ 
  IGameState *state = new CGenericGameState("Uninitialized");
  mGameStates.push_back(state);
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

void CGameStateManager::DeInit()
{
  for(uint32_t i = 0; i < mGameStates.size(); i++)
  {
    delete mGameStates.back();
    mGameStates.pop_back();
  }

};

void CGameStateManager::pushState(std::string name)
{
  
  IGameState *state = new CGenericGameState(name.c_str());
  mGameStates.push_back(state);
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