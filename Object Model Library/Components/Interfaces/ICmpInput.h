#ifndef __ICMPINPUT_H
#define __ICMPINPUT_H

#include "IComponent.h"
#include "CInputManager.h"


class ICmpInput : public IComponent
{
public:
	ICmpInput(){}
	virtual ~ICmpInput(){}

protected:
	static void		RegisterInterface(EComponentTypeId);
};

#endif //__ICMPINPUT_H