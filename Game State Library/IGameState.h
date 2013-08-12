#ifndef __IGAMESTATE_H
#define __IGAMESTATE_H

#include <string>
#include <map>
#include <vector>
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
  virtual ~IGameState();

  //methods
  std::vector<IInputContext *>   flattenContexts();
  bool                           inputContextExists(std::string name);
  void                           addGenericInputContext(std::string name);
  //members
  std::string name;

  std::map<std::string, IInputContext *> mInputContexts;

  protected:

  //methods

  //members
};

#endif