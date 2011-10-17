#ifndef VIDEO_H
#define VIDEO_H

#include <SDL/SDL.h>
#include "WinConstants.h"
#include <SDL/SDL_opengl.h>

class VideoManager{

public:
	VideoManager();
	~VideoManager();
	static VideoManager &Get();
	bool Init();
	void Shutdown();

private:

};

#endif