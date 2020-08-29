#include <bits/stdc++.h>
#include "renderwindow.h"
#include "stage.h"
#include "grid.h"
#define OUT std::pair<int,int>{-1,-1}

void Stage::cardClicked(int x, int y,RenderWindow* window){
	auto position = levelGrid.getCell(x,y);
	if(position != OUT){ //to change
		auto pos = std::find (selected.begin(), selected.end(), position);
		if(pos == selected.end()){
			selected.push_back(position);
		}
		else{
			selected.erase(pos);
		}
		if(selected.size() == 3){
			if(checkIfOK()){
				while(!selected.empty()){
					int k = selected[0].second+ selected[0].first * 3;
					if(int(cards.size())>numCards && numCards == 12){
						cards[k] = cards[numCards];
						cards.erase(std::begin(cards) + numCards);
						selected.erase(std::begin(selected));
					}
					else{
						cards.erase(std::begin(cards) + selected[0].second+ selected[0].first * 3);
						selected.erase(std::begin(selected));
					}	
				}
				if(numCards > 12){
					numCards -=3;
					xGridSize --;
					redoGrid(window);
				}
			}
			else{
				selected.clear();
			}
		}
	}
	else{
		numCards+=3;
		xGridSize++;
		redoGrid(window);
	}
}
void Stage::init(RenderWindow* window){
	numCards = 12;
	chosen = window->loadTexture("res/chosen.png");
	SET.init(window->loadTexture("res/spriteStrip.png"),81,1);
	ydivx = 47.0/36.0;
	for(int i=0;i<81;i++)
		cards.push_back(i);
	std::shuffle(cards.begin(), cards.end(), std::random_device());
	
}
void Stage::drawGrid(RenderWindow* window){
	window->clear();
	SDL_SetRenderDrawColor(window->renderer, 120, 120, 120, 255);
	//window.render(0, 0, " SET", font32, SDL_Color{20,20,20});
	SDL_RenderFillRect(window->renderer, &rect);
	for(int i = 0; i<std::min(int(cards.size()),numCards);i++){
		window->renderGrid(i/3, i%3,SET.tex, &levelGrid, SET.access(cards[i] ,0));
	}
	for(auto i: selected){
		window->renderGrid(i.first, i.second,chosen, &levelGrid, SDL_Rect{0,0,36,47});
	}
	window->display();
}

void Stage::redoGrid(RenderWindow* window){
	levelGrid = window->createGrid(xGridSize, yGridSize, ydivx);
	rect = levelGrid.getSize();
}

bool Stage::checkIfOK(){
	int a = 0;
	int b = 1;
	for(int j=0;j<4;j++){
		for(int i = 0; i<3; i++){
			a += (cards[selected[i].first *3 + selected[i].second]/b)%3; 
		}
		if(a%3 != 0) return 0;
		b*=3;
	}
	return 1;
}
