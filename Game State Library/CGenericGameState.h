#ifndef __CGENERICGAMESTATE_H
#define __CGENERICGAMESTATE_H

#include <string>
#include "IGameState.h"

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

class CGenericGameState : public IGameState
{

public:
  //constructors/destructors
  CGenericGameState(){}
  CGenericGameState(const char * c){name.assign(c);}
  CGenericGameState(std::string s){name.assign(s);}
  virtual ~CGenericGameState(){}

  //methods

  //members

  protected:

  //methods

  //members

};

#endif