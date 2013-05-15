#include "ICmpPhysics.h"
#include "Globals.h"
#include "CObjectManager.h"

void ICmpPhysics::RegisterInterface(EComponentTypeId cmpId)
{
	Globals::GetObjectManager().RegisterInterfaceWithComponent(IID_PHYSICS, cmpId);
}