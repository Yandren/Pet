#ifndef __PLAYERINPUTMAPPING_H
#define __PLAYERINPUTMAPPING_H

#include "IInputIntent.h"
#include "PlayerInput_types.h"
#include <functional>
#include <string>
#include "pal.h"

//Forward Declaration
namespace tinyxml2 { class XMLNode; };

//This is where you need to define specific types of mapping
//Depending on what you want the game to do.
//some defaults are included, standard for an engine

//Ideally, most of this will be replaced by lua scripting, depending on performance
class CIntentToObjectsMapping : public IInputIntent
{

 public:
// CIntentToObjectsMapping(std::string objName, tinyxml2::XMLNode & node);
 CIntentToObjectsMapping(std::string objName);

 bool evoke();

 private:
 CObjectIdHash mObjName;
 std::string mIntentName;
};

class CMouseToObjectsMapping : public IInputIntent
{
public:
 CMouseToObjectsMapping();

 bool evoke();

};



#endif