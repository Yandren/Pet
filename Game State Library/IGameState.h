#ifndef __IGAMESTATE_H
#define __IGAMESTATE_H

#include <string>
#include <map>
#include "IInputContext.h"

/************************************
*
* Structs
*
************************************/


/************************************
*
* Classes
*
************************************/

class IGameState
{

public:
  //constructors/destructors
  IGameState(){}
  virtual ~IGameState(){}

  //methods

  //members
  std::string name;

  protected:

  //methods

  //members
  std::map<std::string, IInputContext *> mInputContexts;
};

#endif