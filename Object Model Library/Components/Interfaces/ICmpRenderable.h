#ifndef __ICMPRENDERABLE_H
#define __ICMPRENDERABLE_H

#include "IComponent.h"
#include "CComponentMessage.h"
#include "CModel.h"

class ICmpRenderable : public IComponent
{
public:
	ICmpRenderable() : m_model(NULL), mSpacialReq(false){};
	ICmpRenderable(CModel* mod) : m_model(mod){};

	virtual ~ICmpRenderable(){}

protected:
	static void	RegisterInterface(EComponentTypeId);
	virtual void setModel(CModel* mod){ m_model = mod;}
	virtual bool createModel(std::string path);
	
	CModel *m_model;
	
  //we'll need to get a position from Entity component to render, so store it
  SSpacialInfo mSpacialInfo;
  bool mSpacialReq;
};

#endif //__ICMPRENDERABLE_H