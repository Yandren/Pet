#include "CSquare.h"

CSquare::CSquare(float x, float y, float xV, float yV, SDL_Surface* screen, std::string model) 
  : IObject(10, 10, 0, 0, screen, model) {
  if(model.empty()){ 
	  model.assign(IObject::cwd.c_str()).append("/CSquare.bmp");
      IObject::model = new CModel(SDL_LoadBMP(model.c_str()));
	  CLog::Get().Write(GEN_CLog, "%s: model path: %s", __FUNCTION__, model.c_str());
      };
}

void CSquare::handle_input(SDL_Event *event) {

    if (event->type == SDL_KEYDOWN) {
        //Adjust the velocity
        switch (event->key.keysym.sym) {
            case SDLK_UP: yVel -= SQUARE_SPEED;
                break;
            case SDLK_DOWN: yVel += SQUARE_SPEED;
                break;
            case SDLK_LEFT: xVel -= SQUARE_SPEED;
                break;
            case SDLK_RIGHT: xVel += SQUARE_SPEED;
                break;
            default: break;
        }
    } else if (event->type == SDL_KEYUP) {
        //Adjust the velocity
        switch (event->key.keysym.sym) {
            case SDLK_UP: yVel += SQUARE_SPEED;
                //break;
            case SDLK_DOWN: yVel -= SQUARE_SPEED;
                break;
            case SDLK_LEFT: xVel += SQUARE_SPEED;
                break;
            case SDLK_RIGHT: xVel -= SQUARE_SPEED;
                break;
            default: break;
        }
		
    }
}

void CSquare::move() {
	
    if(tick++==TICK_TRIGGER){
	  yVel += SQUARE_SPEED;
	  tick = 0;
	}
    x_pos += xVel;

    //If the CSquare went too far
    if ((x_pos < 0) || (x_pos > SCREEN_WIDTH)) {
        x_pos -= xVel;
    }

    y_pos += yVel;

    //If the CSquare went too far
    if ((y_pos < 0) || (y_pos > SCREEN_HEIGHT)) {
        y_pos -= yVel;
    }

	yVel = xVel = 0;
}

void CSquare::show() {
	IObject::show();

}
