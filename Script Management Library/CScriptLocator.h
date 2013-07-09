#ifndef __CSCRIPTLOCATOR_H
#define __CSCRIPTLOCATOR_H


class CScriptLocator
{
public:
  //Constructors/destructors
  ~CScriptLocator() {DeInit();}
  //Methods
  bool Init();
  bool DeInit();
  static CScriptLocator * getInstance()
   { static CScriptLocator * scriptMan = new CScriptLocator(); return scriptMan;}
  //Members


private:
  //Constructor - Singleton
  CScriptLocator(){}
  //Methods
  //Members

};



#endif