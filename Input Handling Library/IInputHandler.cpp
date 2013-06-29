#include "IInputHandler.h"

//initialize our static queue
std::queue< SInput_t *> IInputHandler::mIncomingInput;


IInputHandler::~IInputHandler()
{ 
  for (uint32_t i = 0; i < mIncomingInput.size(); i++)
  {
    delete mIncomingInput.front();
    mIncomingInput.pop();
  }
}

/*
bool
  IInputHandler::registerCallback(SInput_t *input, int action, const SCallbackSignature func)
{
  std::map<int, SCallbackSignature> callback;
  callback[action] = func;
  mActionCallbackMap.at(input)= callback;
  if(mActionCallbackMap.at(input) != callback)
  {
    CLog::Get()->Write(LOG_ERROR, "Error registering callback for key %s, action %d", input->getIdentifier(), action);
    return false;
  }
  return true;
};
*/

bool
  IInputHandler::addActiveInput(SInput_t *input)
{
  mIncomingInput.push(input);
  if(mIncomingInput.back() != input)
  {
    CLog::Get()->Write(LOG_ERROR,"problem adding value %s to polling", input->getIdentifier());
    return false;
  }
  else
  {
    CLog::Get()->Write(LOG_GENERAL,"Adding input to poll %s", input->getIdentifier()); 
    return true;
  }
}