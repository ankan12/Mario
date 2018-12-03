/*Authors:
Anupama Kannan
Brandon Alcaraz
Miranda Montroy
Samuel Kim
Thomas Cho
*Assignment Title: Mario Bros.
*Assignment Description: Recreate Mario Bros.
*Due Date 12/2/2018
*Date Created 11/4/2018
*Date Last Modified 12/2/2018
*/
#ifndef DRAWINGFUNCTIONS_H_INCLUDED
#define DRAWINGFUNCTIONS_H_INCLUDED

#include "SDL_Plotter.h"
#include "Sprite.h"



/*
 * description: draws a square
 * return: void
 * precondition: six ints and a plotter are passed in
 * postcondition: square drawn to screen
 *
*/
void plotSquare(int x, int y, int scale, int r, int g, int b, SDL_Plotter& p);

/*
 * description: draws the black background
 * return: void
 * precondition: two ints and a plotter passed in
 * postcondition: black background drawn to screen
 *
*/
void drawBlackBackground(int screenWidth, int screenHeight, SDL_Plotter& p);

/*
 * description: draws horizontal tiles
 * return: void
 * precondition: passed in sprite, two ints, and a plotter
 * postcondition: tiles drawn to screen
 *
*/
void horizontalTile(Sprite& sprite, int startX, int endX, SDL_Plotter& p);
void drawLives(Sprite&,int,int,int,SDL_Plotter&);
#endif // DRAWINGFUNCTIONS_H_INCLUDED
