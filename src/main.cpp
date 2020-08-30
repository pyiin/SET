#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

#include "renderwindow.h"
#include "grid.h"
#include "stage.h"
#define FPS 60
#define OUT std::pair<int,int>{-1,-1}

int cooldown;
RenderWindow window;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
bool gameRunning;
TTF_Font* font;
std::vector<SDL_Texture*> title;
Stage SETboard;
std::vector<std::pair<int,int>> cards;

void init(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window.create("SET", SCREEN_WIDTH, SCREEN_HEIGHT);
	SETboard.init(&window);
	SETboard.redoGrid();
	font = TTF_OpenFont("res/font.ttf", 128);
	title.push_back(window.loadTexture("res/title.png"));
	title.push_back(window.loadTexture("res/title2.png"));
	title.push_back(window.loadTexture("res/title3.png"));
	title.push_back(window.loadTexture("res/title4.png"));
	std::shuffle(title.begin(), title.end(), std::random_device());
	//SDL_SetTextureColorMod(test, 255, 10, 10);
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	cooldown = 20;
	srand((unsigned)time(0));
}


void eventLoop(){
	SDL_Event event;
 	while (SDL_PollEvent(&event)) 
 	{
    	switch (event.type) {
    		case SDL_QUIT:{
				gameRunning=0;
    	  		break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				if(cooldown > 0){
					continue;
				}
				if(event.button.button == SDL_BUTTON_LEFT)
					cooldown = SETboard.cardClicked(event.button.x, event.button.y);
				if(event.button.button == SDL_BUTTON_RIGHT)
					SETboard.resizeGrid(-1);
    	  		break;
			}
			case SDL_WINDOWEVENT:{
				SETboard.redoGrid();
				//levelGrid = window.createGrid(4,3);
    	  		break;
			}	
		}
	}
}

int main(int argc, char* args[]){
	init();
	gameRunning = 1;
	while(cooldown>0){
		window.clear();
		window.render(title[0]);
		cooldown--;
    	SDL_Delay(int(1000/FPS)); //delay
		window.display();
	}
	while(gameRunning){
		cooldown = cooldown ? cooldown - 1 : 0;
		if(cooldown == 1){
			SETboard.cooldownDown();
		}
    	eventLoop();
		SETboard.drawGrid();
    	SDL_Delay(int(1000/FPS)); //delay
	}

	window.cleanUp();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
