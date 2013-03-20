#ifndef __CCMPPHYSICS_H
#define __CCMPPHYSICS_H

#include "ICmpPhysics.h"
#include "pal.h"
#include <set>

class CCmpPhysics : public ICmpPhysics
{
public:
	CCmpPhysics();
	virtual ~CCmpPhysics();

	// Static methods
	static void			RegisterComponentType(void);
	static IComponent	*CreateMe();
	static bool			DestroyMe(IComponent *);

	// Virtual IComponent methods
	virtual bool		Init(CObjectIdHash, tinyxml2::XMLNode&);
	virtual void		Deinit(void);
	virtual EMessageResult		HandleMessage(const CComponentMessage &);
	virtual EComponentTypeId	GetComponentTypeId(void);

	
private:

};

#endif //__CCMPPHYSICS_H