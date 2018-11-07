#include "DrawingFunctions.h"

void plotSquare(int x, int y, int scale, int r, int g, int b, SDL_Plotter& p){

    for (int c = 0; c < scale; c++){

        for (int c2 = 0; c2 < scale; c2++){

            p.plotPixel(x + c2, y + c, r, g, b);
        }
    }
}
