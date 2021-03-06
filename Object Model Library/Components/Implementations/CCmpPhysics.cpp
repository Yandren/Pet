#include "CCmpPhysics.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"


CCmpPhysics::CCmpPhysics()
{
}

CCmpPhysics::~CCmpPhysics()
{
}

void CCmpPhysics::RegisterComponentType()
{
	ICmpPhysics::RegisterInterface(CID_PHYSICS);
	Globals::GetObjectManager()->RegisterComponentType(CID_PHYSICS, std::bind(&CCmpPhysics::CreateMe), std::bind(&CCmpPhysics::DestroyMe, std::placeholders::_1), CHash("Physics"));
	Globals::GetObjectManager()->SubscribeToMessageType(CID_PHYSICS, MT_OBJECT_CREATED);

}

IComponent *CCmpPhysics::CreateMe()
{
	return new CCmpPhysics;
}

bool CCmpPhysics::DestroyMe(IComponent *pComponent)
{
	delete pComponent;
	return true;
}

// Virtual IComponent methods
bool CCmpPhysics::Init(CObjectIdHash oid, tinyxml2::XMLNode &node)
{


	return true;
}

void CCmpPhysics::Deinit(void)
{

}

EMessageResult CCmpPhysics::HandleMessage(const CComponentMessage &msg)
{
	CLog::Get()->Write( LOG_GENERAL, "Handling message to Physics");
	switch (msg.mType)
	{
		case MT_OBJECT_CREATED:
		{

		}

	}
	return MR_IGNORED;
}

EComponentTypeId CCmpPhysics::GetComponentTypeId(void)
{
	return CID_PHYSICS;
}



