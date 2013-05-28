#ifndef __CMESH_H
#define __CMESH_H

#include "pal.h"
#include "glm\glm\glm.hpp"
#include "assimp\include\assimp\scene.h"

class CMesh {

public:

  CMesh()
  : mName("NoNameMesh"),
    mPosition(glm::vec4(0.0, 0.0, 0.0, 1.0)),
    mOrientation(glm::vec4(0.0, 0.0, 0.0, 0.0)),
    mNumVerts(0),
    mNumInd(0),
    mNumTriangles(0)
      {};
  CMesh(std::string path)
   : mName(path.c_str()),
     mPosition(glm::vec4(0.0, 0.0, 0.0, 1.0)),
     mOrientation(glm::vec4(0.0, 0.0, 0.0, 0.0)),
     mNumVerts(0),
     mNumInd(0),
     mNumTriangles(0)
  { setName(path);};
  virtual ~CMesh(){ };//delete mVertices; delete mNormals; delete mBiNormals; }
  void setOrientation(glm::vec4 orient){ mOrientation = orient; }
  void setPosition(glm::vec4 pos) { mPosition = pos;} 
  void setName(std::string name) {mName = name;}
  std::string getName(){ return mName;}
  glm::vec4 getPosition() {return mPosition;}
  glm::vec4 getOrientation() { return mOrientation;}
  glm::vec4 * getVerticesArray(){return &(mVertices[0]);}
  bool loadFromImport(const aiMesh* loadMesh);

  
  int mNumVerts; //used to index into mVertices
  int mNumFaces;
  int mNumInd;
  int mNumTriangles;

  std::vector<glm::vec4> mVertices; //this is allocated/destroyed/managed internally
  std::vector<glm::vec4> mNormals;
  std::vector<glm::vec4> mBiNormals;

private:

  std::string mName;

  glm::vec4 mPosition;
  glm::vec4 mOrientation;

};


#endif