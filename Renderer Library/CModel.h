#ifndef __CMODEL_H
#define __CMODEL_H

#include "pal.h"
#include "glm\glm\glm.hpp"
#include "CMesh.h"
#include "CTexture.h"
#include <string>

class CVideoManager;


class CModel {

public:
  CModel(CTexture* tex) //add SDL_SetColorKeyf color param here for background color to ignore when drawing 
  : mTexture(tex),
    mMesh(),
    mModelViewMatrix(1.0f)
    {};
  CModel(std::string meshPath) 
  : mTexture(NULL),
    mMesh(),
    mModelViewMatrix(1.0f)
     { loadMeshFromDisk(meshPath); mTexture = new CTexture();};
  CModel(){ mTexture = new CTexture(); }
  CModel(std::string meshPath, std::string texPath)
    {loadMeshFromDisk(meshPath); loadTextureFromDisk(texPath);}
  
  virtual ~CModel(){delete mTexture; while(mMesh.size() > 0) {delete mMesh.back(); mMesh.pop_back();}}
  virtual bool show(glm::vec4 * position, CVideoManager * vidMan);
  bool loadMeshFromDisk(std::string path);
  bool loadTextureFromDisk(std::string path);
  glm::mat4 getModelViewMatrix(){ return mModelViewMatrix;}

private:
  CTexture* mTexture;
  std::vector<CMesh *> mMesh;
  glm::mat4 mModelViewMatrix;
};


#endif //__CMODEL_H