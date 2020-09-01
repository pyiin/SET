#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

#include "grid.h"
#include "renderwindow.h"

Grid::Grid(){

}

void Grid::init(int p_sizeX, int p_sizeY, int p_x, int p_y, int p_Xoffset, int p_Yoffset){
	sizeX = p_sizeX;
	sizeY = p_sizeY;
	x = p_x;
	y = p_y;
	xOffset = p_Xoffset;
	yOffset = p_Yoffset;
	//std::cout<<"x:"<<x<<" y:"<<y<<" size:"<<size<<" offset:"<<xOffset<<" "<<yOffset;
}

SDL_Rect Grid::getDest(int p_x, int p_y){
	SDL_Rect dst;
	dst.x = xOffset + p_x*sizeX;
	dst.y = yOffset + p_y*sizeY;
	dst.w = sizeX;
	dst.h = sizeY;
	return dst;
}

std::pair<int,int> Grid::getCell(int p_x, int p_y){
	if(!(p_x>xOffset && p_x<xOffset + sizeX*x)) return std::make_pair(-1,-1);
	if(!(p_y>yOffset && p_y<yOffset + sizeY*y)) return std::make_pair(-1,-1);
	std::pair<int,int> ans = {(p_x-xOffset)/sizeX, (p_y-yOffset)/sizeY};
	return ans;
}
SDL_Rect Grid::getSize(){
	SDL_Rect dst;
	dst.x = xOffset;
	dst.y = yOffset;
	dst.w = x*sizeX;
	dst.h = y*sizeY;
	return dst;
}
