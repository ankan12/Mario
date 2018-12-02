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

public: //what do these do?

/*
 * description: constructor for Number
 * return: NA
 * precondition: instance of Number
 * postcondition: variables are set to input
 *
*/
    Number(char[], ifstream&);

/*
 * description: constructor for Number
 * return: void
 * precondition: instance of Number
 * postcondition: variables are set to input
 *
*/
    void setNumber(int);
    int getNumber();

    void setLocation(int, int);

    void draw(SDL_Plotter& p);

    Sprite& getSprite();

    void setScale(int);
    int getScale();

};

#endif // NUMBER_H_INCLUDED
