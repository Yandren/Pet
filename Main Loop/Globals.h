#ifndef __GLOBALS_H
#define __GLOBALS_H



class CObjectManager;
class CPhysicsManager;
class CTimer;
class CGameStateManager;
class CVideoManager;


namespace Globals
{
  //TODO replace these with a proper cfg file later
	static const char * OBJECTS_XML_FILE = "C:/Users/dragonerdriftr/Documents/Pet/objects.xml";
	static const char * BASE_DIR = "C:/Users/dragonerdriftr/Documents/Pet/";
	
	CObjectManager	  &GetObjectManager();
	CGameStateManager &GetGameStateManager();
	CTimer			  &GetCTimer();
    CPhysicsManager   &GetPhysicsManager();
    CVideoManager     &GetVideoManager();
}

#endif