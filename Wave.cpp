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
#include "Wave.h"

using namespace std;

/*
 * description: default constructor for the wave class
 * return: NA
 * precondition: instance of wave exists
 * postcondition: all variables initialized
 *
*/
Wave::Wave(){
}

/*
 * description: constructor for the wave class
 * return: NA
 * precondition: instance of wave exists
 * postcondition: all variables initialized to input
 *
*/
Wave::Wave(char filename[], ifstream& inFile){

    sprite.loadImage(filename, inFile);

    resetColumnLocations();

}

/*
 * description: this function gets and passes a sprite by reference
 * return: sprite
 * precondition: wave and sprite exist
 * postcondition: sprite passed by reference
 *
*/
Sprite& Wave::getSprite(){

    return sprite;

}

/*
 * description: sets the location of the sprite
 * return: void
 * precondition: instance of wave exists and sprite exists
 * postcondition: sprite x and y are set
 *
*/
void Wave::setSpriteLocation(int x, int y){

    sprite.set_x(x);
    sprite.set_y(y);

}

/*
 * description: draws the sprite
 * return: void
 * precondition: instance of wave exists
 * postcondition: picture is drawn on the screen
 *
*/
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

/*
 * description: sets the y for the columns
 * return: void
 * precondition: instance of wave exists
 * postcondition: y variable set
 *
*/
void Wave::offsetColumn(int columnNumber, int y){

    columnLocations[sprite.getCurrentFrame()][columnNumber] = y;

}

/*
 * description: resets the column x and y
 * return: void
 * precondition: instance of wave exists
 * postcondition: location variables reset
 *
*/
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

/*
 * description: returns the column locations
 * return: int
 * precondition: instance of wave exists
 * postcondition: nothing is changed
 *
*/
int Wave::numberOfColumns(int frameNumber){

    return columnLocations[frameNumber].size();

}
