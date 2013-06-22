#include "Video.h"
#include "GameStateManager.h"
#include "Physics.h"
#include "CObjectManager.h"
#include "CInputManager.h"
#include "Globals.h"
//Take out eventually
#include "pal.h"

bool 
  init()
{
  if(CLog::Get()->Init())
    if(Globals::GetObjectManager()->Init())
      if(Globals::GetVideoManager()->Init(Globals::GetObjectManager()))
        if(Globals::GetGameStateManager()->Init())
          if(Globals::GetPhysicsManager()->Init())
            if(Globals::GetInputManager()->Init(Globals::GetObjectManager()))
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
  else
    return false;
}

void 
  clean_up()
{
  Globals::GetGameStateManager()->DeInit();
  Globals::GetVideoManager()->DeInit();
  Globals::GetPhysicsManager()->DeInit();
  Globals::GetObjectManager()->DeInit();
  CLog::Get()->DeInit();

}


int 
  main( int argc, char *argv[] ){

    bool quit = false;

    //frame rate regulator
    CTimer * fps_reg = Globals::GetTimer();

    if( init() == false ) return 1;

    //grab global managers into locals
    CGameStateManager* gameStateManager = Globals::GetGameStateManager();
    CPhysicsManager* physicsManager = Globals::GetPhysicsManager();
    CVideoManager* videoManager = Globals::GetVideoManager();
    CObjectManager* objectManager = Globals::GetObjectManager();
    CInputManager* inputManager = Globals::GetInputManager();

    CLog::Get()->Write( LOG_GENERAL, "Managers Initialized");

    //void (*callback)(int, int) = &(gameStateManager->handle_input);

    //TODO: Load objects from file/load the level!
    //TODO: load splash screen here 
    objectManager->LoadObjectsFromFile(Globals::OBJECTS_XML_FILE);
    //IObject* square = (IObject*)new CSquare(1.0, 1.0, 0.0, 0.0, videoManager.scene->screen);


    //end stuff to be moved 

    fps_reg->start();
    float fps = 0.0;
    //it's looping time!
    while( quit == false ){

      switch( gameStateManager->getCurrentState() ){

      case Exiting:
        quit = true;

      case Uninitialized:
        CLog::Get()->Write( LOG_ERROR, "Uninitialized state!");
        return false;

      case Playing:
        //Start a game-state specific clock?


        CLog::Get()->Write( LOG_GENERAL, "Playing state");

        //Event Handling - give it over to gamestate (via callback)
        //glfwSetKeyCallback(callback);
        /*while( glfwPollEvents() ){
        gameStateManager.handle_input(&event);
        //CVideoManager::Get().scene->what_to_render();
        if( event.type == SDL_QUIT ) quit = true;
        }
        */
        //Get any inputs
        if(! inputManager->mPlayerInputHandler->processInput(
                                          videoManager->mScene->mWindow, fps_reg) )
           CLog::Get()->Write( LOG_ERROR, "Input processing failure!");                                  

        //Update
        //Update the game state 
        gameStateManager->update();
        //Update the scene (any changes in what's in view, etc)
        videoManager->mScene->update(objectManager);

        //Display
        glClear( GL_COLOR_BUFFER_BIT );
        videoManager->mScene->display(objectManager);
        //Update the screen, updates Input events


        //Cap the frame rate?
        fps = fps_reg->get_ticks();
        //if( fps < 1000 / FRAMES_PER_SECOND ) glfwSleep( (( 1000 / FRAMES_PER_SECOND ) - fps) / 1000 );
        break;

      case Loading:
        CLog::Get()->Write( LOG_GENERAL, "Loading gamestate");
        gameStateManager->popState();
        gameStateManager->pushState(Menu);
        break;

      case Menu:
        //TODO - put in menu system, actually allow stuff
        CLog::Get()->Write( LOG_GENERAL, "Menu gamestate");
        gameStateManager->popState();
        //we'd normally get here through selecting an option in the menu, in the GUI code
        gameStateManager->pushState(Playing);
        break;
      default:
        CLog::Get()->Write( LOG_GENERAL, "Default reached in GameState switch...?");
        break;
      }
    }

    clean_up();
    return 0;
}