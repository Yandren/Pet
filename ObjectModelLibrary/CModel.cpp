#include "CModel.h"

bool CModel::show(float toDrawX, float toDrawY, SDL_Surface* screen){
	bool brs = false;
	int w = m_texture->clip_rect.w;
	int h = m_texture->clip_rect.h;
	SDL_Rect imageSpecs = m_texture->clip_rect;
	SDL_Rect whereToPlace = {toDrawX, toDrawY, w ,h};
	if((SDL_SetColorKey(m_texture, SDL_SRCCOLORKEY, SDL_MapRGB(m_texture->format, 255, 255, 255))) == 0)
	//copy the full source texture
	  if((SDL_BlitSurface(m_texture, &imageSpecs, screen, &whereToPlace ) == 0) )
	    return true;
	  else
		  return false;
	else
		return false;
}