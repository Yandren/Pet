#ifndef TYPES_H
#define TYPES_H

class Octree {

public:

	Octree() : 
	  NorthWestTop(NULL),
	  NorthWestBot(NULL),
	  NorthEastTop(NULL),
	  NorthEastBot(NULL),
      SouthWestTop(NULL),
	  SouthWestBot(NULL),
	  SouthEastTop(NULL),
	  SouthEastBot(NULL) {};


	static const int CAPACITY = 8;

	Octree* NorthWestTop;
	Octree* NorthWestBot;
	Octree* NorthEastTop;
	Octree* NorthEastBot;
    Octree* SouthWestTop;
	Octree* SouthWestBot;
	Octree* SouthEastTop;
	Octree* SouthEastBot;

private:

};

#endif