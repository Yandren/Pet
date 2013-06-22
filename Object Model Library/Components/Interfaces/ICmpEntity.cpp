#include "ICmpEntity.h"
#include "Globals.h"
#include "CObjectManager.h"

void ICmpEntity::RegisterInterface(EComponentTypeId cmpId)
{
	Globals::GetObjectManager()->RegisterInterfaceWithComponent(IID_ENTITY, cmpId);
}