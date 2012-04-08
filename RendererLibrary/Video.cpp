#include "Video.h"


bool 
VideoManager::Init(){

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) return false;
    if( ( screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL )) == NULL ) return false;     //Create Window


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);							
	glShadeModel(GL_SMOOTH);							
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	//move to lighting class later
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	
	glEnable(GL_LIGHT1);		


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if( glGetError() != GL_NO_ERROR )  return false;

    SDL_WM_SetCaption( "OpenGL Test", NULL );
	
    //SceneGraph* VideoManager::scenegraph = new SceneGraph(screen);
	return true;
}


bool 
VideoManager::SceneGraph::addObject(Object *obj ){
	
	vec.push_back(obj);
	return true;
}; 

bool 
VideoManager::SceneGraph::removeObject(Object *obj){

	std::vector<Object*>::iterator it;

	for(it=vec.begin(); it<=vec.end(); it++)
		if(*it==obj)
			vec.erase(it);
	return true;

};

void 
VideoManager::SceneGraph::handle_input(SDL_Event *event){

	for(uint32_t i=0; i<vec.size(); i++)
		vec.at(i)->handle_input(event);
	
};

void
VideoManager::SceneGraph::display(){

	for(uint32_t i=0; i<vec.size(); i++)
		vec.at(i)->show();
	SDL_Flip(screen);
};

void
VideoManager::SceneGraph::update(){

	for(uint32_t i=0; i<vec.size(); i++)
		vec.at(i)->move();

};