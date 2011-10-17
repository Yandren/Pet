
#ifndef SQUARE_H
#define	SQUARE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "WinConstants.h"

const int SQUARE_SPEED = 5;

class Square
{
    private:
    int x, y;
    int xVel, yVel;

    public:
    Square();

    void handle_input(SDL_Event *event);
    void move();
    void show();
};


#endif	/* SQUARE_H */

