#ifndef CCAMERA_H
#define CCAMERA_H

#include "glm\glm\glm.hpp"

class CCamera {

public:

  CCamera(){};
  ~CCamera(){};

  glm::vec4 mPosition;
  glm::vec4 mOrientation;
  glm::mat4 mViewMatrix;
  int mViewportHeight;
  int mViewportWidth;

};

#endif