#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "pal.h"
#include "Object.h"
#include <vector>

class SceneGraph{
	
  public:
	//methods
	bool addObject(Object *obj ); 
    void handle_input(SDL_Event *event);
	bool removeObject(Object *obj);
	void display();
    void update();

	//members
	std::vector<Object*> vec;
};


#endif