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

    Wave();

    Sprite& getSprite();

    void setSpriteLocation(int, int);

    void offsetColumn(int columnNumber, int y);

    void draw(SDL_Plotter& p);

    void resetColumnLocations();

    int numberOfColumns(int frameNumber);

};




#endif // WAVE_H_INCLUDED
