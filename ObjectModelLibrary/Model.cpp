#include "Model.h"

bool Model::show(float toDrawX, float toDrawY, SDL_Surface* screen){
	bool brs = false;
	int w = texture->clip_rect.w;
	int h = texture->clip_rect.h;
	SDL_Rect imageSpecs = texture->clip_rect;
	SDL_Rect whereToPlace = {toDrawX, toDrawY, w ,h};
	if((SDL_SetColorKey(texture, SDL_SRCCOLORKEY, SDL_MapRGB(texture->format, 255, 255, 255))) == 0)
	//copy the full source texture
	  if((SDL_BlitSurface(texture, &imageSpecs, screen, &whereToPlace ) == 0) )
	    return true;
	  else
		  return false;
	else
		return false;
}