#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <SDL/SDL.h>
#include "Model.h"
#include <cstdlib>

const int TICK_TRIGGER = 75;

class Object{

  public:

	Object(float x, float y, float xV, float yV, SDL_Surface* screen, std::string modelStr = "defaultNoAsset.bmp")
		: x_pos(x), 
		  y_pos(y), 
		  xVel(xV), 
		  yVel(yV), 
		  tick(0),
		  display(screen),
		  model(NULL){ printf( "returned: %d", system("dir")); model = new Model(SDL_LoadBMP(modelStr.c_str()));};
	virtual ~Object(){};

    virtual void handle_input(SDL_Event *event) = 0;
	virtual void move() = 0;
	virtual void show() { model->show(x_pos, y_pos, display); };
	
  protected:

	//Fields
	float x_pos;
	float y_pos;
	float xVel;
	float yVel;
	int tick;
	Model* model;
	SDL_Surface* display;

};



#endif