#ifndef __SINPUTTYPE_H
#define __SINPUTTYPE_H

#include <string>
/************************************
*
* Forward Declarations
*
*************************************/

/************************************
*
* Structs and Enums
*
*************************************/

//the different types of Input we can have
const enum EInputType 
{
  INPUT_GENERIC = 0,
  INPUT_PLAYER_KEY,
  INPUT_PLAYER_MOUSE,
  INPUT_NETWORK,
  INPUT_AI,
  MAX_INPUT_TYPES
};

//an abstract internal representation of an "input"
struct SInput_t
{
  SInput_t(){}
  SInput_t(const char * c);
  SInput_t(std::string s);
  virtual ~SInput_t(){}

  virtual int getValue();
  virtual const char * getIdentifier();

  float state;
  EInputType type;
  std::string identifier;

};

#endif