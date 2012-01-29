#ifndef OBJECT_H
#define OBJECT_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Object{

  public:
	Object( float x, float y, float xV, float yV)
		: x_pos(x), y_pos(y), xVel(xV), yVel(yV){};
	virtual ~Object(){};

    virtual void handle_input(SDL_Event *event) = 0;
	virtual void move() = 0;
	virtual void show() = 0;
	
  protected:

	//Fields
	float x_pos;
	float y_pos;
	float xVel;
	float yVel;

};



#endif