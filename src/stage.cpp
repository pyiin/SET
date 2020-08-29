#include <bits/stdc++.h>
#include "renderwindow.h"
#include "stage.h"
#include "grid.h"
#define OUT std::pair<int,int>{-1,-1}

void Stage::resizeGrid(int dx){
	if(xGridSize + dx > 0 && (xGridSize+dx)*yGridSize<=24){
		numCards +=dx*yGridSize;
		xGridSize += dx;
		selected.clear();
		redoGrid();
	}
}

void Stage::cooldownDown(){
	while(!goodCards.empty()){
		int k = goodCards[0].second+ goodCards[0].first * yGridSize;
		if(int(cards.size())>numCards && numCards == 12){
			cards[k] = cards[numCards];
			cards.erase(std::begin(cards) + numCards);
			goodCards.erase(std::begin(goodCards));
		}
		else{
			cards.erase(std::begin(cards) + goodCards[0].second+ goodCards[0].first * yGridSize);
			goodCards.erase(std::begin(goodCards));
		}	
	}
	if(numCards > 12){
		numCards -=3;
		xGridSize = (numCards+2)/yGridSize;
		redoGrid();
	}
	goodCards.clear();
	badCards.clear();
}


int Stage::cardClicked(int x, int y){
	auto position = levelGrid.getCell(x,y);
	if(position != OUT){ //to change
		auto pos = std::find (selected.begin(), selected.end(), position);
		if(pos == selected.end()){
			if(position.first*yGridSize + position.second < std::min(numCards, int(cards.size())))
				selected.push_back(position);
		}
		else{
			selected.erase(pos);
		}
		if(selected.size() == 3){
			if(checkIfOK()){
				goodCards = selected;
				selected.clear();
				return 30;
			}
			else{
				badCards = selected;
				selected.clear();
				return 30;
			}
		}
	}
	else
		resizeGrid(1);
	return 0;
}


void Stage::init(RenderWindow* p_window){
	window = p_window;
	numCards = xGridSize * yGridSize;
	chosen = window->loadTexture("res/chosen.png");
	right = window->loadTexture("res/right.png");
	wrong = window->loadTexture("res/wrong.png");
	SET.init(window->loadTexture("res/spriteStrip.png"),81,1);
	ydivx = 47.0/36.0;
	for(int i=0;i<81;i++)
		cards.push_back(i);
	std::shuffle(cards.begin(), cards.end(), std::random_device());
	
}


void Stage::drawGrid(){
	window->clear();
	SDL_SetRenderDrawColor(window->renderer, 120, 120, 120, 255);
	//window.render(0, 0, " SET", font32, SDL_Color{20,20,20});
	SDL_RenderFillRect(window->renderer, &rect);
	for(int i = 0; i<std::min(int(cards.size()),numCards);i++){
		window->renderGrid(i/yGridSize, i%yGridSize,SET.tex, &levelGrid, SET.access(cards[i] ,0));
	}
	for(auto i: selected){
		window->renderGrid(i.first, i.second,chosen, &levelGrid, SDL_Rect{0,0,36,47});
	}
	for(auto i: goodCards){
		window->renderGrid(i.first, i.second,right, &levelGrid, SDL_Rect{0,0,36,47});
	}
	for(auto i: badCards){
		window->renderGrid(i.first, i.second,wrong, &levelGrid, SDL_Rect{0,0,36,47});
	}
	window->display();
}


void Stage::redoGrid(){
	levelGrid = window->createGrid(xGridSize, yGridSize, ydivx);
	rect = levelGrid.getSize();
}


bool Stage::checkIfOK(){
	int a = 0;
	int b = 1;
	for(int j=0;j<4;j++){
		for(int i = 0; i<3; i++){
			a += (cards[selected[i].first * yGridSize + selected[i].second]/b)%3; 
		}
		if(a%3 != 0) return 0;
		b*=3;
	}
	return 1;
}
