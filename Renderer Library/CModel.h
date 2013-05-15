#ifndef __CMODEL_H
#define __CMODEL_H

#include "pal.h"
#include "CMesh.h"
#include "CTexture.h"
#include <string>
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_opengl.h"


class CModel {

public:
  CModel(CTexture* tex) //add SDL_SetColorKeyf color param here for background color to ignore when drawing 
  : mTexture(tex),
    mMesh()
    {};
  CModel(std::string texPath) 
  : mTexture(NULL),
    mMesh()
     { mTexture = new CTexture(texPath); };
  CModel(){ mTexture = new CTexture(); }
  virtual ~CModel(){delete mTexture;}
  virtual bool show(Vec3 <float>* position, SDL_Surface* screen);

private:
  CTexture* mTexture;
  Vec3<CMesh *> mMesh;

};


#endif //__CMODEL_H