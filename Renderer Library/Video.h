#ifndef VIDEO_H
#define VIDEO_H

//replace with a PAL-type implementation lookup, or use GLEW.
//#define GLFW_INCLUDE_GL3 1

#include "pal.h"
#include "glew\include\GL\glew.h"
#include "glfw\include\GL\glfw.h"
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
    CSceneManager();   
    CSceneManager(CCamera* cam) : mCamera(cam){}
    ~CSceneManager(){ delete mCamera; glDeleteProgram(mShaderProgramID);};
    bool addObject(CObjectIdHash objID );
    void set_camera_position(float x_coord, float y_coord, float z_coord);
    void set_camera_size(int new_height, int new_width);
    bool removeObject(CObjectIdHash objID);
    void display(CObjectManager * objMan);
    void update(CObjectManager * objMan);
    bool initShaders(const std::string vertPath, const std::string fragPath);
    bool loadShader(const char * path, EShaderType type);

    //members
    CCamera* mCamera;
    std::vector<GLuint> mShaderIDs;
    GLuint mShaderProgramID;
    float m_Degrees_FieldOfView;
    float m_Radians_FieldOfView;
    float mAspectRatio;
    float mDisplayRangeLower;
    float mDisplayRangeUpper;
  }; //end CSceneManager

  CVideoManager(){}
  ~CVideoManager(){ Shutdown();}

  bool Init();

  GLuint getVertexBuffer(){return mVertexBuffer;}
  bool initOpenGL();
  void Shutdown(){ delete mScene; glfwTerminate();}

  CSceneManager* mScene;

private:

  GLuint mVertexBuffer;




};

#endif