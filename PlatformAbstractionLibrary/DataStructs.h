#ifndef __DATASTRUCTS_H
#define __DATASTRUCTS_H

#include "types.h"

class CHash
{
public:
	CHash();
	CHash(uint32_t hashValue);
	CHash(const char *pString);
	CHash(const CHash &rhs);
	CHash &operator=(const CHash &rhs);

	void Set(const uint32_t hash);

	bool IsValid() const;
	operator unsigned int()			{ return mHashValue; }

	const bool operator<(const CHash &rhs) const;
	const bool operator>(const CHash &rhs) const;
	const bool operator<=(const CHash &rhs) const;
	const bool operator>=(const CHash &rhs) const;
	const bool operator==(const CHash &rhs) const;
	const bool operator!=(const CHash &rhs) const;
private:
	uint32_t MakeHash(const char *pString);

	uint32_t mHashValue;
};


class COctree {

public:

	COctree() : 
	  NorthWestTop(NULL),
	  NorthWestBot(NULL),
	  NorthEastTop(NULL),
	  NorthEastBot(NULL),
      SouthWestTop(NULL),
	  SouthWestBot(NULL),
	  SouthEastTop(NULL),
	  SouthEastBot(NULL) {};


	static const int CAPACITY = 8;

	COctree* NorthWestTop;
	COctree* NorthWestBot;
	COctree* NorthEastTop;
	COctree* NorthEastBot;
    COctree* SouthWestTop;
	COctree* SouthWestBot;
	COctree* SouthEastTop;
	COctree* SouthEastBot;

private:

};

class CVector
{
public:
	CVector()	{}
	CVector(float x, float y, float z) : mX(x), mY(y), mZ(z)		{}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetZ() const { return mZ; }
	void SetX(float x) { mX = x; }
	void SetY(float y) { mY = y; }
	void SetZ(float z) { mZ = z; }
private:
	float mX, mY, mZ;
};

#endif