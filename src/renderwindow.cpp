#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

#include "renderwindow.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

RenderWindow::RenderWindow()
{

}

void RenderWindow::create(const char* p_title, int p_w, int p_h)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL; 
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;	
	return texture;
}

void RenderWindow::clear(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}


void RenderWindow::render(float p_x, float p_y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h); 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	int w;
	int h;
	SDL_QueryTexture(p_tex, NULL, NULL, &w, &h);
	int sizeX = windowWidth*1/2/w;
	int sizeY = windowHeight*1/2/h;
	int size = std::min(sizeX, sizeY);
	SDL_Rect dst = {windowWidth/2-size*w/2, windowHeight/2-size*h/2, size*w, size*h};
	SDL_Rect src = {0, 0, w, h};
	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}



void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

Grid RenderWindow::createGrid(int x, int y, float ydivx){
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	int sizeX = windowWidth*8/10/x;
	int sizeY = windowHeight*8/10/(y*ydivx);
	int size = std::min(sizeX, sizeY);
	Grid level;
	level.init(size, (int)(size*ydivx), x, y, (windowWidth - size*x)/2, (windowHeight - (int)(size*ydivx)*y)/2);
	return level;
}


void RenderWindow::renderGrid(int x, int y, SDL_Texture* p_tex, Grid* grd, SDL_Rect src){
	auto dst = grd->getDest(x,y);
	SDL_RenderCopy(renderer, p_tex, &src, &dst);
	//SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
	//SDL_RenderFillRect(renderer, &dst);  
}
