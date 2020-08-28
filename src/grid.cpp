#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

#include "grid.h"
#include "renderwindow.h"

Grid::Grid(){

}

void Grid::init(int p_size, int p_x, int p_y, int p_Xoffset, int p_Yoffset){
	size = p_size;
	x = p_x;
	y = p_y;
	xOffset = p_Xoffset;
	yOffset = p_Yoffset;
	//std::cout<<"x:"<<x<<" y:"<<y<<" size:"<<size<<" offset:"<<xOffset<<" "<<yOffset;
}

//void Grid::cellPrint(int p_x, int p_y, SDL_Texture* tex){
//	
//}
void Grid::changeSize(int newSize, int p_Xoffset, int p_Yoffset){
	size = newSize;
	xOffset = p_Xoffset;
	yOffset = p_Yoffset;
}

SDL_Rect Grid::getDest(int p_x, int p_y){
	SDL_Rect dst;
	dst.x = xOffset + p_x*size;
	dst.y = yOffset + p_y*size;
	dst.w = size;
	dst.h = size;
	return dst;
}

std::pair<int,int> Grid::getCell(int p_x, int p_y){
	if(!(p_x>xOffset && p_x<xOffset + size*x)) return std::make_pair(-1,-1);
	if(!(p_y>yOffset && p_y<yOffset + size*y)) return std::make_pair(-1,-1);
	std::pair<int,int> ans = {(p_x-xOffset)/size, (p_y-yOffset)/size};
	return ans;
}
SDL_Rect Grid::getSize(){
	SDL_Rect dst;
	dst.x = xOffset;
	dst.y = yOffset;
	dst.w = x*size;
	dst.h = y*size;
	return dst;
}
