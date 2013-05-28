#ifndef __ICMPENTITY_H
#define __ICMPENTITY_H

#include "IComponent.h"
#include "glm\glm\glm.hpp"

class CVector;

class ICmpEntity : public IComponent
{
public:
	ICmpEntity(){}
	virtual ~ICmpEntity(){}
	virtual bool	CanThisObjectBeSeenBy(CObjectIdHash viewer, bool includeInventoryObject) const = 0;

	//position information
	virtual glm::vec4	GetPosition() const {return mPosition;}
	virtual void	SetPosition(glm::vec4 pos){mPosition = pos;}
	virtual bool	GetInteract() const { return mCanInteract;}
	virtual void	SetInteract(bool interact) {mCanInteract = interact;}
    

protected:
	static void		RegisterInterface(EComponentTypeId cmpid);
	glm::vec4 mPosition;
	bool	mCanInteract;
};

#endif //__ICMPENTITY_H