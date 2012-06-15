#include "Object.h"


class MachinePiece : DynamicObject {

public:
	int health;
	int powerReq;

protected:
	int sector; // passed to MachinePiece, situates it on the model
	MachinePiece* owner;

	//HexSkeleton
	//attachpoints

private:

};