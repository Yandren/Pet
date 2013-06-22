#include "CModel.h"
#include "Video.h"
#include "assimp\include\assimp\Importer.hpp"
#include "assimp\include\assimp\scene.h"
#include "assimp\include\assimp\postprocess.h"

bool CModel::show(glm::vec4 * position, 
                  glm::vec4 * direction, 
                  glm::vec4 * orientation, 
                  CVideoManager * vidMan){
  int err = 0;

  GLuint vertBuffer = vidMan->getVertexBuffer();
  GLuint colorBuffer = vidMan->getColorBuffer();

  if(mMesh.size() > 0)
  {
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = { 
      -1.0f,-1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f,-1.0f, 1.0f, 
      -1.0f,-1.0f,-1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f, 1.0f,
      1.0f,-1.0f, 1.0f, 1.0f, 
      -1.0f,-1.0f,-1.0f, 1.0f,
      1.0f,-1.0f,-1.0f, 1.0f, 
      1.0f, 1.0f,-1.0f, 1.0f, 
      1.0f,-1.0f,-1.0f, 1.0f, 
      -1.0f,-1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f, 1.0f,
      1.0f,-1.0f, 1.0f, 1.0f, 
      -1.0f,-1.0f, 1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f,-1.0f, 1.0f, 1.0f,
      1.0f,-1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 1.0f, 
      1.0f,-1.0f,-1.0f, 1.0f, 
      1.0f, 1.0f,-1.0f, 1.0f, 
      1.0f,-1.0f,-1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 1.0f, 
      1.0f,-1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f,-1.0f, 1.0f, 
      -1.0f, 1.0f,-1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 
      -1.0f, 1.0f,-1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 
      -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f,-1.0f, 1.0f, 1.0f 
    };
    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = { 
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f
    };
    // Give our vertices to OpenGL.
    //for(int i = 0; i < mMesh.size(); i++)
    //{
      vidMan->loadAndBindBuffer(0, 4, sizeof(g_vertex_buffer_data), 0, vertBuffer, &g_vertex_buffer_data[0]);
      vidMan->loadAndBindBuffer(1, 4, sizeof(g_color_buffer_data), 0, colorBuffer, &g_color_buffer_data[0]);

      // Draw time!
      glDrawArrays(GL_TRIANGLES, 0, 12*3); //mMesh[i]->mNumVerts); // Starting from vertex 0; 3 vertices total -> 1 triangle
      if((err = glGetError()) != GL_NO_ERROR)
        CLog::Get()->Write( LOG_ERROR, " after draw arrays OpenGL error %x", err);
      glDisableVertexAttribArray(0);//TODO - this is horrible, fix it
      glDisableVertexAttribArray(1);

   // }
    if(err != GL_NO_ERROR)
      return false;

    return true;
  }
  else
  {
    CLog::Get()->Write( LOG_ERROR, "No meshes to draw, size zero!");
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
    CLog::Get()->Write( LOG_ERROR, "Couldn't load mesh from file, %s", importer.GetErrorString());
    return false;
  }
  aiNode * root = scene->mRootNode;
  for (uint32_t n = 0; n < root->mNumMeshes; ++n)
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