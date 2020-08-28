#pragma once
#include <bits/stdc++.h>


class Grid{
private:
	int size;
	int x;
	int y;
	int xOffset;
	int yOffset;
public:
	Grid();
	void init(int p_size, int p_x, int p_y, int p_Xoffset, int p_Yoffset);
	//void cellPrint(int p_x, int p_y, SDL_Texture* tex);
	void changeSize(int newSize, int p_Xoffset, int p_Yoffset);
	SDL_Rect getDest(int p_x, int p_y);
	SDL_Rect getSize();
	std::pair<int,int> getCell(int p_x, int p_y);
};
