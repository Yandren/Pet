#ifndef __ICMPENTITY_H
#define __ICMPENTITY_H

#include "IComponent.h"

class CVector;

class ICmpEntity : public IComponent
{
public:
	ICmpEntity(){}
	virtual ~ICmpEntity(){}
	virtual bool	CanThisObjectBeSeenBy(CObjectIdHash viewer, bool includeInventoryObject) const = 0;

	//position information
	virtual Vec3 <float>	GetPosition() const {return mPosition;}
	virtual void	SetPosition(Vec3 <float> pos){mPosition = pos;}
	virtual bool	GetInteract() const { return mCanInteract;}
	virtual void	SetInteract(bool interact) {mCanInteract = interact;}
    

protected:
	static void		RegisterInterface(EComponentTypeId cmpid);
	Vec3 <float> mPosition;
	bool	mCanInteract;
};

#endif //__ICMPENTITY_H