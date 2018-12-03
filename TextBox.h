#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <string>
#include "Sprite.h"

class TextBox{

private:
    int x, y;
    Sprite sprite;

    string text;

    int scale;

public:

/*
 * description: constructor for TextBox
 * return: NA
 * precondition: instance of TextBox exists
 * postcondition: variables are set to input
 *
*/
    TextBox(int x, int y, string text, char[], ifstream&);

/*
 * description: constructor for TextBox
 * return: NA
 * precondition: instance of TextBox exists
 * postcondition: variables are set to input
 *
*/
    TextBox(char[], ifstream&);

/*
 * description: sets text to be displayed
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variable is set
 *
*/
    void setText(string text);

/*
 * description: sets x variable
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variable is set
 *
*/
    void set_x(int x);

/*
 * description: sets y variable
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variable is set
 *
*/
    void set_y(int y);

/*
 * description: sets location of text
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variables are set
 *
*/
    void setLocation(int, int);

/*
 * description: gets x variable
 * return: int
 * precondition: instance of TextBox exists
 * postcondition: x variable is returned
 *
*/
    int get_x();

/*
 * description: gets y variable
 * return: int
 * precondition: instance of TextBox exists
 * postcondition: y variable is returned
 *
*/
    int get_y();

/*
 * description: sets the scale of text
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: scale is set
 *
*/
    void setScale(int scale);

/*
 * description: draws to the screen
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: no variables changed, draws to screen
 *
*/
    void draw(SDL_Plotter& p);

};


#endif // TEXTBOX_H_INCLUDED
