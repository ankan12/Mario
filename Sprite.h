#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <fstream>
#include "SDL_Plotter.h"
#include <vector>

using namespace std;

struct Color{

    int r, g, b;

    bool isEqualTo(const Color& color);

};

struct Point{

    int x, y;

};

class Sprite{

private:

    int x = 0, y = 0;
    int currentFrame = 0;
    int totalFrames = 1;
    int scale = 1;

    vector<Point> offset;

    vector<Color> colors;

    vector<char> characters;

    void plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p);

    Color colorFromCharacter(char input);

    bool isMirrored = false;

    vector<vector<vector<Color> > > pixels;

public:

    Sprite();

    Sprite(char filename[], ifstream& inFile);

    void loadImage(char filename[], ifstream& inFile);

    int get_x();
    int get_y();

    void set_x(int x);
    void set_y(int y);

    void setLocation(int x, int y);

    void nextFrame();

    void setCurrentFrame(int currentFrame);

    int getCurrentFrame();

    int getScale();

    void setScale(int);

    void setOffset(int frameNumber, int x, int y);

    int getHeight(int frameNumber);
    int getWidth(int frameNumber);

    void setMirrored(bool);

    Color getPixel(int frameNumber, int col, int row);

    int pixelsInFrame(int frameNumber);

    void draw(SDL_Plotter& p);

};

#endif // SPRITE_H_INCLUDED
