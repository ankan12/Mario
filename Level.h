#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "SDL_Plotter.h"
#include "Block.h"
#include <fstream>
#include <vector>

class Level{

private:
    vector<Block> blocks;
    Sprite blockSprite;
    Sprite leftEdgeSprite;
    Sprite rightEdgeSprite;

    void placeBlock(int x, int y, Sprite& sprite);

public:

    Level();

    void draw(SDL_Plotter& p);

    void placeBlock(int x, int y);
    void placeBlock(int x, int y, BlockType type);

    void setBlockSprite(char[], ifstream&);
    void setLeftEdgeSprite(char[], ifstream&);
    void setRightEdgeSprite(char[], ifstream&);

    Block& getBlock(int index);

    Block& getBlock(int x, int y);

};

#endif // LEVEL_H_INCLUDED
