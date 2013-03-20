#include "Video.h"
#include "IObject.h"
#include "GameState.h"
#include "Physics.h"
#include "CObjectManager.h"
#include "Globals.h"
//Take out eventually
#include "CSquare.h"
#include "pal.h"
#include <SDL.h>

bool 
init()
{
	if(CLog::Get().Init())
	  if(Globals::GetPhysicsManager().Init())
	    if(Globals::GetVideoManager().Init())
	      if(Globals::GetGameStateManager().Init())
			if(Globals::GetObjectManager().Init())
			  return true;
			else
				  return false;
		  else
			  return false;
		else
			return false;
	  else
		  return false;
	else
		return false;
}

void 
clean_up()
{
	Globals::GetGameStateManager().Shutdown();
	Globals::GetVideoManager().Shutdown();
	Globals::GetPhysicsManager().Shutdown();
	CLog::Get().Shutdown();
	
}


int 
main( int argc, char *argv[] ){
	SDL_Event event;
    bool quit = false;
	
	//create global managers
	CGameStateManager gameStateManager = Globals::GetGameStateManager();
	CPhysicsManager physicsManager = Globals::GetPhysicsManager();
	CVideoManager videoManager = Globals::GetVideoManager();
	CObjectManager objectManager = Globals::GetObjectManager();
	//frame rate regulator
	CTimer fps_reg = Globals::GetCTimer();


    if( init() == false ) return 1;

	CLog::Get().Write(GEN_CLog, "TESTING");

	//this will be moved to the object model library code
	//Load objects from file/load the level!
	//1) 
	//objectManager.LoadObjectsFromFile();
	IObject* square = (IObject*)new CSquare(1.0, 1.0, 0.0, 0.0, videoManager.scene->screen);
	
	videoManager.scene->addObject(square);
	//end stuff to be moved 
 
	//it's looping time!
	while( quit == false ){
        //start our timer
		fps_reg.start();
		
		//Event Handling
		while( SDL_PollEvent( &event ) ){
			gameStateManager.handle_input(&event);
            //CVideoManager::Get().scene->what_to_render();
			if( event.type == SDL_QUIT ) quit = true;
		}
		//Update
	    //Update the game state 
		gameStateManager.update();
		//Update the scene (any changes in what's in view, etc)
		videoManager.scene->update();

		//Display
	    glClear( GL_COLOR_BUFFER_BIT );
	    videoManager.scene->display();
	    //Update the screen
	    SDL_GL_SwapBuffers();
        //Cap the frame rate
        if( fps_reg.get_ticks() < 1000 / FRAMES_PER_SECOND ) SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps_reg.get_ticks() );
	}
	clean_up();
	return 0;
}