#ifndef __GLOBALS_H
#define __GLOBALS_H


class CObjectManager;
class CPhysicsManager;
class CTimer;
class CGameStateManager;
class CVideoManager;

enum ETextType
{
	TTInventoryHeading = 0,
	TTInventoryItem,
	TTExitHeading,
	TTExit,
	TTObjectHeading,
	TTObject,
	TTCharacterHeading,
	TTCharacter,
	TTRoomDesc,
	TTResponse,
	TTStateChange,
	TTShortDesc,
	TTGameOver,
	TTTellRoom,
	TTEvent,
	NUM_TEXT_TYPES,
};

namespace Globals
{
	CObjectManager	  &GetObjectManager();
	CGameStateManager &GetGameStateManager();
	CTimer			  &GetCTimer();
    CPhysicsManager   &GetPhysicsManager();
    CVideoManager     &GetVideoManager();
}

#endif