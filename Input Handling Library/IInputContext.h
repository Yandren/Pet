#ifndef __IINPUTCONTEXT_H
#define __IINPUTCONTEXT_H

#include <string>
#include <map>
#include "IInputMapping.h"
#include "SInput_t.h"

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

  //members
  std::string name;

private:

  //methods

  //members

  //a mapping of an input (e.g. "S" key) to some sort of state change/action/etc
  std::map< SInput_t, IInputMapping * > mInputMappings;


}; //end of class IInputContext

#endif