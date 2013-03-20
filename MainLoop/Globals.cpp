#include "Globals.h"

#include "Physics.h"
#include "CObjectManager.h"
#include "GameState.h"
#include "CTimer.h"
#include "Video.h"

CObjectManager &Globals::GetObjectManager()
{ 
	static CObjectManager objMan; 
	return objMan;
}


CGameStateManager &Globals::GetGameStateManager()
{
	static CGameStateManager gState; 
	return gState;
}


CTimer &Globals::GetCTimer()
{ 
	static CTimer time;
	return time;
}


CPhysicsManager &Globals::GetPhysicsManager()
{ 
	static CPhysicsManager phys;
	return phys;
}


CVideoManager &Globals::GetVideoManager()
{ 
	static CVideoManager video;
	return video;
}
	