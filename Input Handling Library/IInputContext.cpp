#include "IInputContext.h"

IInputContext::~IInputContext()
{
  std::map< SInput_t *, IInputIntent *>::iterator it;
  for(it = mInputIntents.begin(); it != mInputIntents.end(); it++)
  {
    delete it->first;
    delete it->second;
  }

}