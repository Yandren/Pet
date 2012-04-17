#ifndef SQUARE_H
#define	SQUARE_H

#include "Object.h"
#include "WinConstants.h"

const int SQUARE_SPEED = 5;

class Square : Object
{

    public:
    Square(float x, float y, float xV, float yV, SDL_Surface* screen, std::string model = "C:\\Users\\dragonerdriftr\\Documents\\Pet\\MainLoop\\Square.bmp");
	virtual ~Square(){};

    void handle_input(SDL_Event *event);
    void move();
    void show();
	
};


#endif	/* SQUARE_H */