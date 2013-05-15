#ifndef VIDEO_H
#define VIDEO_H

//replace with a PAL-type implementation.
#include "pal.h"
#include "SDL/include/SDL_opengl.h"
#include "CCamera.h"
#include <vector>

class CObjectManager;

class CVideoManager
{
  enum EShaderType
  {
    VERTEX, FRAGMENT, MISC
  };

public:

  class CSceneManager : COctree
  {

  public:
    //methods
    CSceneManager(SDL_Surface* s) : screen(s) 
    { camera = new CCamera(); }
    CSceneManager(SDL_Surface* s, CCamera* cam) : screen(s), camera(cam){}
    ~CSceneManager(){ delete screen; delete camera;};
    bool addObject(CObjectIdHash objID );
    void set_camera_position(float x_coord, float y_coord);
    void set_camera_size(int new_height, int new_width);
    bool removeObject(CObjectIdHash objID);
    void display(CObjectManager * objMan);
    void update(CObjectManager * objMan);

    //members
    SDL_Surface* screen;
    CCamera* camera;
  }; //end CSceneManager

  CVideoManager() : scene(NULL){}
  ~CVideoManager(){ Shutdown();}

  bool Init();
  bool loadShaders(char * path, EShaderType type);
  GLuint getVertexBuffer(){return mVertexBuffer;}
  bool initOpenGL();
  void Shutdown(){ delete scene; SDL_Quit(); }

  CSceneManager* scene;

private:

  GLuint mVertexBuffer;


};

#endif