#ifndef __IINPUTCONTEXT_H
#define __IINPUTCONTEXT_H

#include "IInputIntent.h"
#include "SInput_t.h"
#include <string>
#include <map>


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
class IInputContext
{

public:
  //constructors/destructors
  IInputContext(){}
  virtual ~IInputContext();

  //methods
  bool containsKey(SInput_t * in) { if( mInputIntents.find(in) != mInputIntents.end()) return true; else return false;}
  //members
  std::string name;
  std::map< SInput_t *, IInputIntent *> mInputIntents;
private:

  //methods

  //members


}; //end of class IInputContext

#endif