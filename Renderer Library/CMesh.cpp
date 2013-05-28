#include "CMesh.h"
#include "assimp\include\assimp\Importer.hpp"
#include "assimp\include\assimp\scene.h"
#include "assimp\include\assimp\postprocess.h"

bool
  CMesh::loadFromImport(const aiMesh * loadMesh)
{
  if(mVertices.size() > 0)
  {
    CLog::Get().Write( LOG_GENERAL, "--WARNING-- deleting Vertices previously in Mesh %s", mName.c_str()); 
    mVertices.clear();
  }

  //mVertices = new glm::vec4[loadMesh->mNumVertices];
  for(uint32_t i=0; i < loadMesh->mNumVertices; ++i)
  {
    mVertices.push_back(glm::vec4(loadMesh->mVertices[i].x, loadMesh->mVertices[i].y, loadMesh->mVertices[i].z, 1.0f)); //these are positions, 1.0 in w slot
  }

  return true;
}