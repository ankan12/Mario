#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "Sprite.h"
#include "CollisionBox.h"
#include "SDL_Plotter.h"
#include "Wave.h"
#include <fstream>

enum BlockType {leftEdge, middle, rightEdge};

class Block{

private:
    CollisionBox cBox;
    int x, y;
    int width, height;
    BlockType type = middle;
    Wave wave;
    bool icy = false;

public:
    Block(int x, int y, int width, int height);

    Block(int x, int y, int width, int height, BlockType type);

    void draw(SDL_Plotter& p);

    void offsetColumn(int columnNumber, int y);

    Wave& getWave();

    bool isIcy();

    void setIcy(bool value);

    int get_x();
    int get_y();

};

#endif // BLOCK_H_INCLUDED
