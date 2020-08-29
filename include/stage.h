#pragma once
#include <bits/stdc++.h>
#include "renderwindow.h"
#include "grid.h"
#include "sheet.h"

class Stage{
private:
	int xGridSize = 4;
	int yGridSize = 3;
	int numCards;
	float ydivx = 46/35;
	SpriteSheet SET;
	SDL_Texture* chosen;
	int cardWidth = 46;
	Grid levelGrid;
	SDL_Rect rect;
	RenderWindow* window;
	std::vector<int> cards;
	std::vector<std::pair<int,int>> selected;

public:
	void init(RenderWindow *window);
	void redoGrid();
	void drawGrid();
	void cardClicked(int x, int y);
	bool checkIfOK();
	void resizeGrid(int dx);
};
