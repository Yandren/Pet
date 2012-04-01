#ifndef VIDEO_H
#define VIDEO_H

//replace with a PAL-type implementation.
#include "pal.h"
#include <SDL/SDL_opengl.h>

class VideoManager{

public:
	VideoManager(){}
	~VideoManager(){}
	static VideoManager &Get(){	
      static VideoManager video; return video;}
	bool Init();
	void Shutdown(){ SDL_Quit(); }

private:
	SDL_Surface* screen;
};

#endif