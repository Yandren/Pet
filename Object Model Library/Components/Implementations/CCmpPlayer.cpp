#include "CCmpPlayer.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"
#include "string.h"
#include "ICmpEntity.h"
#include <stdio.h>


CCmpPlayer::CCmpPlayer()
{
}

CCmpPlayer::~CCmpPlayer()
{
}

void CCmpPlayer::RegisterComponentType()
{
	ICmpPlayer::RegisterInterface(CID_PLAYER);
	Globals::GetObjectManager()->RegisterComponentType(CID_PLAYER, std::bind(&CCmpPlayer::CreateMe), std::bind(&CCmpPlayer::DestroyMe, std::placeholders::_1), CHash("Player"));
	Globals::GetObjectManager()->SubscribeToMessageType(CID_PLAYER, MT_OBJECT_CREATED);
	Globals::GetObjectManager()->SubscribeToMessageType(CID_PLAYER, MT_ALL_OBJECTS_CREATED);
	Globals::GetObjectManager()->SubscribeToMessageType(CID_PLAYER, MT_COMMAND);
	Globals::GetObjectManager()->SubscribeToMessageType(CID_PLAYER, MT_EVENT);
}

IComponent *CCmpPlayer::CreateMe()
{
	return new CCmpPlayer;
}

bool CCmpPlayer::DestroyMe(IComponent *pComponent)
{
	delete pComponent;
	return true;
}

// Virtual IComponent methods
bool CCmpPlayer::Init(CObjectIdHash oid, tinyxml2::XMLNode &node)
{

	return true;
}

void CCmpPlayer::Deinit(void)
{
}

EMessageResult CCmpPlayer::HandleMessage(const CComponentMessage &msg)
{
	CLog::Get()->Write( LOG_GENERAL, "Handling message to Player!");
	switch (msg.mType)
	{
		case MT_OBJECT_CREATED:
		{
			
			return MR_TRUE;
		}
		case MT_ALL_OBJECTS_CREATED:
		{
			//Globals::GetObjectManager()->PostMessage(GetEntity()->GetPosition(), MT_LOOK);
			return MR_TRUE;
		}
		case MT_COMMAND:
		{
			if (HandleCommand(static_cast<const char *>(msg.mpData)))
			{
				return MR_TRUE;
			}
			return MR_FALSE;
		}
		case MT_EVENT:
		{ // In the real world, this part would live in a script. That seems a bit overkill for this example though.
			EventInfo *pEventInfo = static_cast<EventInfo*>(msg.mpData);
			if (pEventInfo->mEventName == CHash("StateChange") && pEventInfo->mTargetId == CObjectIdHash("Laxative"))
			{
				//Globals::PrintWithType(TTGameOver, "Oh no! The laxative has an explosive effect on your digestive system rending you hostage to your own bowels. You'll be lucky to see the outside of a lavatory for the next two weeks. Alas, there's no way you'll be able to make the GDC now. Your journey ends here.\n");
				//Globals::GetTextAdventureEngine().EndGame();
			}
			else if (pEventInfo->mEventName == CHash("StateChange") && pEventInfo->mTargetId == CObjectIdHash("WaterCooler"))
			{
				
			}
			return MR_TRUE;
		}

	}
	return MR_IGNORED;
}

bool CCmpPlayer::HandleCommand(const char *commandString)
{
	CLog::Get()->Write( LOG_GENERAL, "Handling command sent to player");
	char tmpStr[MAX_STR_LEN];
	strncpy(tmpStr, commandString, MAX_STR_LEN);

	char *pToken = tmpStr; //Globals::GetFirstToken(tmpStr, " ", &pRemainder);
	if (pToken == NULL)
		return false;

	CHash command(pToken);

	if (command == CHash("Enter"))
	{
		/*ICmpRoom *pCurrentRoomInterface = static_cast<ICmpRoom *>(Globals::GetObjectManager()->QueryInterface(GetEntity()->GetPosition(), IID_ROOM));

		if (pCurrentRoomInterface)
		{
			CObjectIdHash destRoom = pCurrentRoomInterface->GetConnectedRoom(pRemainder);
			if (destRoom.IsValid())
			{
				GetEntity()->SetPosition(destRoom);

				EventInfo	evInfo(CHash("EnterRoom"), destRoom, GetObjectId());
				Globals::GetObjectManager()->BroadcastMessage(CComponentMessage(MT_EVENT, &evInfo));

				Globals::GetObjectManager()->PostMessage(GetObjectId(), CComponentMessage(MT_SET_INVENTORY_ITEM_POS, &destRoom));
				Globals::GetObjectManager()->PostMessage(destRoom, MT_LOOK);
			}
			else
			{
				Globals::PrintWithType(TTResponse, "I don't know how to get to %s from here.\n", pRemainder);
			}
			
		}
		return true;
		*/
	}
	printf("Don't know how to: %s\n", commandString);
	return false;
}

EComponentTypeId CCmpPlayer::GetComponentTypeId()
{
	return CID_PLAYER;
}







