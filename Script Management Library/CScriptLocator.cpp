#include "CScriptLocator.h"
#include "pal.h"

bool
  CScriptLocator::Init()
{


  return true;
}

bool
  CScriptLocator::DeInit()
{


  return true;
}

bool
  CScriptLocator::registerScript(Callable_t * call)
{

  std::pair<std::string, Callable_t *> err;
  mScriptRegistry.insert(std::pair<std::string, Callable_t *>(call->nameToken, call));
  //if(err.second == NULL)
  //{
   // CLog::Get()->Write( LOG_ERROR, "Script isn't registered");
   // return false;
  //}
  return true;
}

bool
  CScriptLocator::registerScript(std::string path)
{

  CLog::Get()->Write( LOG_GENERAL, "registerScript via a path TBI!");
  return false;
}

bool
  CScriptLocator::tokenRegistered(std::string nm)
{
  std::map<std::string, Callable_t *>::iterator iter;
  iter = mScriptRegistry.find(nm);
  if(iter == mScriptRegistry.end())
  {
    CLog::Get()->Write( LOG_GENERAL, "Script isn't registered");
    return false;
  }

  return true;
}