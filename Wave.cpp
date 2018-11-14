#include "Wave.h"

using namespace std;

Wave::Wave(){
}

Wave::Wave(char filename[], ifstream& inFile){

    sprite.loadImage(filename, inFile);

    resetColumnLocations();

}

Sprite& Wave::getSprite(){

    return sprite;

}

void Wave::setSpriteLocation(int x, int y){

    sprite.set_x(x);
    sprite.set_y(y);

}

void Wave::draw(SDL_Plotter& p){

    if (columnLocations.empty()){
        cout << "Column locations need to be initialized for Wave::draw"
        << endl;
        return;
    }

    int cf = sprite.getCurrentFrame();

    int scale = sprite.getScale();

    int x = sprite.get_x(), y = sprite.get_y();

    int offx = sprite.getOffset(cf).x, offy = sprite.getOffset(cf).y;

    int px = sprite.mirrored() ? sprite.getWidth(cf)-1 : 0;

    for (int c = 0; c < sprite.getWidth(cf); c++){

        int py = columnLocations[cf][c];

        for (int r = 0; r < sprite.getHeight(cf); r++, py++){

            Color color = sprite.getPixel(cf,c,r);

            if (color.r == -1){
                continue;
            }

            sprite.plotSquare(x + (px + offx) * scale, y + (py + offy) * scale,
                              scale, sprite.getPixel(cf,c,r), p);

        }

        px += sprite.mirrored() ? -1 : 1;

    }

}

void Wave::offsetColumn(int columnNumber, int y){

    columnLocations[sprite.getCurrentFrame()][columnNumber] = y;

}

void Wave::resetColumnLocations(){

    if (sprite.getTotalFrames() == 0){

        cout << "The sprite needs to be loaded for Wave::resetColumnLocations"
        << endl;
        return;

    }

    columnLocations.resize(sprite.getTotalFrames());

    for (int f = 0; f < sprite.getTotalFrames(); f++){

        columnLocations[f].resize(sprite.getWidth(f), 0);

    }

}

int Wave::numberOfColumns(int frameNumber){

    return columnLocations[frameNumber].size();

}
