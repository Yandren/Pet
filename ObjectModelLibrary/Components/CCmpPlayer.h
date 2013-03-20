#ifndef __CCMPPlayer_H
#define __CCMPPlayer_H

#include "ICmpPlayer.h"
#include "pal.h"

class CCmpPlayer : public ICmpPlayer
{
public:
	CCmpPlayer();
	virtual ~CCmpPlayer();

	// Static methods
	static void			RegisterComponentType(void);
	static IComponent	*CreateMe();
	static bool			DestroyMe(IComponent *);

	// Virtual IComponent methods
	virtual bool		Init(CObjectIdHash, tinyxml2::XMLNode &);
	virtual void		Deinit(void);
	virtual EMessageResult		HandleMessage(const CComponentMessage &);
	virtual EComponentTypeId	GetComponentTypeId();

protected:
	bool	HandleCommand(const char *commandString);
};

#endif //__CCMPPlayer_H