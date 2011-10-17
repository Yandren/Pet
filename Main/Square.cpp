#include "Square.h"

Square::Square() : x(10), y(10), xVel(0), yVel(0) {
}

void Square::handle_input(SDL_Event *event) {

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
                break;
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

void Square::move() {

    x += xVel;

    //If the square went too far
    if ((x < 0) || (x > SCREEN_WIDTH)) {
        x -= xVel;
    }

    y += yVel;

    //If the square went too far
    if ((y < 0) || (y > SCREEN_HEIGHT)) {
        y -= yVel;
    }
}

void Square::show() {
    //Move to offset
    glTranslatef(x, y, 0);
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
}
