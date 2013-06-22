#ifndef __CCMPRENDERABLE_H
#define __CCMPRENDERABLE_H

#include "ICmpRenderable.h"
#include "pal.h"
#include <set>

class CCmpRenderable : public ICmpRenderable
{
public:
	CCmpRenderable();
	virtual ~CCmpRenderable();

	// Static methods
	static void			RegisterComponentType(void);
	static IComponent	*CreateMe();
	static bool			DestroyMe(IComponent *);

	// Virtual IComponent methods
	virtual bool		Init(CObjectIdHash, tinyxml2::XMLNode &);
	virtual void		Deinit(void);
	virtual EMessageResult		HandleMessage(const CComponentMessage &);
	virtual EComponentTypeId	GetComponentTypeId(void);
	
private:

};

#endif //__CCMPRENDERABLE_H