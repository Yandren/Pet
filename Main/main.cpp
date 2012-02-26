#include "WinConstants.h"
#include "Video.h"
#include "Timer.h"
#include "Log.h"
#include "Object.h"
#include "Physics.h"
//Take out eventually
#include "Square.h"
#include "SceneGraph.h"


bool 
init()
{
	Log::Get().Init();
	PhysicsManager::Get().Init();
	VideoManager::Get().Init();

    return true;
}

void 
clean_up()
{

    VideoManager::Get().Shutdown();
	PhysicsManager::Get().Shutdown();
	Log::Get().Shutdown();
	
}


int 
main( int argc, char *argv[] )
{
	SDL_Event event;
    bool quit = false;

    if( init() == false ) return 1;

	Log::Get().Write(GEN_LOG, "TESTING");
	SceneGraph scenegraph;
    Square square;

	scenegraph.addObject((Object*) &square);

    //frame rate regulator
    Timer fps;

	while( quit == false )
	{
        fps.start();
 
		//Event Handling
		while( SDL_PollEvent( &event ) )
		{
            scenegraph.handle_input(&event);
			if( event.type == SDL_QUIT ) quit = true;
		}
		
	    //Render
	    scenegraph.update();

		//Display
	    glClear( GL_COLOR_BUFFER_BIT );
	    scenegraph.display();

	
	    //Update screen
	    SDL_GL_SwapBuffers();
	
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
     
	}

	clean_up();

	return 0;
}
