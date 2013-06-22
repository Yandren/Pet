#ifndef __IINPUTHANDLER_H
#define __IINPUTHANDLER_H

#include "pal.h"
#include <functional>
#include <map>
#include <vector>
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
//enum declaring the different types of callbacks we can store
const enum ECallbackType 
{
  GENERIC = 0,
  PLAYER,
  NETWORK,
  AI
};


typedef std::function<bool (int32_t, void *)> inputFunctionCallback;

// a wrapper to allow us to store different kinds of function callbacks
struct SCallbackSignature
{ 
  SCallbackSignature( ECallbackType ty, int sz, void * call) 
    : type(ty), size(sz), callback(call) {}
  virtual void* getCallback() { return callback;}

  ECallbackType type;
  int size;
  void * callback;

};


/************************************
*
* Structs
*
*************************************/

//an abstract internal representation of an "input"
struct SInput_t
{
  SInput_t(std::string s){identifier.assign(s);}
  SInput_t(char * c){identifier.assign(c);}

  virtual int getValue(){ return (int)identifier.c_str();}
  virtual const char * getIdentifier(){return identifier.c_str();}

  std::string identifier;
  float state;
};


/************************************
*
* Classes
*
*************************************/

class IInputHandler
{
public:

  //Constructors/Destructors
  IInputHandler(){};
  virtual ~IInputHandler();
  //methods
  virtual bool processInput(GLFWwindow* window, CTimer * time) = 0;
  //bool registerCallback(SInput_t *input, int action, const SCallbackSignature func);
  virtual bool pollInputList(GLFWwindow* window, CTimer * time) = 0;
  virtual bool addActiveInput(SInput_t *input);

  //members
  float mTimeTaken;

protected:
  //a mapping of the callbacks associated with various keys and states
  std::map<SInput_t *, std::map<int, SCallbackSignature> > mActionCallbackMap;

  //for polling, an array of keys to check for, arranged by "InputValue" order for quick lookups
  //NOTE: The memory for these is handled internally,
  // but they must be created outside the class.
  std::map< int, SInput_t *> mActiveInputs;

};

#endif