#ifndef OBJECT_H
#define OBJECT_H
#include "pal.h"
#include <string>
#include <SDL/SDL.h>
#include "Model.h"
#include <cstdlib>

const int TICK_TRIGGER = 1;

class AABB{

public:
	AABB(Object* object){};
	~AABB(){};
private:


};


class Object{

  public:

	Object(float x, float y, float xV, float yV, SDL_Surface* screen, std::string modelStr = "C:\\Users\\dragonerdriftr\\Documents\\PetProject\\defaultNoAsset.bmp")
		: x_pos(x), 
		  y_pos(y), 
		  xVel(xV), 
		  yVel(yV), 
		  tick(0),
		  display(screen),
		  model(NULL){ try {model = new Model(SDL_LoadBMP(modelStr.c_str()));} 
	                   catch(std::exception &e){Log::Get().Write(GEN_LOG, "Exception: %s", e.what());}};
	virtual ~Object(){ delete model;};

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


class DynamicObject : Object {

};

class StaticObject : Object {

};
#endif