#include "GameStateManager.h"


void CGameStateManager::update()
{
	CLog::Get().Write( LOG_GENERAL, "Updating gamestate");
};



 void CGameStateManager::handle_input(int key, int action)
{	
		CLog::Get().Write( LOG_GENERAL, "Gamestate handling input; key %d action: %d", key, action);
};

bool CGameStateManager::Init()
{
  gameStates.push_back(Loading);
	return true;
};

void CGameStateManager::Shutdown()
{


};