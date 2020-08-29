#include "renderwindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class SpriteSheet{
private:
	int xSize;
	int ySize;
public:
	SDL_Texture* tex;
	SDL_Rect access(int p_x, int p_y);
	void init(SDL_Texture* p_tex, int p_x, int p_y);
};
