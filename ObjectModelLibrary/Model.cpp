#include "Model.h"

bool Model::show(float toDrawX, float toDrawY, SDL_Surface* screen){
	bool brs = false;
	SDL_Rect imageToShow = {0,0, };
	SDL_Rect whereToPlace = {toDrawX, toDrawY};
	brs = SDL_BlitSurface(texture, &imageToShow, screen, &whereToPlace ); 
	return brs;
}