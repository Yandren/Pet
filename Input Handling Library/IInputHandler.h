#ifndef __IINPUTHANDLER_H
#define __IINPUTHANDLER_H

#include "pal.h"
#include <functional>
#include <queue>
#include <vector>
#include "SInput_t.h"
#include "IInputContext.h"

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


typedef std::function<bool (int32_t, void *)> inputFunctionCallback;

// a wrapper to allow us to store different kinds of function callbacks
/*struct SCallbackSignature
{ 
SCallbackSignature( EHandlerType ty, int sz, void * call) 
: type(ty), size(sz), callback(call) {}
virtual void* getCallback() { return callback;}

EHandlerType type;
int size;
void * callback;

};
*/

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
  virtual bool processInput(GLFWwindow* window, SInput_t * input, std::vector<IInputContext *> contexts) = 0;
  //bool registerCallback(SInput_t *input, int action, const SCallbackSignature func);
  //virtual bool pollInputList(GLFWwindow* window, CTimer * time) = 0;
  virtual bool addActiveInput(SInput_t *input);

  //members
  float mTimeTaken;
  //a queue of inputs we get from callbacks, serviced in order we get them
  static std::queue< SInput_t *> mIncomingInput;

protected:
  //a mapping of the callbacks associated with various keys and states
  //std::map<SInput_t *, std::map<int, SCallbackSignature> > mActionCallbackMap;

  
};

#endif