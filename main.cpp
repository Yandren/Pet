#include "WinConstants.h"
#include "Video.h"
#include "Timer.h"
#include "Square.h"
#include "Log.h"


bool init()
{
	Log::Get().Init();
	VideoManager::Get().Init();

    return true;
}

void clean_up()
{
    VideoManager::Get().Shutdown();
	Log::Get().Shutdown();
}


int main( int argc, char *argv[] )
{
	SDL_Event event;
    bool quit = false;

    if( init() == false ) return 1;

	Log::Get().Write(GEN_LOG, "TESTING");
    Square square;

    //frame rate regulator
    Timer fps;

	while( quit == false )
	{
        fps.start();
 
		//Event Handling
		while( SDL_PollEvent( &event ) )
		{
            square.handle_input(&event);
			if( event.type == SDL_QUIT ) quit = true;
		}
		
			//Render
	    square.move();

		//Display
	    glClear( GL_COLOR_BUFFER_BIT );
	    square.show();

	
	    //Update screen
	    SDL_GL_SwapBuffers();
	
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
     
	}

	clean_up();

	return 0;
}
