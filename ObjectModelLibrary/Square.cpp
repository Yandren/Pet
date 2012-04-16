#include "Square.h"

Square::Square(float x, float y, float xV, float yV, SDL_Surface* screen, std::string model) 
  : Object(10, 10, 0, 0, screen, model) 
{}

void Square::handle_input(SDL_Event *event) {

    if (event->type == SDL_KEYDOWN) {
        //Adjust the velocity
        switch (event->key.keysym.sym) {
            //case SDLK_UP: yVel -= SQUARE_SPEED;
              //  break;
            case SDLK_DOWN: yVel += SQUARE_SPEED;
                break;
            case SDLK_LEFT: xVel -= SQUARE_SPEED;
                break;
            case SDLK_RIGHT: xVel += SQUARE_SPEED;
                break;
            default: break;
        }
    } /*else if (event->type == SDL_KEYUP) {
        //Adjust the velocity
        switch (event->key.keysym.sym) {
            //case SDLK_UP: yVel += SQUARE_SPEED;
                //break;
            case SDLK_DOWN: yVel -= SQUARE_SPEED;
                break;
            case SDLK_LEFT: xVel += SQUARE_SPEED;
                break;
            case SDLK_RIGHT: xVel -= SQUARE_SPEED;
                break;
            default: break;
        }
		
    }*/
}

void Square::move() {
	
	if(tick++==TICK_TRIGGER){
	  yVel += SQUARE_SPEED;
	  tick = 0;
	  }

    x_pos += xVel;

    //If the square went too far
    if ((x_pos < 0) || (x_pos > SCREEN_WIDTH)) {
        x_pos -= xVel;
    }

    y_pos += yVel;

    //If the square went too far
    if ((y_pos < 0) || (y_pos > SCREEN_HEIGHT)) {
        y_pos -= yVel;
    }

	yVel = xVel = 0;
}

void Square::show() {
    //Move to offset
    /*glTranslatef(x_pos, y_pos, 0);
    glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		//glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f,  1.0f);
		//glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 1.0f, -1.0f,  1.0f);
		//glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.0f,  1.0f,  1.0f);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		//glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, -1.0f);
		//glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(-1.0f,  1.0f, -1.0f);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f( 1.0f,  1.0f, -1.0f);
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f,  1.0f, -1.0f);
		//glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f,  1.0f,  1.0f);
		//glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 1.0f,  1.0f,  1.0f);
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f( 1.0f, -1.0f, -1.0f);
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		//glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		//glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.0f,  1.0f, -1.0f);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f( 1.0f,  1.0f,  1.0f);
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		//glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, -1.0f);
		//glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f,  1.0f);
		//glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(-1.0f,  1.0f,  1.0f);
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();


    glLoadIdentity();
	*/


}
