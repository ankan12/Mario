#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include <vector>
#include "block.h"
#include "CollisionBox.h"

class Platform{

private:

    int x, y;

    vector<Block> blocks;
    vector<int> columnLocations;

    CollisionBox cBox;

    bool frozen;

    bool blue;

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

    bool isBlue();

    void setBlue();

    void clearBlocks();

};

#endif // PLATFORM_H_INCLUDED
