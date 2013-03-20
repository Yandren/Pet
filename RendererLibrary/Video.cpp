#include "Video.h"


bool 
CVideoManager::Init(){
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
	return (scene = new CSceneGraph(tempScreen))?true:false;
}


bool 
CVideoManager::CSceneGraph::addObject(IObject *obj ){
	dynamiObjects.push_back(obj);
	return true;
}; 

bool 
CVideoManager::CSceneGraph::removeObject(IObject *obj){
	bool brs = false;
	std::vector<IObject*>::iterator it;

	for(it=dynamiObjects.begin(); it<=dynamiObjects.end(); it++)
		if(*it==obj){
			dynamiObjects.erase(it);
			brs = true;
		}
	return brs;

};

void 
CVideoManager::CSceneGraph::set_camera_position(float x_coord, float y_coord){
	CSceneGraph::camera->y_coord = y_coord;
	CSceneGraph::camera->x_coord = x_coord;
	
};

void 
CVideoManager::CSceneGraph::set_camera_size(int new_height, int new_width){
	CSceneGraph::camera->viewport_height = new_height;
	CSceneGraph::camera->viewport_width = new_width;
	
};


void
CVideoManager::CSceneGraph::display(){
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	

	for(uint32_t i=0; i<dynamiObjects.size(); i++)
		dynamiObjects.at(i)->show();
	SDL_Flip(screen);
};

void
CVideoManager::CSceneGraph::update(){

	//view frustum culling, based on camera


};