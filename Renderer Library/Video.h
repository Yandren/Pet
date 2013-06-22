#ifndef __VIDEO_H
#define __VIDEO_H

//replace with a PAL-type implementation lookup, or use GLEW.
//#define GLFW_INCLUDE_GL3 1

#include "pal.h"
#include "glew\include\GL\glew.h"
#include "glfw\include\GLFW\glfw3.h"
#include "CCamera.h"
#include "CShaderManager.h"
#include "glm\glm\glm.hpp"

class CObjectManager;

class CVideoManager
{
public:

  class CSceneManager
  {

  public:
    //methods
    CSceneManager();   
    //CSceneManager(CCamera* cam) : mCamera(cam){}
    ~CSceneManager(){ delete mShaderManager;}
    //bool addObject(CObjectIdHash objID );
    //bool removeObject(CObjectIdHash objID);
    void display(CObjectManager * objMan);
    void update(CObjectManager * objMan);
    glm::mat4 getViewProjectionMatrix(CObjectManager * objMan);
    bool updateViewMatrix(int size, void * info);
    //members
    //CCamera* mCamera;
    CHash mCameraID;
    CShaderManager* mShaderManager;
    GLFWwindow * mWindow;

    // some basic properties about our scene
    float m_Degrees_FieldOfView;
    float m_Radians_FieldOfView;
    float mAspectRatio;
    float mDisplayRangeLower;
    float mDisplayRangeUpper;
    float mToClipPlaneNear;
    float mToClipPlaneFar;

    //View matrix from the camera; since it's an object
    // in object manager, need to query for it and it'll call
    // a callback
    glm::mat4 mViewMatrix;

  }; //end CSceneManager

  //methods
  CVideoManager(){}
  ~CVideoManager(){ DeInit();}
  bool Init(CObjectManager * objMan);
  bool initOpenGL();
  GLuint getVertexBuffer(){return mVertexBuffer;}
  GLuint getColorBuffer(){return mColorBuffer;}
  void DeInit();
  bool loadAndBindBuffer(int attributeNum, int cmpPerData, 
    size_t size, int stride, GLuint bufferID, const GLfloat * data); 
  //members
  CSceneManager* mScene;

private:
  //methods


  //members
  GLuint mVertexArrayID;
  GLuint mVertexBuffer;
  GLuint mColorBuffer;

};

#endif