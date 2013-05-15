#ifndef __CMESH_H
#define __CMESH_H

#include "pal.h"


class CMesh {

public:

  CMesh()
  : mName("NoNameMesh"),
    mPosition(Vec3<float>(0.0f, 0.0f, 0.0f)),
    mOrientation(Vec3<float>(0.0f, 0.0f, 0.0f)),
    mNumVerts(0),
    mNumInd(0),
    mNumTriangles(0)
      {};
  CMesh(std::string path)
   : mName(path.c_str()),
     mPosition(Vec3<float>(0.0f, 0.0f, 0.0f)),
     mOrientation(Vec3<float>(0.0f, 0.0f, 0.0f)),
     mNumVerts(0),
     mNumInd(0),
     mNumTriangles(0)
  {};
  CMesh(std::vector<float> vec)
   {mVertices = vec;};
  void setOrientation(Vec3<float> orient){ mOrientation = orient; }
  void setPosition(Vec3<float> pos) { mPosition = pos;} 
  void setName(std::string name) {mName = name;}
  std::string getName(){ return mName;}
  Vec3<float> getPosition() {return mPosition;}
  Vec3<float> getOrientation() { return mOrientation;}

private:

  std::string mName;

  Vec3<float> mPosition;
  Vec3<float> mOrientation;

  int mNumVerts;
  int mNumInd;
  int mNumTriangles;

  std::vector<float> mVertices;



};


#endif