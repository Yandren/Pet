#ifndef __ICMPPHYSICS_H
#define __ICMPPHYSICS_H

#include "IComponent.h"

class CVector;

class ICmpPhysics : public IComponent
{
public:
	ICmpPhysics(){}
	virtual ~ICmpPhysics(){}

protected:
	static void		RegisterInterface(EComponentTypeId);
};

#endif //__ICMPPHYSICS_H