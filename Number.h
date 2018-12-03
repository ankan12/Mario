#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED

#include "SDL_Plotter.h"
#include "Sprite.h"
#include <vector>

class Number{

private:
    int number;
    Sprite sprite;
    int x, y;
    vector<int> digits;
    int scale;

public:

/*
 * description: constructor for Number
 * return: NA
 * precondition: instance of Number
 * postcondition: variables are set to input
 *
*/
    Number(char[], ifstream&);

/*
 * description: sets and scales number
 * return: void
 * precondition: instance of Number and int is passed in
 * postcondition: number is resized and set
 *
*/
    void setNumber(int);

/*
 * description: returns number
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int getNumber();

/*
 * description: sets location to output number
 * return: void
 * precondition: class instance exists and two ints are passed
 * postcondition: x and y are set for location
 *
*/
    void setLocation(int, int);

/*
 * description: uses SDL to draw to the screen
 * return: void
 * precondition: class instance exists and plotter is passed in
 * postcondition: nothing is changed, input drawn to screen
 *
*/
    void draw(SDL_Plotter& p);

/*
 * description: gets sprite and passes it by reference
 * return: Sprite
 * precondition: class instance exists
 * postcondition: sprite is gotten and passed by reference
 *
*/
    Sprite& getSprite();

/*
 * description: sets the scale variable =
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: scale variable is set
 *
*/
    void setScale(int);

/*
 * description: gets the scale variable
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int getScale();

};

#endif // NUMBER_H_INCLUDED
