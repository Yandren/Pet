#include "CModel.h"

bool CModel::show(Vec3 <float>* position, SDL_Surface* screen){
  int err = 0;
  SDL_Surface * sdlTex = mTexture->getSDL_Surface();
  if(!sdlTex)
  {
    CLog::Get().Write( LOG_ERROR, "No surface from the Texture");
    return false;
  }
  if(!screen)
  {
    CLog::Get().Write( LOG_ERROR, "No screen passed to us");
    return false;
  }

  //Old 2-D style displaying
  /*prep the info we need for an SDL blit
  int w = sdlTex->clip_rect.w;
  int h = sdlTex->clip_rect.h;
  SDL_Rect imageSpecs = sdlTex->clip_rect;
  SDL_Rect whereToPlace = {position->X, position->Y, w ,h};
  //let the blitting begin
  if((err = SDL_SetColorKey(sdlTex, SDL_SRCCOLORKEY, SDL_MapRGB(sdlTex->format, 255, 255, 255))) == 0)
  { //copy the full source texture
    if((err = SDL_BlitSurface(sdlTex, &imageSpecs, screen, &whereToPlace ) == 0) )
      return true;
    else{
      CLog::Get().Write( LOG_ERROR, "BlitSurface didn't return cleanly: %d", err);
      return false;
    }//end else - BlitSurface
  }//end if - setcolorkey
  */


  else
  {
    CLog::Get().Write( LOG_ERROR, "BlitSurface didn't return cleanly: %d", err);
    return false;
  }//end else - setColorKey

}