#ifndef VIDEO_H
#define VIDEO_H

//replace with a PAL-type implementation.
#include "pal.h"
#include <SDL/SDL_opengl.h>
#include "IObject.h"
#include "CCamera.h"
#include <vector>

class CVideoManager{

public:

	class CSceneGraph : COctree{
	
      public:
	  //methods
	    CSceneGraph(SDL_Surface* s) : screen(s) {};
		~CSceneGraph(){ delete screen; delete camera;};
	    bool addObject(IObject *obj );
        void set_camera_position(float x_coord, float y_coord);
		void set_camera_size(int new_height, int new_width);
	    bool removeObject(IObject *obj);
	    void display();
        void update();

	    //members
	    std::vector<IObject*> dynamiObjects;
	    SDL_Surface* screen;
		CCamera* camera;
    };

	CVideoManager() : scene(NULL){}
	~CVideoManager(){ Shutdown();}
	
	bool Init();
	void Shutdown(){ delete scene; SDL_Quit(); }

	CSceneGraph* scene;

};

#endif