#include "Physics.h"

bool 
CPhysicsManager::Init(){
	b2Vec2 gravity(0.0f, -10.0f);

	world = new b2World(gravity);
	return true;
}


void
CPhysicsManager::Shutdown(){

	delete world;

}




