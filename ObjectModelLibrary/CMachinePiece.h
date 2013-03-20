#include "IObject.h"


class CMachinePiece : DynamiObject {

public:
	int health;
	int powerReq;

protected:
	int sector; // passed to MachinePiece, situates it on the model
	CMachinePiece* owner;

	//HexSkeleton
	//attachpoints

private:

};