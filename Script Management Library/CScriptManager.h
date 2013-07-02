#ifndef __CSCRIPTMANAGER_H
#define __CSCRIPTMANAGER_H


class CScriptManager
{
public:
  //Constructors/destructors
  ~CScriptManager() {DeInit();}
  //Methods
  bool Init();
  bool DeInit();
  static CScriptManager * getInstance()
   { static CScriptManager * scriptMan = new CScriptManager(); return scriptMan;}
  //Members


private:
  //Constructor - Singleton
  CScriptManager(){}
  //Methods
  //Members

};



#endif