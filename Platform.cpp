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
#include "Platform.h"



/*
 * description: constructor for Platform
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
Platform::Platform(int x, int y){

    this->x = x;
    this->y = y;

    frozen = false;

}

/*
 * description: gets x variable
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Platform::get_x(){

    return x;

}

/*
 * description: gets y variable
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Platform::get_y(){

    return y;

}

/*
 * description: gets and passes box by reference
 * return: Block
 * precondition: class instance exists and int passed in
 * postcondition: block is passed by reference
 *
*/
Block& Platform::getBlock(int index){

    return blocks[index];

}

/*
 * description: gets the number of blocks
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Platform::numOfBlocks(){

    return blocks.size();

}

/*
 * description: adds a block to save pixels into
 * return: void
 * precondition: class instance exists and header files are linked
 * postcondition: sprite has been added
 *
*/
void Platform::addBlock(Sprite& sprite){

    int width = sprite.getScaledWidth(0);
    int height = sprite.getScaledHeight(0);

    int bX = x;

    for (int b = 0; b < blocks.size(); b++){

        bX += blocks[b].getWidth();

    }

    int bY = y;

    Block block(bX, bY, width, height);

    sprite.copyPixelsOnto(block.getWave().getSprite());

    block.getWave().resetColumnLocations();

    block.getWave().getSprite().setScale(sprite.getScale());

    blocks.push_back(block);

}

/*
 * description: gets column locations by reference
 * return: vector<int>
 * precondition: class instance exists and header files linked
 * postcondition: column locations passed by reference into vector<int>
 *
*/
vector<int>& Platform::getColLocations(){

    return columnLocations;

}

/*
 * description: gets collision box by reference
 * return: CollisionBox
 * precondition: class instance exists and header files linked
 * postcondition: collision box passed by reference
 *
*/
CollisionBox& Platform::getCollisionBox(){

    return cBox;

}

/*
 * description: gets the number of columns
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Platform::numOfColumns(){

    return columnLocations.size();

}

/*
 * description: gets the state of frozen
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
bool Platform::isFrozen(){

    return frozen;

}

/*
 * description: sets the variable frozen
 * return: void
 * precondition: class instance exists and header files linked
 * postcondition: frozen variable set
 *
*/
void Platform::setFrozen(){

    frozen = true;

}

/*
 * description: constructor for Level
 * return: NA
 * precondition: class instance exists
 * postcondition: Nothing is changed
 *
*/

bool Platform::isBlue(){
    return blue;
}

void Platform::setBlue(){
    blue = true;
}

