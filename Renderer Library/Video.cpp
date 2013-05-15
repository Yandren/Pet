#include "Video.h"
#include "CObjectManager.h"
#include "Component System\CComponentMessage.h"

bool 
  CVideoManager::Init()
{
  bool brs= false;
  SDL_Surface* tempScreen = NULL;
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
  {
    CLog::Get().Write( LOG_ERROR, "didn't initialize SDL");
    return false;
  }
  if( ( tempScreen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_OPENGL*/ )) == NULL ) 
  {
    CLog::Get().Write( LOG_ERROR, "Couldn't create window");
    return false;     //Create Window
  }
  if(!initOpenGL())
  {
    CLog::Get().Write( LOG_ERROR, "Couldn't initialize OpenGL");
    return false;
  }

  SDL_WM_SetCaption( "Pet Project", NULL );
  return (scene = new CSceneManager(tempScreen));
}

bool CVideoManager::initOpenGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
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

  if( glGetError() != GL_NO_ERROR )
  {
    CLog::Get().Write( LOG_ERROR, "OpenGL error %d", glGetError());
    return false;
  }

  /*
  //set up some drawing buffers and bind them (OpenGL 3.x)
  glGenBuffers(1, &mVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

  // Give our vertices to OpenGL, should be in the model code
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
 */

  return false;
};
bool 
  CVideoManager::CSceneManager::addObject(CObjectIdHash objID)
{

  return true;
}; 

bool 
  CVideoManager::CSceneManager::removeObject(CObjectIdHash objID)
{
  bool brs = false;

  return brs;

};

bool 
  CVideoManager::loadShaders(char* path, EShaderType type)
{


}

void 
  CVideoManager::CSceneManager::set_camera_position(float x_coord, float y_coord)
{
  CSceneManager::camera->y_coord = y_coord;
  CSceneManager::camera->x_coord = x_coord;

};

void 
  CVideoManager::CSceneManager::set_camera_size(int new_height, int new_width)
{
  CSceneManager::camera->viewport_height = new_height;
  CSceneManager::camera->viewport_width = new_width;

};


void
  CVideoManager::CSceneManager::display(CObjectManager * objMan)
{
  if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)) != 0)
    CLog::Get().Write( LOG_ERROR, "display FillRect call errored");

  objMan->BroadcastMessage(CComponentMessage(MT_INIT_RENDER));
  objMan->BroadcastMessage(CComponentMessage(MT_RENDER));
  if(SDL_Flip(screen) != 0)
    CLog::Get().Write( LOG_ERROR, "SDL_Flip errored");
  //clear the culling flag, since we've displayed for this loop
  objMan->BroadcastMessage(CComponentMessage(MT_CLEAR_CULL_FLAG));
};

void
  CVideoManager::CSceneManager::update(CObjectManager * objMan)
{

  //view frustum culling, based on camera
  CComponentMessage cull = CComponentMessage(MT_FRUSTUM_CULL);

  //send along the viewing volume we're using
  if(this->camera)
  {
    float buff[] = { camera->x_coord, camera->y_coord, camera->viewport_width, camera->viewport_height}; 
    cull.mpData = buff;
  }
  objMan->BroadcastMessage(cull);

};