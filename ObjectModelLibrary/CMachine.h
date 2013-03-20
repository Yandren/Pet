#include "IObject.h"
#include "CMachinePiece.h"
#include <vector>

class CMachine : DynamiObject{

public:

	class DamageMap {


	};



	std::vector<CMachinePiece *> pieces;

	//Damage Map
	//  -model should be "dynamically generated", split into sectors
	//  - tell lua what the pieces are, have them bolted on to a model, then bring it back?

private:

};