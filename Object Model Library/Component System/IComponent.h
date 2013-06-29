#ifndef __ICOMPONENT_H
#define __ICOMPONENT_H

#include "pal.h"
#include "Component System\ComponentStructs.h"


/************************************
*
* Forward Declarations
*
*************************************/
namespace tinyxml2 {class XMLNode;}
class CComponentMessage;
class ICmpEntity;
class ObjectManager;

// The IComponent class. All our component classes inherit from this
class IComponent
{
	friend class CObjectManager;

public:
  //constructors/destructors
	IComponent();
	virtual ~IComponent();
  //methods
	virtual bool              Init(CObjectIdHash, tinyxml2::XMLNode &) = 0;
	virtual void              Deinit(void) = 0;
	CObjectIdHash             GetObjectId(void) const     { return mObjectId; }
	ICmpEntity *              GetEntity() const;
	virtual EMessageResult    HandleMessage(const CComponentMessage &) = 0;
	virtual EComponentTypeId	GetComponentTypeId(void) = 0;
  //members
protected:
  //methods
  void      addExternalCallback(ExternalComponentInfoCallback func) { mExternalCallback = func;}
	void      SetObjectId(CObjectIdHash oId)  { mObjectId = oId; }
	
  //members
  CObjectIdHash       mObjectId;
  //callback function for whatever use component wants it. Registered via ObjectManager
  ExternalComponentInfoCallback mExternalCallback;
	
};
#endif //__ICOMPONENT_H