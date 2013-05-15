#include "CCmpRenderable.h"
#include "Globals.h"
#include "CObjectManager.h"
#include "tinyxml2.h"
#include "CComponentMessage.h"
#include "Video.h"
#include <gl\gl.h>



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
  Globals::GetObjectManager().SubscribeToMessageType(CID_RENDERABLE, MT_INIT_RENDER);
  Globals::GetObjectManager().SubscribeToMessageType(CID_RENDERABLE, MT_RENDER);
  Globals::GetObjectManager().SubscribeToMessageType(CID_RENDERABLE, MT_POSITION);
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
    for(element = node.FirstChild()->ToElement(); element; element = element->NextSiblingElement()) {
      std::string name = element->Name();
      if(name == "path")
      {
        std::string nameAttrib = element->Attribute("name");
        if(nameAttrib == "model")
          this->createModel(element->FirstChild()->ToText()->Value());
      }

      /*if(name == "position")
      { 

      for(tinyxml2::XMLElement *posRoot = element->FirstChildElement("float"); posRoot; posRoot = posRoot->NextSiblingElement())
      {
      std::string nameAttr = posRoot->Attribute("name");
      if(nameAttr == "X")
      mPosition.X = atof(posRoot->FirstChild()->ToText()->Value());
      else if(nameAttr == "Y")
      mPosition.Y = atof(posRoot->FirstChild()->ToText()->Value());
      else if(nameAttr == "Z")
      mPosition.Z = atof(posRoot->FirstChild()->ToText()->Value());
      else
      CLog::Get().Write(LOG_ERROR, "Unable to parse XML for CCmpEntity to get position %s", nameAttr.c_str());

      }
      } */         
    }
  }
  catch(std::exception e)
  {
    CLog::Get().Write( LOG_ERROR, "Unable to parse XML for CCmpRenderable Init! %s", e.what());
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
  CLog::Get().Write( LOG_GENERAL, "Handling message to Renderable!");
  switch (msg.mType)
  {
  case MT_OBJECT_CREATED:
    {
      return retval;
    }
  case MT_INIT_RENDER:
    {
      CLog::Get().Write( LOG_GENERAL, "Initialize Rendering, request info");
      mPositionReq = true;
      CComponentMessage positionReq = CComponentMessage(MT_POSITION_REQ_LOCAL);
      //post a message to THIS object, asking for position
      Globals::GetObjectManager().PostMessage(this->GetObjectId(), positionReq); 
      //listen in on positioning information broadcasts
      retval = MR_TRUE;
      return retval;
    }
  case MT_RENDER:
    {
      //real deal, time to show how pretty we are
      m_surface = (Globals::GetVideoManager()).scene->screen;
      Vec3 <float> posVec = Vec3<float>(mPosition.x_pos, mPosition.y_pos, mPosition.z_pos);
      if(m_surface)
        glBindBuffer(GL_ARRAY_BUFFER, Globals::GetVideoManager()).scene->getVertexBuffer());

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        if(m_model->show( &posVec, m_surface))
          retval = MR_TRUE;
        else
        {
          CLog::Get().Write( LOG_ERROR, "Not rendering! :( ");
          retval = MR_FALSE;
        }
      else
        CLog::Get().Write( LOG_ERROR, "no surface to render to");
      return retval;
    }
  case MT_POSITION:
    {
      //if we're supposed to hear it, grab a position and store it, then stop listening
      if(mPositionReq)
      {
        mPosition = *(static_cast< SPositionInfo*>(msg.mpData));
        mPositionReq = false;
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



