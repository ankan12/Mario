#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include "Sprite.h"
#include "SDL_Plotter.h"

using namespace std;

class Wave{

private:

    vector<vector<int> > columnLocations;

    Sprite sprite;

public:

/*
 * description: constructor for the wave class
 * return: NA
 * precondition: instance of wave exists
 * postcondition: all variables initialized to input
 *
*/
    Wave(char filename[], ifstream& inFile);

/*
 * description: default constructor for the wave class
 * return: NA
 * precondition: instance of wave exists
 * postcondition: all variables initialized
 *
*/
    Wave();

/*
 * description: this function gets and passes a sprite by reference
 * return: sprite
 * precondition: wave and sprite exist
 * postcondition: sprite passed by reference
 *
*/
    Sprite& getSprite();

/*
 * description: sets the location of the sprite
 * return: void
 * precondition: instance of wave exists and sprite exists
 * postcondition: sprite x and y are set
 *
*/
    void setSpriteLocation(int, int);

/*
 * description: sets the y for the columns
 * return: void
 * precondition: instance of wave exists
 * postcondition: y variable set
 *
*/
    void offsetColumn(int columnNumber, int y);

/*
 * description: draws the sprite
 * return: void
 * precondition: instance of wave exists
 * postcondition: picture is drawn on the screen
 *
*/
    void draw(SDL_Plotter& p);

/*
 * description: resets the column x and y
 * return: void
 * precondition: instance of wave exists
 * postcondition: location variables reset
 *
*/
    void resetColumnLocations();

/*
 * description: returns the column locations
 * return: int
 * precondition: instance of wave exists
 * postcondition: nothing is changed
 *
*/
    int numberOfColumns(int frameNumber);

};




#endif // WAVE_H_INCLUDED
