#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//#include "entity.h"
#include "grid.h"

class RenderWindow{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	RenderWindow();
	void create(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void clear(int r=90, int g=90, int b=90, int a=255);
	//void render(Entity& p_entity);
	void render(float p_x, float p_y, SDL_Texture* p_tex);
	void render(SDL_Texture* p_tex);
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void display();
	void cleanUp();
	Grid createGrid(int x, int y, float ydivx = 1);
	void renderGrid(int x, int y, SDL_Texture* p_tex, Grid* grd, SDL_Rect src);
};
