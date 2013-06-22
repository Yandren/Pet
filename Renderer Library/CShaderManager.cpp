#include "pal.h"
#include "glew\include\GL\glew.h"
#include "glfw\include\GLFW\glfw3.h"
#include "CShaderManager.h"



bool
  CShaderManager::initShaders(const std::string vertPath, const std::string fragPath){
    int err = 0;
    GLint Result = GL_FALSE;
    int InfoLogLength;
    int shadersAttached;

    if(!loadShader(vertPath.c_str(), VERTEX))
    {
      CLog::Get()->Write(LOG_ERROR, "Can't load vertex shader");
      return false;
    }
    if(!loadShader(fragPath.c_str(), FRAGMENT))
    {
      CLog::Get()->Write(LOG_ERROR, "Can't load vertex shader");
      return false;
    }
    // Link the program
    mShaderProgramID = glCreateProgram();
    if((err = glGetError()) != GL_NO_ERROR)
      CLog::Get()->Write( LOG_ERROR, " creating shader program; OpenGL error %x", err);

    for(int i =0; i < mShaderIDs.size(); i++)
    {
      glAttachShader(mShaderProgramID, mShaderIDs[i]);
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get()->Write( LOG_ERROR, " attaching shaders; OpenGL error %x", err);
    }
    glGetProgramiv(mShaderProgramID, GL_ATTACHED_SHADERS, &shadersAttached);
    if(shadersAttached > mShaderIDs.size())
      CLog::Get()->Write( LOG_ERROR, "Not all shaders are attached to the shader program!");

    glLinkProgram(mShaderProgramID);
    if((err = glGetError()) != GL_NO_ERROR)
      CLog::Get()->Write( LOG_ERROR, " linking program; OpenGL error %x", err);

    // Check the program
    glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(mShaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0 || Result != GL_TRUE)
    { //grab the error message
      std::vector<char> ProgramErrorMessage( InfoLogLength + 1 );
      glGetProgramInfoLog(mShaderProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      CLog::Get()->Write(LOG_ERROR, "shader linking says: %s\n", &ProgramErrorMessage[0]);
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
      CLog::Get()->Write(LOG_GENERAL, "WARNING: shader not fully cleared, "\
        "may not have deleted unlinked shaders; "\
        "%d left in memory", mShaderIDs.size());
    }

    if(mShaderProgramID == 0)
    {
      CLog::Get()->Write(LOG_ERROR, "ShaderProgram ID is 0 for some reason, we have an issue");
      return false;
    }


    return true;
}

bool 
  CShaderManager::loadShader(const char* path, EShaderType type)
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
    CLog::Get()->Write(LOG_ERROR, "Incorrect shader type given %d", type);
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
  CLog::Get()->Write( LOG_GENERAL, "Compiling shader : %s", path);
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
    CLog::Get()->Write( LOG_ERROR, "Shader says: %s", ShaderErrorMessage);
    delete ShaderErrorMessage;
  }
  //add it to the tracked Shader ID's
  mShaderIDs.push_back(ShaderID);

  return true;
}



bool 
  CShaderManager::useShaderPrograms()
{
  int err = 0;
  //Shader business - check that it's a valid state for shader
  glValidateProgram(mShaderProgramID);
  if((err = glGetError()) != GL_NO_ERROR)
  { //grab and write out the error message
    int InfoLogLength = 0;
    CLog::Get()->Write( LOG_ERROR, "validation check of shader program failed, %x!", err);
    glGetProgramiv(mShaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(mShaderProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    CLog::Get()->Write(LOG_ERROR, "shader says: %s", &ProgramErrorMessage[0]);
    return false;
  }//end if glGetError
  GLint errOut = 0;
  glGetProgramiv(mShaderProgramID, GL_VALIDATE_STATUS, &errOut);
  if(errOut != GL_TRUE)
  {
    CLog::Get()->Write( LOG_ERROR, "shader program not validated.");
    return false;
  }

  //everything's okay, we can use the shader
  glUseProgram(mShaderProgramID);
  if((err = glGetError()) != GL_NO_ERROR)
    CLog::Get()->Write( LOG_ERROR, "shader use errored, %x", err);

  return true;
}


bool
  CShaderManager::sendDataToShader(std::string varName, void* data)
{
  int err = 0;
  GLuint varID = glGetUniformLocation(mShaderProgramID, varName.c_str());
  GLsizei length = 0;
  GLint size = 0;
  GLenum type = 0;
  GLchar * name = new char [1024];

  glGetActiveUniform(mShaderProgramID, varID, 1024, NULL, &size, &type, name);
  if((err = glGetError()) != GL_NO_ERROR)
  {
    CLog::Get()->Write( LOG_ERROR, "OpenGL error trying to get access to variables in shader, err: %x", err);
    return false;
    }
  delete name;

  switch(type)
  {
  case GL_FLOAT:
    glUniform1f(varID, *(static_cast<GLfloat*>(data)));
    break;
  case GL_FLOAT_VEC2:
    glUniform2fv(varID, 1, static_cast<GLfloat*>(data));
    break;
  case GL_FLOAT_VEC3:
    glUniform3fv(varID, 1, static_cast<GLfloat*>(data));
    break;
  case GL_FLOAT_VEC4:
    glUniform4fv(varID, 1, static_cast<GLfloat*>(data));
    break;
  case GL_INT:
    glUniform1i(varID, *(static_cast<GLint*>(data)));
    break;
  case GL_INT_VEC2:
    glUniform2iv(varID, 1, static_cast<GLint*>(data));
    break;
  case GL_INT_VEC3:
    glUniform3iv(varID, 1, static_cast<GLint*>(data));
    break;
  case GL_INT_VEC4:
    glUniform4iv(varID, 1, static_cast<GLint*>(data));
    break;
  case GL_FLOAT_MAT2:
    glUniformMatrix2fv(varID, 1, GL_FALSE, static_cast<GLfloat*>(data));
    break;
  case GL_FLOAT_MAT3:
    glUniformMatrix3fv(varID, 1, GL_FALSE, static_cast<GLfloat*>(data));
    break;
  case GL_FLOAT_MAT4:
    glUniformMatrix4fv(varID, 1, GL_FALSE, static_cast<GLfloat*>(data));
    break;

  default:
    CLog::Get()->Write( LOG_ERROR, "Shader uniform variable type not supported. %d", type);
    return false;
  };

  if((err = glGetError()) != GL_NO_ERROR)
  {
    CLog::Get()->Write( LOG_ERROR, "OpenGL error trying to pass a value to shader, err: %x", err);
    return false;
  }
  return true;
}