#include "Globals.h"
#include "Physics.h"
#include "CObjectManager.h"
#include "GameStateManager.h"
#include "CTimer.h"
#include "Video.h"
#include "CInputManager.h"
#include "CScriptLocator.h"

CObjectManager* 
Globals::GetObjectManager()
{ 
	CObjectManager * objMan = CObjectManager::getInstance(); 
	return objMan;
}


CGameStateManager* 
Globals::GetGameStateManager()
{
  CGameStateManager * gState = CGameStateManager::getInstance(); 
	return gState;
}


CTimer* 
Globals::GetTimer()
{ 
	static CTimer time;
	return &time;
}


CPhysicsManager* 
Globals::GetPhysicsManager()
{ 
  CPhysicsManager * phys = CPhysicsManager::getInstance(); 
	return phys;
}


CVideoManager* 
Globals::GetVideoManager()
{ 
  CVideoManager * video = CVideoManager::getInstance(); 
	return video;
}
	

  CInputManager* 
  Globals::GetInputManager()
{ 
  CInputManager * inputMan = CInputManager::getInstance(); 
	return inputMan;
}


  CScriptLocator* 
  Globals::GetScriptLocator()
{ 
  CScriptLocator * scriptMan = CScriptLocator::getInstance(); 
	return scriptMan;
}
