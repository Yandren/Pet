#include "Video.h"
#include "CObjectManager.h"
#include "Component System\CComponentMessage.h"
#include "glm/glm/gtc/matrix_transform.hpp"


static const char * VERTEX_SHADER = "C:/Users/dragonerdriftr/Documents/Pet/Renderer Library/Shaders/base.vert";
static const char * FRAGMENT_SHADER = "C:/Users/dragonerdriftr/Documents/Pet/Renderer Library/Shaders/base.frag";



bool 
  CVideoManager::Init(CObjectManager * objMan)
{
  bool brs= false;
  //SDL_Surface* tempScreen = NULL;

  if(!glfwInit())
  {
    CLog::Get()->Write( LOG_ERROR, "Couldn't create window");
    return false;     //Create Window
  }
  if(!initOpenGL())
  {
    CLog::Get()->Write( LOG_ERROR, "Failed to initialize OpenGL");
    return false;
  }
  if(!(mScene = new CSceneManager()))
  {
    CLog::Get()->Write( LOG_ERROR, "Failed to make a new SceneManager");
    return false;
  }

  return true;
}

bool CVideoManager::initOpenGL()
{
  int err = 0;

  //TODO - move this to a config file
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
#ifdef _DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

  // Open a window and create its OpenGL context
  if( !(mWindow = glfwCreateWindow( 1024, 768, "Pet Project", NULL, NULL )) )
  {
    CLog::Get()->Write( LOG_ERROR, "Failed to open GLFW window\n" );
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(mWindow);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after window open OpenGL error %x", err);
  // Initialize GLEW
  glewExperimental=true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    CLog::Get()->Write( LOG_ERROR, "Failed to initialize GLEW\n");
    return false;
  }
  if((err = glGetError()) != GL_NO_ERROR && err != GL_INVALID_ENUM ) //sometimes init will cause GL_INVALID_ENUM for no reason...
    CLog::Get()->Write( LOG_ERROR, " after glewinit OpenGL error %x", err);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS); 
  //cull triangles whose normals aren't facing us
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  /* New bells
  glEnable(GL_MULTISAMPLE);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(true);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);
  glEnable(GL_DEPTH_CLAMP);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  */

  /* old bells
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
  */

  //create a vertex array
  glGenVertexArrays(1, &mVertexArrayID);
  glBindVertexArray(mVertexArrayID);

  // Generate a vertex buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &mVertexBuffer);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after genbuffers OpenGL error %x", err);
  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after bind buffers OpenGL error %x", err);

  // Generate a color buffer, put the resulting identifier in our colorbuffer
  glGenBuffers(1, &mColorBuffer);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after genbuffers OpenGL error %x", err);
  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after bind buffers OpenGL error %x", err);


  if( (err = glGetError()) != GL_NO_ERROR )
  {
    CLog::Get()->Write( LOG_ERROR, "OpenGL error %x", err);
    return false;
  }

  return true;
};

bool
  CVideoManager::loadAndBindBuffer(int attributeNum, int cmpPerData, 
  size_t size, int stride, GLuint bufferID, const GLfloat * data )
{
  int err = 0;
  glBindBuffer(GL_ARRAY_BUFFER, bufferID);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after bind buffer OpenGL error %x", err);
  //Vertices for shaders/drawing
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 
  //sizeof(glm::vec4) * mMesh[i]->mVertices.size(), &(mMesh[i]->mVertices[0]), GL_STATIC_DRAW);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after bufferdata OpenGL error %x", err);
  // 1rst attribute buffer : vertices, prep for shaders
  glEnableVertexAttribArray(attributeNum);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, " after enable VAA OpenGL error %x", err);
  glVertexAttribPointer(
    attributeNum,       // attribute 0. No particular reason for 0, but must match the layout in the shader.
    cmpPerData,         // number of components per vertex
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,             // stride
    (void*)0            // array buffer offset
    );
  if((err = glGetError()) != GL_NO_ERROR)
  {
    CLog::Get()->Write( LOG_ERROR, " after attribute pointer OpenGL error %x", err);
    return false;
  }
  return true;
}

void
  CVideoManager::DeInit()
{
  delete mScene; 
  glDeleteBuffers(1, &mVertexBuffer);
  glDeleteBuffers(1, &mColorBuffer); 
  glDeleteVertexArrays(1, &mVertexArrayID);
  glfwTerminate();

}


CVideoManager::CSceneManager::CSceneManager()
{
  //set up 
  //mCamera = new CCamera(); <- moved to being an object in Object Manager
  mShaderManager = new CShaderManager();
  if(!mShaderManager->initShaders(VERTEX_SHADER, FRAGMENT_SHADER))
  {
    CLog::Get()->Write( LOG_ERROR, "Failed to init shaders!");
  }

  //set up default projection matrix
  m_Degrees_FieldOfView = 45.0f;
  mAspectRatio = 4.0f / 3.0f;
  mDisplayRangeLower = 0.1f;
  mDisplayRangeUpper = 100.0f;
}

void
  CVideoManager::CSceneManager::display(GLFWwindow * window, CObjectManager * objMan)
{
  int err = 0;
  if( (err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, "display() errored before anything was done, %x", err );

  glm::mat4 ViewProj = getViewProjectionMatrix(objMan);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, "display() clear errored, %x", err);

  //validates, then tells OpenGL to use shader programs stored in manager
  if(!mShaderManager->useShaderPrograms())
    CLog::Get()->Write( LOG_ERROR, "Error using the shaders");

  //send uniform MVP transformation to shaders
  if(!mShaderManager->sendDataToShader("MVP", &ViewProj[0][0]))
    CLog::Get()->Write( LOG_ERROR, "Problems giving data to shader!");


  //Construct the neccesary render info for components
  CComponentMessage renderMsg = CComponentMessage(MT_INIT_RENDER);
  //renderMsg.mpData = &ViewProj;
  objMan->BroadcastMessage(renderMsg);
  objMan->BroadcastMessage(CComponentMessage(MT_RENDER));

  //after all the things have been drawn, swap the buffers to see things
  glfwSwapBuffers(window);

  //clear the culling flag, since we've displayed for this loop
  objMan->BroadcastMessage(CComponentMessage(MT_CLEAR_CULL_FLAG));
};

void
  CVideoManager::CSceneManager::update(CObjectManager * objMan)
{

  //view frustum culling, based on camera
  CComponentMessage cull = CComponentMessage(MT_FRUSTUM_CULL);

  //send along the viewing volume we're using
  //if(this->mCamera)
  //{
  //float buff[] = { mCamera->mPosition.x, mCamera->mPosition.y, mCamera->mViewportWidth, mCamera->mViewportHeight}; 
  //cull.mpData = buff;
  //}
  objMan->BroadcastMessage(cull);

};

glm::mat4
  CVideoManager::CSceneManager::getViewProjectionMatrix(CObjectManager * objMan)
{

  glm::mat4 projectionMatrix = glm::perspective(m_Degrees_FieldOfView,
                                                mAspectRatio, 
                                                mDisplayRangeLower, 
                                                mDisplayRangeUpper);
  //call to the Object Manager, which will net us a view matrix 
  // from the camera (via callbacks) to work with.
  if(!attachCamera(objMan))
     CLog::Get()->Write( LOG_ERROR, "Couldn't find camera object" );
  
  //now that the message was posted and callback serviced, we have
  // an updated ViewMatrix to return
  return (projectionMatrix * mViewMatrix);
};

bool 
  CVideoManager::CSceneManager::updateViewMatrix(int size, SSpacialInfo info)
{
  /*
  if(info)
    return false;
    */
  mViewMatrix = glm::lookAt(glm::vec3(info.mPosition), glm::vec3(info.mDirection), glm::vec3(info.mOrientation));
  return true;
};

bool
  CVideoManager::CSceneManager::attachCamera(CObjectManager * objMan)
{
  //register callbacks for general objects that need to
  //send information to the video manager (e.g. the camera)
  //if(!objMan->addCallbackForCmpInterface(CHash("camera"), IID_ENTITY, std::bind(&CSceneManager::updateViewMatrix, this, std::placeholders::_1, std::placeholders::_2 )))
  SpacialCallback_t binding = std::bind(&CSceneManager::updateViewMatrix, this, std::placeholders::_1, std::placeholders::_2 );
  SSpacialCallbackInfo call(binding);
  CComponentMessage msg = CComponentMessage( MT_CALLBACK_INFO, &call);
  objMan->PostMessage(mCameraID, msg);
  //TODO: need to report message-delivery results, in ObjectManager
 
  return true;
}