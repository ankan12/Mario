#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "SDL_Plotter.h"
#include "Block.h"
#include <fstream>
#include <vector>

class Platform{

private:

    int x, y;

    vector<Block> blocks;
    vector<int> columnLocations;

    CollisionBox cBox;

    bool frozen = false;

public:

    Platform(int x, int y);

    Block& getBlock(int index);

    int numOfBlocks();

    int numOfColumns();

    int get_x();

    int get_y();

    void addBlock(Sprite& sprite);

    vector<int>& getColLocations();

    CollisionBox& getCollisionBox();

    bool isFrozen();

    void setFrozen();

};

class Level{

private:
    vector<Platform> platforms;
    Sprite blockSprite;
    Sprite leftEdgeSprite;
    Sprite rightEdgeSprite;

public:

    Level();

    void draw(SDL_Plotter& p);

    void placePlatform(int x, int y, int numOfBlocks);

    void setBlockSprite(char[], ifstream&, int scale);
    void setLeftEdgeSprite(char[], ifstream&, int scale);
    void setRightEdgeSprite(char[], ifstream&, int scale);

    bool containsEdgeSprites();

    Sprite& getSprite();
    Sprite& getSprite(BlockType type);

    int numOfPlatforms();

    Platform& getPlatform(int index);

};

#endif // LEVEL_H_INCLUDED
