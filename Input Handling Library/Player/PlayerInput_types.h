#ifndef __SPLAYERINPUTTYPE_H
#define __SPLAYERINPUTTYPE_H

#include "SInput_t.h"
#include <map>

/************************************
*
* Structs
*
* Our internal representation of a key, 
* including how we map it to an int value,
* and our internal representation of a mouse click.
*
*************************************/

struct SKeyboardKey_t : public SInput_t
{  //expanding on SInput_t from IInputHandler interface
   SKeyboardKey_t(){type = INPUT_PLAYER_KEY;}
   SKeyboardKey_t(std::string k) : SInput_t(k){type = INPUT_PLAYER_KEY;}
   SKeyboardKey_t(const char * c) : SInput_t(c){type = INPUT_PLAYER_KEY;}
   SKeyboardKey_t(int v) { identifier.assign(valuesToCharacters.at(v)); }
   //we have a specific mapping for values to return, overriding SInput_t
   virtual int getValue(){return charactersToValues.at(identifier.c_str());}

   //a static mapping of chars to int values, to match GLFW
   //TODO - get a better data structure in here, eliminate boost
   const static std::map< const char *, int> charactersToValues;
   const static std::map< int, const char *> valuesToCharacters;
};

struct SMouse_t : public SInput_t
{
  SMouse_t(){type = INPUT_PLAYER_MOUSE;}
  SMouse_t(double x, double y, int action, int button) : mAction(action), mButton(button) { type = INPUT_PLAYER_MOUSE; mPos[0] = x; mPos[1] = y;}

  int mButton;
  int mAction;
  double mPos[2];
};

#endif