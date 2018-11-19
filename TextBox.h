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
    TextBox(int x, int y, string text, char[], ifstream&);

    TextBox(char[], ifstream&);

    void setText(string text);

    void set_x(int x);
    void set_y(int y);
    void setLocation(int, int);

    int get_x();
    int get_y();

    void setScale(int scale);

    void draw(SDL_Plotter& p);

};


#endif // TEXTBOX_H_INCLUDED
