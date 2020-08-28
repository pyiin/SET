#include "renderwindow.h"
#include "stage.h"
#include "grid.h"
#define OUT std::pair<int,int>{-1,-1}

void Stage::cardClicked(int x, int y){
	auto position = levelGrid.getCell(x,y);
	if(position != OUT){ //to change
		auto pos = std::find (cards.begin(), cards.end(), position);
		if(pos == cards.end()){
			cards.push_back(position);
		}
		else{
			cards.erase(pos);
		}
	}
}
void Stage::init(RenderWindow* window){
	//SET = window->loadTexture("res/spriteStrip.png");
	SET = window->loadTexture("res/one.png");
}
void Stage::drawGrid(RenderWindow* window){
	window->clear();
	SDL_SetRenderDrawColor(window->renderer, 120, 120, 120, 255);
	//window.render(0, 0, " SET", font32, SDL_Color{20,20,20});
	SDL_RenderFillRect(window->renderer, &rect);
	for(auto i: cards){
		window->renderGrid(i.first, i.second, SET, &levelGrid);
	}
	window->display();
}

void Stage::redoGrid(RenderWindow* window){
	levelGrid = window->createGrid(xGridSize, yGridSize, ydivx);
	rect = levelGrid.getSize();
}
