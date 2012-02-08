#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "Object.h"

class SceneGraph{
	
  public:
	//methods
	bool addObject(Object *obj ); 
	bool removeObject(Object *obj);
	bool update();
    
}


#endif