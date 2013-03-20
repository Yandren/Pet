#include "GameState.h"

void CGameStateManager::UserControl::handle_input(SDL_Event *event){

		for(uint32_t i=0; i<userObj->size(); i++)
		  userObj->at(i)->handle_input(event);
};

void CGameStateManager::UserControl::update(){

		for(uint32_t i=0; i<userObj->size(); i++)
		  userObj->at(i)->move();
};

void CGameStateManager::update(){
	((UserControl*)this)->update();
};



void CGameStateManager::handle_input(SDL_Event *event){

		for(uint32_t i=0; i < userObjects.size(); i++)
		  userObjects.at(i)->handle_input(event);
};

bool CGameStateManager::Init(){

	return true;
};

void CGameStateManager::Shutdown(){


};