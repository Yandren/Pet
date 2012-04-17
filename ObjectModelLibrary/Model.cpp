#include "Model.h"

bool Model::show(float toDrawX, float toDrawY, SDL_Surface* screen){
	bool brs = false;
	int w = texture->clip_rect.w;
	int h = texture->clip_rect.h;
	SDL_Rect imageSpecs = texture->clip_rect;
	SDL_Rect whereToPlace = {1, 1, w ,h};
	brs = SDL_BlitSurface(texture, &imageSpecs, screen, &whereToPlace ); 
	return brs;
}