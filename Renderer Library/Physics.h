#ifndef __PHYSICS_H
#define	__PHYSICS_H

//#include "Box2D/Box2D.h"

//class b2World;

class CPhysicsManager{

public:
	
	~CPhysicsManager(){}

	bool Init();
	void DeInit();
  static CPhysicsManager * getInstance()
    { static CPhysicsManager * physMan = new CPhysicsManager(); return physMan;}

private:
  //Constructor - singleton
  CPhysicsManager(){}
	//b2World* world;

};

#endif