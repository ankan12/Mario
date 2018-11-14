#include "DrawingFunctions.h"
#include "Sprite.h"
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

void horizontalTile(Sprite& sprite, int startX, int endX, SDL_Plotter& p){

    int cf = sprite.getCurrentFrame();

    sprite.set_x(startX);

    while (!(sprite.get_x() + sprite.getWidth(cf) > endX)){

        sprite.draw(p);
        sprite.set_x(sprite.get_x() + sprite.getWidth(cf));

    }
    sprite.set_xCrop(endX - sprite.getWidth(cf));
    sprite.draw(p);

}
