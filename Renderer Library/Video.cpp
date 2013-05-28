#include "Video.h"
#include "CObjectManager.h"
#include "Component System\CComponentMessage.h"


static const char * VERTEX_SHADER = "C:/Users/dragonerdriftr/Documents/Pet/Renderer Library/Shaders/base.vert";
static const char * FRAGMENT_SHADER = "C:/Users/dragonerdriftr/Documents/Pet/Renderer Library/Shaders/base.frag";



bool 
  CVideoManager::Init()
{
  bool brs= false;
  //SDL_Surface* tempScreen = NULL;

  if(!glfwInit())
  {
    CLog::Get().Write( LOG_ERROR, "Couldn't create window");
    return false;     //Create Window
  }

  if(!initOpenGL())
  {
    CLog::Get().Write( LOG_ERROR, "Failed to initialize OpenGL");
    return false;
  }
  if((mScene = new CSceneManager()))
  {
    mScene->initShaders(VERTEX_SHADER, FRAGMENT_SHADER);
    return true;
    }
  return false;
}

bool CVideoManager::initOpenGL()
{
  int err = 0;

  //TODO - move this to a config file
  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
#ifdef DEBUG
  glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

  // Open a window and create its OpenGL context
  if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
  {
    CLog::Get().Write( LOG_ERROR, "Failed to open GLFW window\n" );
    glfwTerminate();
    return false;
  }
  if((err = glGetError()) != GL_NO_ERROR)
  CLog::Get().Write( LOG_ERROR, " after window open OpenGL error %x", err);
  // Initialize GLEW
  glewExperimental=true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    CLog::Get().Write( LOG_ERROR, "Failed to initialize GLEW\n");
    return false;
  }
  if((err = glGetError()) != GL_NO_ERROR)
  CLog::Get().Write( LOG_ERROR, " after glewinit OpenGL error %x", err);

  glfwSetWindowTitle( "Pet Project" );

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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

  //START OF CRAP TO REMOVE


  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &mVertexBuffer);
  if((err = glGetError()) != GL_NO_ERROR)
  CLog::Get().Write( LOG_ERROR, " after genbuffers OpenGL error %x", err);
  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
  if((err = glGetError()) != GL_NO_ERROR)
  CLog::Get().Write( LOG_ERROR, " after bind buffers OpenGL error %x", err);

  //END OF CRAP TO REMOVE

  if( (err = glGetError()) != GL_NO_ERROR )
  {
    CLog::Get().Write( LOG_ERROR, "OpenGL error %x", err);
    return false;
  }

  return true;
};


CVideoManager::CSceneManager::CSceneManager()
{
  mCamera = new CCamera();
  /*
  if(!initShaders(VERTEX_SHADER, FRAGMENT_SHADER))
  {
  CLog::Get().Write( LOG_ERROR, "Failed to init shaders!");
  }
  */
}

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
  CVideoManager::CSceneManager::initShaders(const std::string vertPath, const std::string fragPath){
    int err = 0;
    GLint Result = GL_FALSE;
    int InfoLogLength;
    int shadersAttached;

    if(!loadShader(vertPath.c_str(), VERTEX))
    {
      CLog::Get().Write(LOG_ERROR, "Can't load vertex shader");
      return false;
    }
    if(!loadShader(fragPath.c_str(), FRAGMENT))
    {
      CLog::Get().Write(LOG_ERROR, "Can't load vertex shader");
      return false;
    }
    // Link the program
    mShaderProgramID = glCreateProgram();
    if((err = glGetError()) != GL_NO_ERROR)
      CLog::Get().Write( LOG_ERROR, " creating shader program; OpenGL error %x", err);

    for(int i =0; i < mShaderIDs.size(); i++)
    {
      glAttachShader(mShaderProgramID, mShaderIDs[i]);
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get().Write( LOG_ERROR, " attaching shaders; OpenGL error %x", err);
    }
    glGetProgramiv(mShaderProgramID, GL_ATTACHED_SHADERS, &shadersAttached);
    if(shadersAttached > mShaderIDs.size())
      CLog::Get().Write( LOG_ERROR, "Not all shaders are attached to the shader program!");

    glLinkProgram(mShaderProgramID);
    if((err = glGetError()) != GL_NO_ERROR)
      CLog::Get().Write( LOG_ERROR, " linking program; OpenGL error %x", err);

    // Check the program

    glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(mShaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0 || Result != GL_TRUE)
    {

      char * ProgramErrorMessage = new char[InfoLogLength +1];
      glGetProgramInfoLog(mShaderProgramID, InfoLogLength, NULL, ProgramErrorMessage);
      CLog::Get().Write(LOG_ERROR, "shader linking says: %s\n", ProgramErrorMessage);
      delete ProgramErrorMessage;
    }

    //get rid of compiled shaders, now that they're all linked
    int size = mShaderIDs.size();
    for(int i = 0; i < size; i++)
    {
      glDeleteShader(mShaderIDs.back());
      mShaderIDs.pop_back();
    }

    if(mShaderIDs.size() != 0)
    {
      CLog::Get().Write(LOG_GENERAL, "WARNING: shader not fully cleared, "\
        "may not have deleted unlinked shaders; "\
        "%d left in memory", mShaderIDs.size());
    }

    if(mShaderProgramID == 0)
    {
      CLog::Get().Write(LOG_ERROR, "ShaderProgram ID is 0 for some reason, we have an issue");
      return false;
    }
    return true;
}

bool 
  CVideoManager::CSceneManager::loadShader(const char* path, EShaderType type)
{
  GLint Result = GL_FALSE;
  int InfoLogLength;
  // Create the shader
  GLuint ShaderID;

  switch (type) {

  case VERTEX:
    ShaderID = glCreateShader(GL_VERTEX_SHADER);
    break;

  case FRAGMENT:
    ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    break;

  default:
    CLog::Get().Write(LOG_ERROR, "Incorrect shader type given %d", type);
    return false;
    break;
  }; 

  // Read the Shader code from the file
  std::string ShaderCode;
  std::ifstream ShaderStream(path, std::ios::in);
  if(ShaderStream.is_open())
  {
    std::string Line = "";
    while(getline(ShaderStream, Line))
      ShaderCode += "\n" + Line;
    ShaderStream.close();
  }

  // Compile Shader
  CLog::Get().Write( LOG_GENERAL, "Compiling shader : %s", path);
  char const * SourcePointer = ShaderCode.c_str();
  glShaderSource(ShaderID, 1, &SourcePointer , NULL);
  glCompileShader(ShaderID);

  // Check Shader
  glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

  char * ShaderErrorMessage = new char[InfoLogLength +1];
  if(InfoLogLength > 0 || Result != GL_TRUE)
   {
  glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, ShaderErrorMessage);
  CLog::Get().Write( LOG_ERROR, "Shader says: %s", ShaderErrorMessage);
  delete ShaderErrorMessage;
   }
  //add it to the tracked Shader ID's
  mShaderIDs.push_back(ShaderID);

  return true;
}

void 
  CVideoManager::CSceneManager::set_camera_position(float x_coord, float y_coord, float z_coord)
{
  glm::vec4 pos(x_coord, y_coord, z_coord, 1.0);
  mCamera->mPosition = pos;
};

void 
  CVideoManager::CSceneManager::set_camera_size(int new_height, int new_width)
{
  mCamera->mViewportHeight = new_height;
  mCamera->mViewportWidth = new_width;

};


void
  CVideoManager::CSceneManager::display(CObjectManager * objMan)
{
  int err = 0;
  if( (err = glGetError()) != GL_NO_ERROR)
    CLog::Get().Write( LOG_ERROR, "display() errored before anything was done, %x", err );

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get().Write( LOG_ERROR, "display() clear errored, %x", err);


  glUseProgram(mShaderProgramID);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get().Write( LOG_ERROR, "shader use errored, %x", err);


  glValidateProgram(mShaderProgramID);
  if((err = glGetError()) != GL_NO_ERROR)
  {
    int InfoLogLength = 0;
    CLog::Get().Write( LOG_ERROR, "validation of shader program failed, %x!", err);
    glGetProgramiv(mShaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char * ProgramErrorMessage = new char[InfoLogLength + 1];
    glGetProgramInfoLog(mShaderProgramID, InfoLogLength, NULL, ProgramErrorMessage);
    CLog::Get().Write(LOG_ERROR, "shader says: %s", ProgramErrorMessage);
    delete ProgramErrorMessage;
  }
  GLint errOut = 0;
  glGetProgramiv(mShaderProgramID, GL_VALIDATE_STATUS, &errOut);
  if(errOut != GL_TRUE)
    CLog::Get().Write( LOG_ERROR, "shader program not validated.");

  objMan->BroadcastMessage(CComponentMessage(MT_INIT_RENDER));
  objMan->BroadcastMessage(CComponentMessage(MT_RENDER));

  //after all the things have been drawn, swap the buffers to see things
  glfwSwapBuffers();

  //clear the culling flag, since we've displayed for this loop
  objMan->BroadcastMessage(CComponentMessage(MT_CLEAR_CULL_FLAG));
};

void
  CVideoManager::CSceneManager::update(CObjectManager * objMan)
{

  //view frustum culling, based on camera
  CComponentMessage cull = CComponentMessage(MT_FRUSTUM_CULL);

  //send along the viewing volume we're using
  if(this->mCamera)
  {
    float buff[] = { mCamera->mPosition.x, mCamera->mPosition.y, mCamera->mViewportWidth, mCamera->mViewportHeight}; 
    cull.mpData = buff;
  }
  objMan->BroadcastMessage(cull);

};