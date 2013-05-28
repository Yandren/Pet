
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "pal.h"
#include <vector>
#include "Component System/IComponent.h"

enum GameState { Uninitialized, Splash, Paused, Menu, Playing, Exiting, Loading };

class CGameStateManager {

	// GameState handles any menu systems that we need, pausing, etc.
public:

  void update();

  CGameStateManager(){ gameStates.push_back(Uninitialized); }
  ~CGameStateManager(){}
  
  bool Init();
  void Shutdown();
  static void handle_input(int key, int action);

  //gets the current gamestate without altering the stack
  GameState getCurrentState() {return gameStates.back();}
  //pops the gamestate off the top of the stack
  GameState popState(){
    GameState retval = gameStates.front(); gameStates.pop_back(); return retval; }
  void pushState(GameState state) { gameStates.push_back(state);}

private:
  std::vector<GameState> gameStates;

};

#endif