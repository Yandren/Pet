
#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "pal.h"
#include <vector>
#include "Component System/IComponent.h"

//TODO - this should be a factory, making/managing different classes of state
enum GameState { Uninitialized, Splash, Paused, Menu, Playing, Exiting, Loading };


class CGameStateManager {

	// GameState handles any menu systems that we need, pausing, etc.
public:

  void update();

  CGameStateManager();
  ~CGameStateManager(){}
  
  bool Init();
  void DeInit();
  //static void handle_input(int key, int action);

  //gets the last time that the time on the gamestate was updated
  float getPreviousInputTime()
       {return mPreviousInputTick;}
  float setInputTime(float time)
    {return (mPreviousInputTick = time);}
  //gets the current gamestate without altering the stack
  GameState getCurrentState() {return gameStates.back();}
  //pops the gamestate off the top of the stack
  GameState popState(){
    GameState retval = gameStates.front(); gameStates.pop_back(); return retval; }
  void pushState(GameState state) { gameStates.push_back(state);}

private:
  std::vector<GameState> gameStates;
  float mPreviousInputTick;
};

#endif