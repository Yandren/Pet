#ifndef __CSCRIPTLOCATOR_H
#define __CSCRIPTLOCATOR_H

#include <map>
#include <string>

struct Callable_t
{
  

};


class CScriptLocator
{
public:
  //Constructors/destructors
  ~CScriptLocator() {DeInit();}
  //Methods
  bool Init();
  bool DeInit();
  bool registerScript();
  static CScriptLocator * getInstance()
   { static CScriptLocator * scriptMan = new CScriptLocator(); return scriptMan;}
  //Members


private:
  //Constructor - Singleton
  CScriptLocator(){}
  //Methods
  //Members
  std::map<std::string, Callable_t *> scriptRegistry;

};



#endif