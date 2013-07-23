#ifndef __IINPUTCONTEXT_H
#define __IINPUTCONTEXT_H

#include "IInputMapping.h"
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
  ~IInputContext(){}

  //methods
  bool containsKey(SInput_t * in) { if( mInputMappings.find(in) != mInputMappings.end()) return true; else return false;}
  //members
  std::string name;
  std::map< SInput_t *, IInputMapping *> mInputMappings;
private:

  //methods

  //members


}; //end of class IInputContext

#endif