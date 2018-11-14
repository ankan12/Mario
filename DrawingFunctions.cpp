#include "DrawingFunctions.h"

void plotSquare(int x, int y, int scale, int r, int g, int b, SDL_Plotter& p){

    for (int c = 0; c < scale; c++){

        for (int c2 = 0; c2 < scale; c2++){

            p.plotPixel(x + c2, y + c, r, g, b);
        }
    }
}

void drawBlackBackground(int screenWidth, int screenHeight, SDL_Plotter& p){

    for (int y = 0; y < screenHeight; y++){

        for (int x = 0; x < screenHeight; x++){

            p.plotPixel(x, y, 0, 0, 0);

        }

    }

}
