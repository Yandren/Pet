#include "Video.h"
#include "GameStateManager.h"
#include "Physics.h"
#include "CObjectManager.h"
#include "Globals.h"
//Take out eventually
#include "pal.h"

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
  Globals::GetObjectManager().DeInit();
  CLog::Get().Shutdown();

}


int 
  main( int argc, char *argv[] ){
    SDL_Event event;
    bool quit = false;

    //frame rate regulator
    CTimer fps_reg = Globals::GetCTimer();

    if( init() == false ) return 1;

    //grab global managers into locals
    CGameStateManager gameStateManager = Globals::GetGameStateManager();
    CPhysicsManager physicsManager = Globals::GetPhysicsManager();
    CVideoManager videoManager = Globals::GetVideoManager();
    CObjectManager objectManager = Globals::GetObjectManager();

    CLog::Get().Write( LOG_GENERAL, "TESTING");

    //this will be moved to the object model library code
    //Load objects from file/load the level!
    //1) 
    objectManager.LoadObjectsFromFile(Globals::OBJECTS_XML_FILE);
    //IObject* square = (IObject*)new CSquare(1.0, 1.0, 0.0, 0.0, videoManager.scene->screen);

    //videoManager.scene->addObject(square);
    //end stuff to be moved 
     fps_reg.start();

    //it's looping time!
    while( quit == false ){

      switch( gameStateManager.getCurrentState() ){

      case Uninitialized:
        CLog::Get().Write( LOG_ERROR, "Uninitialized state!");
        return false;

      case Playing:
        //start our timer
        CLog::Get().Write( LOG_GENERAL, "Playing state");
       
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
        videoManager.scene->update(&objectManager);

        //Display
        glClear( GL_COLOR_BUFFER_BIT );
        videoManager.scene->display(&objectManager);
        //Update the screen
        //SDL_GL_SwapBuffers();
        //Cap the frame rate
        if( fps_reg.get_ticks() < 1000 / FRAMES_PER_SECOND ) SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps_reg.get_ticks() );
        break;

      case Loading:
        CLog::Get().Write( LOG_GENERAL, "Loading gamestate");
        gameStateManager.popState();
        gameStateManager.pushState(Menu);
        break;

      case Menu:
        //TODO - put in menu system, actually allow stuff
        CLog::Get().Write( LOG_GENERAL, "Menu gamestate");
        gameStateManager.popState();
        //we'd normally get here through selecting an option in the menu, in the GUI code
        gameStateManager.pushState(Playing);
        break;
      default:
        CLog::Get().Write( LOG_GENERAL, "Default reached in GameState switch...?");
        break;
      }
    }

    clean_up();
    return 0;
}