#include "Video.h"
#include "Object.h"
#include "Physics.h"
//Take out eventually
#include "Square.h"
#include "pal.h"
#include <SDL.h>

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
    Object* square = (Object*)new Square();
	VideoManager::Get().scene->addObject(square);

    //frame rate regulator
    Timer fps_reg;

	while( quit == false )
	{
        fps_reg.start();
 
		//Event Handling
		while( SDL_PollEvent( &event ) )
		{
            VideoManager::Get().scene->handle_input(&event);
			if( event.type == SDL_QUIT ) quit = true;
		}

	    //Render
	    VideoManager::Get().scene->update();
		  
		//Display
	    glClear( GL_COLOR_BUFFER_BIT );
	    VideoManager::Get().scene->display();

	
	    //Update screen
	    SDL_GL_SwapBuffers();
	
        //Cap the frame rate
        if( fps_reg.get_ticks() < 1000 / FRAMES_PER_SECOND ) SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps_reg.get_ticks() );
	}

	clean_up();

	return 0;
}
