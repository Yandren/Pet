
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "pal.h"
#include "IObject.h"
#include "ComponentSystem/IComponent.h"

class CGameStateManager {

public:
  int **gameMap; //double array
  bool rowFull;
  int score;


  void update();

  CGameStateManager(){}
  ~CGameStateManager(){}
  
  bool Init();
  void Shutdown();
  void handle_input(SDL_Event *event);

  std::vector<IObject*> userObjects;

  class UserControl {
  public:
    void handle_input(SDL_Event *event);
	void add_user_object(IObject *object);
	void remove_user_object(IObject *object);
	void update();

	std::vector<IObject*> * userObj;

  };
private:


};

#endif