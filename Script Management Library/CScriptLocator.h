#ifndef __CSCRIPTLOCATOR_H
#define __CSCRIPTLOCATOR_H

#include <map>
#include <string>

class Callable_t
{
  public:
  //Constructors/Destructors
                Callable_t(std::string nm) : nameToken(nm){}
  virtual       ~Callable_t(){}

  //Methods
  virtual bool  call() = 0;
  //Members
  std::string nameToken;
};

class CScriptLocator
{
public:
  //Constructors/destructors
  ~CScriptLocator() {DeInit();}
  //Methods
  bool                      Init();
  bool                      DeInit();

  bool                      registerScript(Callable_t * call);
    //overloads of registerScript for ease of not making a Callable_t
  bool                      registerScript(std::string path);

  bool                      tokenRegistered(std::string nm);
  static CScriptLocator *   getInstance()
   { static CScriptLocator * scriptMan = new CScriptLocator(); return scriptMan;}
  //Members

private:
  //Constructor - Singleton
  CScriptLocator(){}
  //Methods
  //Members
  std::map<std::string, Callable_t *> mScriptRegistry;
};


#endif