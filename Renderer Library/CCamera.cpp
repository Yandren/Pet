
/*
#include "CCamera.h"
#include "pal.h"
#include "glm\glm\gtc\matrix_transform.hpp"

CCamera::CCamera()
{ 
  //grab an entity from the object system and 
  // fill out the camera based on it
  mPosition = glm::vec3(4,3,3);
  mUpOrientation = glm::vec3(0,1,0);
  mDirection = glm::vec3(0,0,0);
  mName = "DefaultCam";
  mMoveSpeed = 3.0f;
}

float 
  CCamera::getAspectRatio()
{ 
  if(mViewportHeight && mViewportWidth > 0) 
  {
    if (mViewportHeight < mViewportWidth)
      return (mViewportWidth / mViewportHeight);
    else
      return (mViewportHeight / mViewportWidth);
  } 
  else
    CLog::Get()->Write( LOG_ERROR, "No Viewport Height or Width defined in Camera");

  return 0.0f;
}

glm::mat4
  CCamera::getViewMatrix()
{
  return glm::lookAt( mPosition, mDirection, mUpOrientation);
}

bool 
  CCamera::moveCam(int key, float timeTick)
{
  CLog::Get()->Write( LOG_GENERAL, "Moving camera! Time tick: %f", timeTick);
  
  switch(key)
  {
  case GLFW_KEY_RIGHT:
    CLog::Get()->Write( LOG_GENERAL, "camera position before right: %f", mPosition.x);
    mPosition.x = mPosition.x + timeTick * mMoveSpeed;
    CLog::Get()->Write( LOG_GENERAL, "camera position after right: %f", mPosition.x);
    break;
  case GLFW_KEY_LEFT:
    CLog::Get()->Write( LOG_GENERAL, "camera position before left: %f", mPosition.x);
    mPosition.x = mPosition.x - timeTick * mMoveSpeed;
    CLog::Get()->Write( LOG_GENERAL, "camera position after left: %f", mPosition.x);
    break;
  case GLFW_KEY_UP:
    CLog::Get()->Write( LOG_GENERAL, "camera position before up: %f", mPosition.y);
    mPosition.y = mPosition.y + timeTick * mMoveSpeed;
    CLog::Get()->Write( LOG_GENERAL, "camera position after up: %f", mPosition.y);
    break;
  case GLFW_KEY_DOWN:
    CLog::Get()->Write( LOG_GENERAL, "camera position before down: %f", mPosition.y);
    mPosition.y = mPosition.y - timeTick * mMoveSpeed;
    CLog::Get()->Write( LOG_GENERAL, "camera position after down: %f", mPosition.y);
    break;
  default:
    CLog::Get()->Write( LOG_ERROR, "Can't move cam, weird direction %d", key);
    return false;
  }
  
  return true;
  
}
*/