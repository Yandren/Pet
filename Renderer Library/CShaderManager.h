#ifndef __CSHADERMANAGER_H
#define __CSHADERMANAGER_H

#include <vector>

enum EShaderType
{
  VERTEX, FRAGMENT, MISC
};

class CShaderManager
{
public:
  //constructors/destructors
  CShaderManager() {}
  CShaderManager(std::string shaders[]){}//TODO
  virtual   ~CShaderManager(){glDeleteProgram(mShaderProgramID); }
  //methods
  bool    initShaders(const std::string vertPath, const std::string fragPath);
  bool    loadShader(const char * path, EShaderType type);
  bool    useShaderPrograms();
  bool    useShaderProgram(std::string name);
  bool    sendDataToShader( std::string varName, void* data);

private:

  //members
  std::vector<GLuint> mShaderIDs;
  GLuint              mShaderProgramID;
};


#endif