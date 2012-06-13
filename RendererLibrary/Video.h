#ifndef VIDEO_H
#define VIDEO_H

//replace with a PAL-type implementation.
#include "pal.h"
#include <SDL/SDL_opengl.h>
#include "Object.h"
#include <vector>

class VideoManager{

public:

	class SceneGraph{
	
      public:
	  //methods
	    SceneGraph(SDL_Surface* s) : screen(s) {};
		~SceneGraph(){};
	    bool addObject(Object *obj ); 
        void handle_input(SDL_Event *event);
	    bool removeObject(Object *obj);
	    void display();
        void update();

	    //members
	    std::vector<Object*> dynamicObjects;
	    SDL_Surface* screen;
    };

	VideoManager() : scene(NULL){}
	~VideoManager(){}
	static VideoManager &Get(){	static VideoManager video; return video;}
	bool Init();
	void Shutdown(){ delete scene; SDL_Quit(); }

	SceneGraph* scene;

};

#endif