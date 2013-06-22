#ifndef __PHYSICS_H
#define	__PHYSICS_H

//#include "Box2D/Box2D.h"

//class b2World;

class CPhysicsManager{

public:
	CPhysicsManager(){}
	~CPhysicsManager(){}

	bool Init();
	void DeInit();


private:
	//b2World* world;

};

#endif