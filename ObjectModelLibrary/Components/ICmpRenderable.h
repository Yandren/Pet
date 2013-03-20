#ifndef __ICMPRENDERABLE_H
#define __ICMPRENDERABLE_H

#include "IComponent.h"
#include "CModel.h"

class ICmpRenderable : public IComponent
{
public:
	ICmpRenderable() : m_model(NULL), m_surface(NULL){}
	ICmpRenderable(SDL_Surface* srf) : m_model(NULL), m_surface(srf){}
	ICmpRenderable(CModel* mod) : m_model(mod), m_surface(NULL){}
	ICmpRenderable(SDL_Surface* srf, CModel* mod) : m_model(mod), m_surface(srf){}

	virtual ~ICmpRenderable(){}

protected:
	static void	RegisterInterface(EComponentTypeId);
	virtual void setModel(CModel* mod){ m_model = mod;}
	virtual bool createModel(string path);
	virtual void setSurface(SDL_Surface* surface) { m_surface = surface;}

	CModel *m_model;
	SDL_Surface *m_surface;
};

struct SRenderableInfo
{
	float x_pos;
	float y_pos;
};

#endif //__ICMPRENDERABLE_H