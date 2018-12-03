#ifndef DRAWINGFUNCTIONS_H_INCLUDED
#define DRAWINGFUNCTIONS_H_INCLUDED

#include "SDL_Plotter.h"
#include "Sprite.h"

void plotSquare(int x, int y, int scale, int r, int g, int b, SDL_Plotter& p);
void drawBlackBackground(int screenWidth, int screenHeight, SDL_Plotter& p);
void horizontalTile(Sprite& sprite, int startX, int endX, SDL_Plotter& p);
void drawLives(Sprite&,int,int,int,SDL_Plotter&);
#endif // DRAWINGFUNCTIONS_H_INCLUDED
