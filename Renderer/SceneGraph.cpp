#include "SceneGraph.h"

bool 
SceneGraph::addObject(Object *obj ){
	
	vec.push_back(obj);
	return true;
}; 

bool 
SceneGraph::removeObject(Object *obj){

	std::vector<Object*>::iterator it;

	for(it=vec.begin(); it<=vec.end(); it++)
		if(*it==obj)
			vec.erase(it);
	return true;

};

void 
SceneGraph::handle_input(SDL_Event *event){

	for(uint32_t i=0; i<vec.size(); i++)
		vec.at(i)->handle_input(event);
	
};

void
SceneGraph::display(){

	for(uint32_t i=0; i<vec.size(); i++)
		vec.at(i)->show();

};

void
SceneGraph::update(){

	for(uint32_t i=0; i<vec.size(); i++)
		vec.at(i)->move();

};