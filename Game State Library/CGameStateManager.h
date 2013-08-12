
#ifndef __GAMESTATE_H
#define __GAMESTATE_H

//#include "pal.h"
#include <vector>
#include <map>
#include "IGameState.h"
#include "Component System/IComponent.h"
#include "IInputContext.h"

//TODO - this should be a factory, making/managing different classes of state
// GameState { Uninitialized, Splash, Paused, Menu, Playing, Exiting, Loading };


class CGameStateManager {

  // GameState handles any menu systems that we need, pausing, etc.
public:
  //Constructors/Destructors
  ~CGameStateManager()
    {DeInit();}

  //Methods
  bool                       Init();
  void                       DeInit();
  static CGameStateManager * getInstance()
    { static CGameStateManager * gameMan = new CGameStateManager(); return gameMan;}

  void         update();
  //static void handle_input(int key, int action);

  //gets the last time that the time on the gamestate was updated
  float        getPreviousInputTime();
  float        setInputTime(float time);
  //gets the current gamestate without altering the stack
  IGameState * getCurrentState() {return mCurrentGameStates.back();}
  //pops the gamestate off the top of the stack
  IGameState * popState();
  void         pushState(IGameState * state);
  //adds a generic state with a name to the stack
  void         pushState(std::string name);
  void         addEncounteredState(std::string name);
  bool         encounteredState(std::string name) { return mEncounteredStates.find(name) != mEncounteredStates.end(); }

  //Members
  std::map<std::string, IGameState *>   mEncounteredStates; //all possible gamestates, different from the stack of states

private:
  //Constructor - singleton
  CGameStateManager();
  //methods
  //members
  std::vector<IGameState *>             mCurrentGameStates;
  
  float                     mPreviousInputTick;

};

#endif