#ifndef OBJECT_H
#define OBJECT_H
#include "pal.h"
#include <string>
#include <SDL/SDL.h>
#include "CModel.h"
#include <cstdlib>

const int TICK_TRIGGER = 1;

typedef	CHash CObjectIdHash;


class IObject{

  public:

	IObject(float x, float y, float xV, float yV, SDL_Surface* screen, std::string modelStr = "")
		: x_pos(x), 
		  y_pos(y), 
		  xVel(xV), 
		  yVel(yV), 
		  tick(0),
		  display(screen),
		  model(NULL){ try {
			             cwd.assign(getCWD());
			             if(modelStr.empty()) modelStr.assign(cwd).append("/defaultNoAsset.bmp");
			             model = new CModel(SDL_LoadBMP(modelStr.c_str()));
	                     CLog::Get().Write(GEN_CLog, "model path: %s", modelStr.c_str());}
	                   catch(std::exception &e){CLog::Get().Write(GEN_CLog, "Exception: %s", e.what());}};
	virtual ~IObject(){ delete model;};

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
	CModel* model;
	SDL_Surface* display;
	string cwd;

};

class AABB{

public:
	AABB(IObject* object){};
	~AABB(){};
private:


};


class DynamiObject : IObject {

};

class StatiObject : IObject {

};
#endif