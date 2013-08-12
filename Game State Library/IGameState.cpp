#include "IGameState.h"

IGameState::~IGameState()
{
  
  std::map<std::string, IInputContext*>::iterator it;
  for(it = mInputContexts.begin(); it != mInputContexts.end(); it++)
  {
    delete it->second;
  }
}

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

bool
  IGameState::inputContextExists(std::string name)
{
  return mInputContexts.find(name) != mInputContexts.end(); 
}

void
  IGameState::addGenericInputContext(std::string name)
{
  IInputContext * context = new IInputContext();
  context->name = name;
  mInputContexts.insert(std::pair<std::string, IInputContext *>(name, context));

}

