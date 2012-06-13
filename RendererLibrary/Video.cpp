#include "Video.h"


bool 
VideoManager::Init(){
	bool brs= false;
	SDL_Surface* tempScreen = NULL;
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) return false;
    if( ( tempScreen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF )) == NULL ) return false;     //Create Window


	/*glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);							
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);							
	//glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	//move to lighting class later
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	
	glEnable(GL_LIGHT1);		


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	
    if( glGetError() != GL_NO_ERROR )  return false;
	*/
    SDL_WM_SetCaption( "Pet Project", NULL );
	return (scene = new SceneGraph(tempScreen))?true:false;
}


bool 
VideoManager::SceneGraph::addObject(Object *obj ){
	dynamicObjects.push_back(obj);
	return true;
}; 

bool 
VideoManager::SceneGraph::removeObject(Object *obj){
	bool brs = false;
	std::vector<Object*>::iterator it;

	for(it=dynamicObjects.begin(); it<=dynamicObjects.end(); it++)
		if(*it==obj){
			dynamicObjects.erase(it);
			brs = true;
		}
	return brs;

};

void 
VideoManager::SceneGraph::handle_input(SDL_Event *event){

	for(uint32_t i=0; i<dynamicObjects.size(); i++)
		dynamicObjects.at(i)->handle_input(event);
	
};

void
VideoManager::SceneGraph::display(){
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	
	for(uint32_t i=0; i<dynamicObjects.size(); i++)
		dynamicObjects.at(i)->show();
	SDL_Flip(screen);
};

void
VideoManager::SceneGraph::update(){

	for(uint32_t i=0; i<dynamicObjects.size(); i++)
		dynamicObjects.at(i)->move();
	

};