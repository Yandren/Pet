#ifndef __ICMPRENDERABLE_H
#define __ICMPRENDERABLE_H

#include "IComponent.h"
#include "CComponentMessage.h"
#include "CModel.h"

class ICmpRenderable : public IComponent
{
public:
	ICmpRenderable() : m_model(NULL), m_surface(NULL), mPositionReq(false){};
	ICmpRenderable(SDL_Surface* srf) : m_model(NULL), m_surface(srf){};
	ICmpRenderable(CModel* mod) : m_model(mod), m_surface(NULL){};
	ICmpRenderable(SDL_Surface* srf, CModel* mod) : m_model(mod), m_surface(srf){};

	virtual ~ICmpRenderable(){}

protected:
	static void	RegisterInterface(EComponentTypeId);
	virtual void setModel(CModel* mod){ m_model = mod;}
	virtual bool createModel(std::string path);
	virtual void setSurface(SDL_Surface* surface) { m_surface = surface;}

	CModel *m_model;
	SDL_Surface *m_surface;
  //we'll need to get a position from Entity component to render, so store it
  SPositionInfo mPosition;
  bool mPositionReq;
};

#endif //__ICMPRENDERABLE_H