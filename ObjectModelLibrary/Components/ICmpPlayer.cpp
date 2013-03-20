#include "ICmpPlayer.h"
#include "Globals.h"
#include "CObjectManager.h"

void ICmpPlayer::RegisterInterface(EComponentTypeId cmpId)
{
	Globals::GetObjectManager().RegisterInterfaceWithComponent(IID_PLAYER, cmpId);
}