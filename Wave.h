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
    Wave(char filename[], ifstream& inFile);

    Sprite getSprite();

    void setSpriteLocation(int, int);

    void offsetColumn(int columnNumber, int y);

    void draw(SDL_Plotter& p);

};




#endif // WAVE_H_INCLUDED
