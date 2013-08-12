#ifndef __GLOBALS_H
#define __GLOBALS_H

class CObjectManager;
class CPhysicsManager;
class CTimer;
class CGameStateManager;
class CVideoManager;
class CInputManager;
class CScriptLocator;

namespace Globals
{
  //TODO replace these with a proper cfg file later
  static const char * OBJECTS_XML_FILE = "C:/Users/dragonerdriftr/Documents/Pet/objects.xml";
  static const char * BASE_DIR = "C:/Users/dragonerdriftr/Documents/Pet/";
  static const char * INPUT_CONFIG_XML_FILE = "C:/Users/dragonerdriftr/Documents/Pet/inputconfig.xml";

  CObjectManager*	   GetObjectManager();
  CGameStateManager* GetGameStateManager();
  CTimer*			       GetTimer();
  CPhysicsManager*   GetPhysicsManager();
  CVideoManager*     GetVideoManager();
  CInputManager*     GetInputManager();
  CScriptLocator*    GetScriptLocator();

};

#endif