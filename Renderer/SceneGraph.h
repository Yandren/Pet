#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "Object.h"

class SceneGraph{
	
  public:
	//methods
	bool addObject(object *obj ); 
	virtual display() = 0;
	bool removeObject(object *obj);




}


#endif