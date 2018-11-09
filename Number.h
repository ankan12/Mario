#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED

#include "SDL_Plotter.h"
#include "Sprite.h"
#include <vector>

class Number{

private:
    int number = 0;
    Sprite sprite;
    int x = 0, y = 0;
    vector<int> digits;
    int scale = 1;

public:

    Number(char[], ifstream&);

    void setNumber(int);
    int getNumber();

    void setLocation(int, int);

    void draw(SDL_Plotter& p);

    Sprite& getSprite();

    void setScale(int);
    int getScale();

};

#endif // NUMBER_H_INCLUDED
