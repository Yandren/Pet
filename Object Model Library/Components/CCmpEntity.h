#ifndef __CCMPENTITY_H
#define __CCMPENTITY_H

#include "ICmpEntity.h"
#include "pal.h"
#include <set>

class CCmpEntity : public ICmpEntity
{
public:
	CCmpEntity();
	virtual ~CCmpEntity();

	// Static methods
	static void			RegisterComponentType(void);
	static IComponent	*CreateMe();
	static bool			DestroyMe(IComponent *);

	// Virtual IComponent methods
	virtual bool		Init(CObjectIdHash, tinyxml2::XMLNode&);
	virtual void		Deinit(void);
	virtual EMessageResult		HandleMessage(const CComponentMessage &);
	virtual EComponentTypeId	GetComponentTypeId(void);

	// Tests whether this object can be seen by the viewer taking its position, and whether this object is
	// in an inventory into account.
	virtual bool	CanThisObjectBeSeenBy(CObjectIdHash viewer, bool includeInventoryObject) const;


};

#endif //__CCMPENTITY_H