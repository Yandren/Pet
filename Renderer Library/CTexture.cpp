#include "CTexture.h"
#include "CLog.h"

SDL_Surface*
CTexture::loadFromString(const char* string)
{
  SDL_Surface * retval;
  if( !(retval = SDL_LoadBMP(string)))
      CLog::Get().Write( LOG_ERROR, "No texture loaded from %s", mPath.c_str()); 
  return retval;
}