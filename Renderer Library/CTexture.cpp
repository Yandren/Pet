#include "CTexture.h"
#include "CLog.h"
#include "glew\include\GL\glew.h"
#include "glfw\include\GLFW\glfw3.h"


bool
  CTexture::loadFromDisk(const char* path)
{
  /*
  if( GL_FALSE == glfwReadImage(path, &mImageRaw, GLFW_ORIGIN_UL_BIT))
  {
    CLog::Get()->Write( LOG_ERROR, "No texture loaded from %s", mPath.c_str()); 
    return false;
  }
  return true;
  */
  CLog::Get()->Write( LOG_ERROR, "texture load TBI");
  return false;
}