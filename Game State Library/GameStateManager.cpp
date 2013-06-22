#include "GameStateManager.h"
#include "Globals.h"
#include "glew\include\GL\glew.h"
#include "glfw\include\GLFW\glfw3.h"
#include "Video.h"
#include "CTimer.h"

CGameStateManager::CGameStateManager()
{
  gameStates.push_back(Uninitialized);
}

void CGameStateManager::update()
{
  CLog::Get()->Write( LOG_GENERAL, "Updating gamestate");
};

bool CGameStateManager::Init()
{
  gameStates.push_back(Loading);
  return true;
};

void CGameStateManager::DeInit()
{


};


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