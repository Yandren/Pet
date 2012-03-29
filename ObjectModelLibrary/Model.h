#include <SDL.h>
#include <SDL/SDL_opengl.h>

class Model {

public:
	Model(SDL_Surface* tex) 
		: texture(tex){};
	virtual bool show();

private:
	SDL_Surface* texture;


};