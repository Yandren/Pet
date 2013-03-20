#ifndef SQUARE_H
#define	SQUARE_H

#include "IObject.h"
#include "WinConstants.h"

const int SQUARE_SPEED = 5;

class CSquare : IObject
{

    public:
    CSquare(float x, float y, float xV, float yV, SDL_Surface* screen, std::string model = "");
	virtual ~CSquare(){};

    void handle_input(SDL_Event *event);
    void move();
    void show();
	
};


#endif	/* SQUARE_H */