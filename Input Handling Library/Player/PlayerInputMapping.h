#ifndef __PLAYERINPUTMAPPING_H
#define __PLAYERINPUTMAPPING_H

#include "IInputMapping.h"
#include <functional>

//Forward Declaration
namespace tinyxml2 { class XMLNode; };

//This is where you need to define specific types of mapping
//Depending on what you want the game to do.
//some defaults are included, standard for an engine

//Ideally, most of this will be replaced by lua scripting, depending on performance
class CMovementAction : public IAction
{

 public:
 CMovementAction(tinyxml2::XMLNode & node);
 CMovementAction();

 bool evoke();

};




#endif