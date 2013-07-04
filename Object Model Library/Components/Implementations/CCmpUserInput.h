#ifndef __CCMPUSERINPUT_H
#define __CCMPUSERINPUT_H

#include "ICmpInput.h"
#include "glew\include\GL\glew.h"
#include "glfw\include\GLFW\glfw3.h"


/************************************
*
* Forward Declarations
*
*************************************/
class CComponentMessage;



/************************************
*
* Callbacks
*
*************************************/
 
 //our callback function signature
//typedef std::function<void (CHash,  CComponentMessage &)> playerInputFunctionCallback;

//Structure which we store in the input+action->callback mapping;
//specifically
/*struct SPlayerInputCallback : public SCallbackSignature
{

  playerInputFunctionCallback pCallback;
  virtual void * getCallback() const { return (void *)&pCallback;};

};
*/



/************************************
*
* Classes
*
************************************/

class CCmpUserInput : public ICmpInput
{

public:
  //Constructors/Destructors
  CCmpUserInput(){};
  virtual ~CCmpUserInput(){};
  //methods
  
  // Static methods
	static void			          RegisterComponentType(void);
	static IComponent	*       CreateMe();
	static bool			          DestroyMe(IComponent *);

  // Virtual IComponent methods
	virtual bool		          Init(CObjectIdHash, tinyxml2::XMLNode&);
	virtual void		          Deinit(void);
	virtual EMessageResult		HandleMessage(const CComponentMessage &);
	virtual EComponentTypeId	GetComponentTypeId(void);

  //members

private:
  //methods
  //members

}; //end class CCmpUserInput


#endif