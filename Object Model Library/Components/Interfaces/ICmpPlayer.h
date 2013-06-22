#ifndef __ICMPPlayer_H
#define __ICMPPlayer_H

#include "ICmpInput.h"


class CVector;

class ICmpPlayer : public ICmpInput
{
public:
	ICmpPlayer(){}
	virtual ~ICmpPlayer(){}

protected:
	static void		RegisterInterface(EComponentTypeId);
};

#endif //__ICMPPlayer_H