#ifndef VIDEO_H
#define VIDEO_H

#include <SDL/SDL.h>
#include "WinConstants.h"
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

};

#endif