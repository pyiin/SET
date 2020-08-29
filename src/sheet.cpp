#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sheet.h"
#include "renderwindow.h"

void SpriteSheet::init(SDL_Texture* p_tex, int p_x, int p_y){
	tex = p_tex;
	xSize = p_x;
	ySize = p_y;
}


SDL_Rect SpriteSheet::access(int p_x, int p_y){
	int w;
	int h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	SDL_Rect src;
	src.y = p_y * h/ySize;
	src.x = p_x * w/xSize;
	src.w = w/xSize;
	src.h = h/ySize;
	return src;
}
