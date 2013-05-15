#include "GameStateManager.h"


void CGameStateManager::update()
{
	CLog::Get().Write( LOG_GENERAL, "Updating gamestate");
};



void CGameStateManager::handle_input(SDL_Event *event)
{	
		CLog::Get().Write( LOG_GENERAL, "Gamestate handling input");

};

bool CGameStateManager::Init()
{
  gameStates.push_back(Loading);
	return true;
};

void CGameStateManager::Shutdown()
{


};