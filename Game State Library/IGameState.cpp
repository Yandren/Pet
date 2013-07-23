#include "IGameState.h"


std::vector<IInputContext *> 
  IGameState::flattenContexts()
{
  std::vector<IInputContext *> retVec;
  std::map<std::string, IInputContext *>::iterator iter;
  for(iter = mInputContexts.begin(); iter != mInputContexts.end(); iter++)
  {
    retVec.push_back(iter->second);
  }
  return retVec;

}