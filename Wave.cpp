#include "Wave.h"

using namespace std;

Wave::Wave(char filename[], ifstream& inFile){

    sprite.loadImage(filename, inFile);

    for (int f = 0; f < sprite.getTotalFrames(); f++){

        columnLocations[f].resize(sprite.getWidth(f), 0);

    }

}

Sprite Wave::getSprite(){

    return sprite;

}

void Wave::setSpriteLocation(int x, int y){

    sprite.set_x(x);
    sprite.set_y(y);

}

void Wave::draw(SDL_Plotter& p){

    int cf = sprite.getCurrentFrame();

    int scale = sprite.getScale();

    int x = sprite.get_x(), y = sprite.get_y();

    int offx = sprite.getOffset(cf).x, offy = sprite.getOffset(cf).y;

    int px = sprite.mirrored() ? sprite.getWidth(cf)-1 : 0;

    for (int c = 0; c < sprite.getWidth(cf); c++){

        int py = columnLocations[cf][c];

        for (int r = 0; r < sprite.getHeight(cf); r++){

            plotSquare(x + (px + offx) * scale, y + (py + offy) * scale, scale,
                       sprite.getPixel(cf,c,r), p);

            py++;

        }

        px += sprite.mirrored() ? -1 : 1;

    }

}

void Wave::offsetColumn(int columnNumber, int y){

    columnLocations[sprite.getCurrentFrame()][columnNumber] = y;

}
