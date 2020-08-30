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
	float ydivx;
	SpriteSheet SET;
	SDL_Texture* chosen;
	SDL_Texture* right;
	SDL_Texture* nothing;
	SDL_Texture* wrong;
	int cardWidth = 46;
	Grid levelGrid;
	SDL_Rect rect;
	RenderWindow* window;
	std::vector<int> cards;
	std::vector<std::pair<int,int>> selected;
	std::vector<std::pair<int,int>> goodCards;
	std::vector<std::pair<int,int>> badCards;

public:
	void init(RenderWindow *window);
	void redoGrid();
	void drawGrid();
	int cardClicked(int x, int y);
	bool checkIfOK();
	void resizeGrid(int dx);
	void cooldownDown();
};
