/*Authors:
Anupama Kannan
Brandon Alcaraz
Miranda Montroy
Samuel Kim
Thomas Cho
*Assignment Title: Mario Bros.
*Assignment Description: Recreate Mario Bros.
*Due Date 12/2/2018
*Date Created 11/4/2018
*Date Last Modified 12/2/2018
*/
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
