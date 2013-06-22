#include "CCmpRenderable.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"
#include "Video.h"
#include "glew\include\GL\glew.h"



CCmpRenderable::CCmpRenderable()
{
}

CCmpRenderable::~CCmpRenderable()
{
}

void CCmpRenderable::RegisterComponentType()
{
  ICmpRenderable::RegisterInterface(CID_RENDERABLE);
  Globals::GetObjectManager()->RegisterComponentType(CID_RENDERABLE, std::bind(&CCmpRenderable::CreateMe), std::bind(&CCmpRenderable::DestroyMe, std::placeholders::_1), CHash("Renderable"));
  Globals::GetObjectManager()->SubscribeToMessageType(CID_RENDERABLE, MT_OBJECT_CREATED);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_RENDERABLE, MT_INIT_RENDER);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_RENDERABLE, MT_RENDER);
  Globals::GetObjectManager()->SubscribeToMessageType(CID_RENDERABLE, MT_SPACIAL);
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
  // Get XML info
  try
  {
    tinyxml2::XMLElement * element = NULL;
    for(element = node.FirstChild()->ToElement(); element; element = element->NextSiblingElement())
     {
      std::string name = element->Name();
      if(name == "path")
      {
        std::string nameAttrib = element->Attribute("name");
        if(nameAttrib == "model")
          this->createModel(element->FirstChild()->ToText()->Value());
      }//end if - name == path
    }//end for loop through nodes
  }//end try block
  catch(std::exception e)
  {
    CLog::Get()->Write( LOG_ERROR, "Unable to parse XML for CCmpRenderable Init! %s", e.what());
    return false;
  }
  return true;
}

void CCmpRenderable::Deinit(void)
{

}

EMessageResult CCmpRenderable::HandleMessage(const CComponentMessage &msg)
{
  EMessageResult retval = MR_IGNORED;
  CLog::Get()->Write( LOG_GENERAL, "Handling message to Renderable!");
  switch (msg.mType)
  {
  case MT_OBJECT_CREATED:
    {
      return retval;
    }
  case MT_INIT_RENDER:
    {
      CLog::Get()->Write( LOG_GENERAL, "Initialize Rendering, request info");
      mSpacialReq = true;

      CComponentMessage positionReq = CComponentMessage(MT_SPACIAL_REQ_LOCAL);
      //post a message to THIS object, asking for position
      Globals::GetObjectManager()->PostMessage(this->GetObjectId(), positionReq); 
      //listen in on positioning information broadcasts
      retval = MR_TRUE;
      return retval;
    }
  case MT_RENDER:
    {
      //real deal, time to show how pretty we are
      CVideoManager * vidMan = Globals::GetVideoManager();
      if(mSpacialInfo.mPosition.length() > 0 &&
         mSpacialInfo.mDirection.length() > 0 &&
         mSpacialInfo.mOrientation.length() > 0)
      {
        if(m_model->show( &mSpacialInfo.mPosition, &mSpacialInfo.mDirection, &mSpacialInfo.mOrientation, vidMan ))
        {
          retval = MR_TRUE;
          }
        else
        {
          CLog::Get()->Write( LOG_ERROR, "Not rendering! :( ");
          retval = MR_FALSE;
        }
      }//end if - position isn't null
      else
        CLog::Get()->Write( LOG_ERROR, "no position");
      
      return retval;
    }
  case MT_SPACIAL:
    {
      //if we're supposed to hear it, grab a position and store it, then stop listening
      if(mSpacialReq)
      {
        mSpacialInfo = *(static_cast< SSpacialInfo*>(msg.mpData));
        mSpacialReq = false;
        retval = MR_TRUE;
      }
      return retval;
    }

  }
  return MR_IGNORED;
}

EComponentTypeId CCmpRenderable::GetComponentTypeId(void)
{
  return CID_RENDERABLE;
}



