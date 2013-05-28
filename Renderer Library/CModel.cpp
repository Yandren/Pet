#include "CModel.h"
#include "Video.h"
#include "assimp\include\assimp\Importer.hpp"
#include "assimp\include\assimp\scene.h"
#include "assimp\include\assimp\postprocess.h"

bool CModel::show(glm::vec4 * position, CVideoManager * vidMan){
  int err = 0;
  //SDL_Surface * sdlTex = mTexture->getSDL_Surface();
  if(false)
  {
    CLog::Get().Write( LOG_ERROR, "No surface from the Texture");
    return false;
  }
  if(false)
  {
    CLog::Get().Write( LOG_ERROR, "No screen passed to us");
    return false;
  }
  GLuint vertBuffer = vidMan->getVertexBuffer();

  if(mMesh.size() > 0)
  {
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
      -1.0f, -1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f,
      0.0f,  1.0f, 0.0f, 1.0f
    };
    // Give our vertices to OpenGL.
    for(int i = 0; i < mMesh.size(); i++)
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); 
      //sizeof(glm::vec4) * mMesh[i]->mVertices.size(), &(mMesh[i]->mVertices[0]), GL_STATIC_DRAW);
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get().Write( LOG_ERROR, " after bufferdata OpenGL error %x", err);
      // 1rst attribute buffer : vertices, prep for shaders
      glEnableVertexAttribArray(0);
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get().Write( LOG_ERROR, " after enable VAA OpenGL error %x", err);
      glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get().Write( LOG_ERROR, " after bind buffer OpenGL error %x", err);
      glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        4,                  // number of components per vertex
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get().Write( LOG_ERROR, " after attribute pointer OpenGL error %x", err);
      // Draw the triangle !
      glDrawArrays(GL_TRIANGLES, 0, 3); //mMesh[i]->mNumVerts); // Starting from vertex 0; 3 vertices total -> 1 triangle
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get().Write( LOG_ERROR, " after draw arrays OpenGL error %x", err);
      glDisableVertexAttribArray(0);

    }
    if(err != GL_NO_ERROR)
      return false;

    return true;
  }

  else
  {
    CLog::Get().Write( LOG_ERROR, "No meshes to draw, size zero!");
    return false;
  }//end else - setColorKey

}

bool
  CModel::loadMeshFromDisk(std::string path)
{

  Assimp::Importer importer;

  const aiScene * scene = importer.ReadFile(path.c_str(), 
    aiProcess_CalcTangentSpace      |
    aiProcess_Triangulate           |
    aiProcess_JoinIdenticalVertices |
    aiProcess_SortByPType);

  if(!scene){
    CLog::Get().Write( LOG_ERROR, "Couldn't load mesh from file, %s", importer.GetErrorString());
    return false;
  }
  aiNode * root = scene->mRootNode;
  for (int n = 0; n < root->mNumMeshes; ++n)
  {
    const aiMesh* loadMesh = scene->mMeshes[root->mMeshes[n]];
    //apply material
    if(loadMesh->mNormals == NULL)
    {
      //either no lightning, or generate normals
    }
    CMesh * mesh = new CMesh();
    mesh->loadFromImport(loadMesh);
    mMesh.push_back(mesh);


  }


  return true;
}