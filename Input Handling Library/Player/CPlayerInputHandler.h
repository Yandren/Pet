#ifndef __CPLAYERINPUTHANDLER_H
#define __CPLAYERINPUTHANDLER_H

#include "IInputHandler.h"
#include <map>
#include <string>
#include <queue>


/************************************
*
* Forward Declarations
*
*************************************/
struct GLFWwindow;

/************************************
*
* Callbacks
*
*************************************/


/************************************
*
* Structs
*
* Our internal representation of a key, 
* including how we map it to an int value.
*
*************************************/
struct SKeyboardKey_t : public SInput_t
{  //expanding on SInput_t from IInputHandler interface
   SKeyboardKey_t(){type = INPUT_PLAYER;}
   SKeyboardKey_t(std::string k) : SInput_t(k){type = INPUT_PLAYER;}
   SKeyboardKey_t(const char * c) : SInput_t(c){type = INPUT_PLAYER;}
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
  float * getPosition(){ return pos;}  
  float pos[2];
};


/************************************
*
* Classes
*
*************************************/

class CPlayerInputHandler : public IInputHandler
{
public:
  //Constructors/Destructors
  CPlayerInputHandler(){}
  CPlayerInputHandler(GLFWwindow* window);
  virtual ~CPlayerInputHandler(){};

  //methods
  bool processInput(GLFWwindow* window, SInput_t * input);
  static void keyboardKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
   //this will be called from configureKeys in the future and will be a private method
  bool executeCallbackForKey(GLFWwindow* window, SKeyboardKey_t* key);
  //bool pollInputList(GLFWwindow* window, CTimer * time);

  //members

  protected:

  private:
  //methods
 
  //members
  GLFWwindow* mWindow; 

};
#endif