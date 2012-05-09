#include <SDL.h>
#include <SDL/SDL_opengl.h>

class Model {

public:
	Model(SDL_Surface* tex) //add SDL_SetColorKey color param here for background color to ignore when drawing 
		: texture(tex){};
	virtual bool show(float toDrawX, float toDrawY, SDL_Surface* screen);

private:
	SDL_Surface* texture;

};