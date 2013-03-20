#ifndef PHYSICS_H
#define	PHYSICS_H

#include "Box2D/Box2D.h"

class b2World;

class CPhysicsManager{

public:
	CPhysicsManager(){}
	~CPhysicsManager(){}

	bool Init();
	void Shutdown();


private:
	b2World* world;

};

#endif