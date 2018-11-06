#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <fstream>
#include "SDL_Plotter.h"
#include <vector>

using namespace std;

struct Color{

    int r, g, b;

    bool isEqualTo(Color color);

};

struct Point{

    int x, y;

};

class Sprite{

private:

    int x = 0, y = 0;
    vector<vector<Color> > frames;
    int currentFrame = 0;
    int totalFrames = 1;
    int scale = 1;

    vector<Point> offset;

    vector<Color> colors;

    vector<char> characters;

    void plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p);

    Color colorFromCharacter(char input);

public:

    Sprite();

    Sprite(char filename[], ifstream& inFile);

    void loadImage(char filename[], ifstream& inFile);
    void draw(SDL_Plotter& plotter);

    int getx();
    int gety();

    void set_x(int x);
    void set_y(int y);

    void setLocation(int x, int y);

    void nextFrame();

    void setCurrentFrame(int currentFrame);

    int getCurrentFrame();

    int getScale();

    void setScale(int);

    void setOffset(int frameNumber, int x, int y);

};

#endif // SPRITE_H_INCLUDED
