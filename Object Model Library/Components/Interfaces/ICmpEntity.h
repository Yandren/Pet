#ifndef __ICMPENTITY_H
#define __ICMPENTITY_H

#include "IComponent.h"
#include "glm\glm\glm.hpp"

class CVector;

class ICmpEntity : public IComponent
{
public:
  //constructors/destructors
  ICmpEntity(){}
  virtual ~ICmpEntity(){}

  //methods
  
  //spacial information
  virtual glm::vec4	GetPosition() const {return mPosition;}
  virtual void	SetPosition(glm::vec4 pos){mPosition = pos;}
  virtual glm::vec4	GetOrientation() const {return mOrientation;}
  virtual void	SetOrientation(glm::vec4 orient){mOrientation = orient;}
  virtual glm::vec4	GetDirection() const {return mDirection;}
  virtual void	SetDirection(glm::vec4 direction){mDirection = direction;}

  virtual bool	GetInteract() const { return mCanInteract;}
  virtual void	SetInteract(bool interact) {mCanInteract = interact;}


protected:
  //methods
  static void		RegisterInterface(EComponentTypeId cmpid);
  //members
  glm::vec4 mPosition;
  glm::vec4 mOrientation;
  glm::vec4 mDirection;
  float mMoveSpeed;
  std::string mName;
  bool	mCanInteract;
};

#endif //__ICMPENTITY_H