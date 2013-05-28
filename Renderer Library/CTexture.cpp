#include "CTexture.h"
#include "CLog.h"


bool
  CTexture::loadFromDisk(const char* string)
{
  if( GL_FALSE == glfwReadImage(string, &mImageRaw, GLFW_ORIGIN_UL_BIT))
  {
    CLog::Get().Write( LOG_ERROR, "No texture loaded from %s", mPath.c_str()); 
    return false;
  }
  return true;
}