#include "ICmpRenderable.h"
#include "Globals.h"
#include "CObjectManager.h"

void ICmpRenderable::RegisterInterface(EComponentTypeId cmpId)
{
	Globals::GetObjectManager().RegisterInterfaceWithComponent(IID_RENDERABLE, cmpId);
}

bool ICmpRenderable::createModel(string path){

	if(m_model = new CModel(path))
      return true;

	return false;
}