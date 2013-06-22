#ifndef __CPLAYERINPUTHANDLER_H
#define __CPLAYERINPUTHANDLER_H

#include "IInputHandler.h"
#include <map>
#include <string>


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
//function callback to store for when a key is pressed
typedef std::function<void ( CHash, CComponentMessage &)> playerInputCallback;


/************************************
*
* Structs
*
* Our internal representation of a key, 
* including how we map it to an int value.
*
*************************************/
struct SKeyboardKey_t : public SInput_t
{
   SKeyboardKey_t(std::string k) : SInput_t(k){}
   SKeyboardKey_t(const char * k) : SInput_t(k){}

   virtual int getValue(){return valuesToCharacters.at(identifier.c_str());}

   const static std::map<const char *, int> valuesToCharacters;
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
  CPlayerInputHandler(){ };
  virtual ~CPlayerInputHandler(){};

  //methods
  bool processInput(GLFWwindow* window, CTimer * time);
  bool configureKeys(/*IConfig * config*/);

   //this will be called from configureKeys in the future and will be a private method
  bool executeCallbackForKey(GLFWwindow* window, SKeyboardKey_t* key);
  bool pollInputList(GLFWwindow* window, CTimer * time);

  //members

  private:
  //methods
 
  //members

};
#endif