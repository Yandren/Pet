#include "CCmpRenderable.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"


CCmpRenderable::CCmpRenderable()
{
}

CCmpRenderable::~CCmpRenderable()
{
}

void CCmpRenderable::RegisterComponentType()
{
	ICmpRenderable::RegisterInterface(CID_RENDERABLE);
	Globals::GetObjectManager().RegisterComponentType(CID_RENDERABLE, CCmpRenderable::CreateMe, CCmpRenderable::DestroyMe, CHash("Renderable"));
	Globals::GetObjectManager().SubscribeToMessageType(CID_RENDERABLE, MT_OBJECT_CREATED);

}

IComponent *CCmpRenderable::CreateMe()
{
	return new CCmpRenderable;
}

bool CCmpRenderable::DestroyMe(IComponent *pComponent)
{
	delete pComponent;
	return true;
}

// Virtual IComponent methods
bool CCmpRenderable::Init(CObjectIdHash oid, tinyxml2::XMLNode &node)
{


	return true;
}

void CCmpRenderable::Deinit(void)
{

}

EMessageResult CCmpRenderable::HandleMessage(const CComponentMessage &msg)
{
	switch (msg.mType)
	{
		case MT_OBJECT_CREATED:
		{

		}
		case MT_RENDER:
		{
			SRenderableInfo *info = static_cast<SRenderableInfo*>(msg.mpData);
			m_model->show( info->x_pos, info->y_pos, m_surface);
		}

	}
	return MR_IGNORED;
}

EComponentTypeId CCmpRenderable::GetComponentTypeId(void)
{
	return CID_RENDERABLE;
}



