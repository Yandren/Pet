#include "ICmpInput.h"
#include "Globals.h"
#include "CObjectManager.h"

void ICmpInput::RegisterInterface(EComponentTypeId cmpId)
{
	Globals::GetObjectManager()->RegisterInterfaceWithComponent(IID_INPUT, cmpId);
}