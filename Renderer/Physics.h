#ifndef PHYSICS_H
#define	PHYSICS_H

#include "../OtherLibs/Box2D/Box2D.h"

class b2World;

class PhysicsManager{

public:
	PhysicsManager(){}
	~PhysicsManager(){}
	static PhysicsManager &Get(){
	  static PhysicsManager phys; return phys;}
	bool Init();
	void Shutdown();

private:
	b2World* world;

};

#endif