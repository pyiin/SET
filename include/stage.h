#pragma once
#include <bits/stdc++.h>
#include "renderwindow.h"
#include "grid.h"

class Stage{
private:
	int xGridSize = 4;
	int yGridSize = 3;
	float ydivx = 46/35;
	SDL_Texture* SET;
	int cardWidth = 46;
	Grid levelGrid;
	SDL_Rect rect;
	std::vector<std::pair<int,int>> cards;

public:
	void init(RenderWindow *window);
	void redoGrid(RenderWindow *window);
	void drawGrid(RenderWindow *window);
	void cardClicked(int x, int y);
	
};
