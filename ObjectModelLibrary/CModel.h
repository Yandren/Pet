#ifndef __CMODEL_H
#define __CMODEL_H

#include "pal.h"
#include <string>
#include <SDL.h>
#include <SDL/SDL_opengl.h>


class CModel {

public:
	CModel(SDL_Surface* tex) //add SDL_SetColorKey color param here for background color to ignore when drawing 
		: m_texture(tex){};
	CModel(string path) : m_texture(NULL) { m_texture = SDL_LoadBMP(path.c_str()); };
	virtual bool show(float toDrawX, float toDrawY, SDL_Surface* screen);

private:
	SDL_Surface* m_texture;

};


#endif //__CMODEL_H