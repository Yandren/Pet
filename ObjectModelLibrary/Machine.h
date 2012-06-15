#include "Object.h"
#include "MachinePiece.h"
#include <vector>

class Machine : DynamicObject{

public:

	class DamageMap {


	};



	std::vector<MachinePiece *> pieces;

	//Damage Map
	//  -model should be "dynamically generated", split into sectors
	//  - tell lua what the pieces are, have them bolted on to a model, then bring it back?

private:

};