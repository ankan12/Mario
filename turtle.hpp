#ifndef TURTLE_HPP
#define TURTLE_HPP

#include<vector>
#include "SDL_Plotter.h"

using namespace std;

struct Turt
{
    int x;
    int y;
    int a;
    int b;
    int c;

};

class Turtle{

    int x, y;

    vector<vector<Turt> > images;

    int image;

    Turtle();

    void setLocation(int, int);

    void setImage(int image);

    void draw(SDL_Plotter& p);

//    Turt image(int i, int j);

};



#endif // TURTLE_HPP
