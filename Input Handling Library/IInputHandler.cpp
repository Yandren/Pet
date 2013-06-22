#include "IInputHandler.h"



IInputHandler::~IInputHandler()
{ 
  for (int i = 0; i < mActiveInputs.size(); i++)
  {
    delete mActiveInputs[i];
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
  mActiveInputs.insert(std::pair<int, SInput_t *> (input->getValue(), input));
  if(mActiveInputs.at(input->getValue()) != input)
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