#ifndef __GLOBALS_H
#define __GLOBALS_H

class CObjectManager;
class CPhysicsManager;
class CTimer;
class CGameStateManager;
class CVideoManager;
class CInputManager;
class CScriptManager;

namespace Globals
{
  //TODO replace these with a proper cfg file later
  static const char * OBJECTS_XML_FILE = "C:/Users/dragonerdriftr/Documents/Pet/objects.xml";
  static const char * BASE_DIR = "C:/Users/dragonerdriftr/Documents/Pet/";


  CObjectManager*	   GetObjectManager();
  CGameStateManager* GetGameStateManager();
  CTimer*			       GetTimer();
  CPhysicsManager*   GetPhysicsManager();
  CVideoManager*     GetVideoManager();
  CInputManager*     GetInputManager();
  CScriptManager*    GetScriptManager();

};

#endif