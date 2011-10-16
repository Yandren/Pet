#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "Object.h"

class SceneGraph{
	
  public:
	//methods
	bool addObject(Object *obj ); 
	void virtual display() = 0;
	bool removeObject(Object *obj);




}


#endif