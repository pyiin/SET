#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>

#include "renderwindow.h"
#include "grid.h"
#define FPS 60
#define OUT std::pair<int,int>{-1,-1}

RenderWindow window;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
bool gameRunning;
TTF_Font* font32;
SDL_Texture* test;
Grid levelGrid;
std::vector<std::pair<int,int>> cards;
SDL_Rect rect;

void init(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window.create("Test", SCREEN_WIDTH, SCREEN_HEIGHT);
	font32 = TTF_OpenFont("res/cocogoose.ttf", 32);
	test = window.loadTexture("res/one.png");

	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	levelGrid = window.createGrid(4,3);

	srand((unsigned)time(0));
}

void gameLoop(){
	SDL_Event event;
 	while (SDL_PollEvent(&event)) 
 	{
    	switch (event.type) {
    		case SDL_QUIT:{
				gameRunning=0;
    	  		break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				if(event.button.button != SDL_BUTTON_LEFT) continue;
				auto position = levelGrid.getCell(event.button.x, event.button.y);
				if(position != OUT) 
					cards.push_back(position);
    	  		break;
			}
			case SDL_WINDOWEVENT:{
				levelGrid = window.createGrid(4,3);
				rect = levelGrid.getSize();
    	  		break;
			}	
		}
	}
}


int main(int argc, char* args[]){
	init();
	rect = levelGrid.getSize();
	gameRunning = 1;
	while(gameRunning){
		window.clear();
		//window.render(test);
    	gameLoop();
		//SDL_Rect a= {1390,970,86,86};
		SDL_SetRenderDrawColor(window.renderer, 120, 120, 120, 255);
		//SDL_RenderFillRect(window.renderer, &a);
		SDL_RenderFillRect(window.renderer, &rect);
		for(auto i: cards){
			window.renderGrid(i.first, i.second, test, &levelGrid);
		}
		window.display();
    	SDL_Delay(int(1000/FPS)); //delay
	}

	window.cleanUp();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
