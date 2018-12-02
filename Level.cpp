#include "Level.h"
#include <vector>


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
Level::Level(){
}

/*
 * description: draws input to the screen
 * return: void
 * precondition: class instance exists and SDL is passed in
 * postcondition: input is drawn to the screen
 *
*/
void Level::draw(SDL_Plotter& p){

    for (int w = 0; w < waveAnimations.size(); w++){

        WaveAnimation& wa = waveAnimations[w];

        if (wa.finished()){
            waveAnimations.erase(waveAnimations.begin() + w);
            continue;
        }

        Platform& p = platforms[wa.platformNum()];

        wa.setNextFrame(p.getColLocations());

    }

    for (int i = 0; i < platforms.size(); i++){

        vector<int>& colLoc = platforms[i].getColLocations();
        int colIndex = 0;

        for (int b = 0; b < platforms[i].numOfBlocks(); b++){

            Block& block = platforms[i].getBlock(b);


            for (int c = 0; c < block.getWave().numberOfColumns(0); c++){

                block.getWave().offsetColumn(c, colLoc[colIndex]);
                colIndex++;

            }

            block.draw(p);

        }

        int numOfColumns = colLoc.size();
        colLoc.clear();
        colLoc.resize(numOfColumns, 0);

    }
}

/*
 * description: loads the sprite image
 * return: void
 * precondition: class instance exists
 * postcondition: sprite is set and scaled
 *
*/
void Level::setBlockSprite(char filename[], ifstream& inFile, int scale){

    blockSprite.loadImage(filename, inFile);
    blockSprite.setScale(scale);
}

/*
 * description: loads the left edge sprite image
 * return: void
 * precondition: class instance exists
 * postcondition: sprite is set and scaled
 *
*/
void Level::setLeftEdgeSprite(char filename[], ifstream& inFile, int scale){

    leftEdgeSprite.loadImage(filename, inFile);
    leftEdgeSprite.setScale(scale);

}

/*
 * description: loads the right edge sprite image
 * return: void
 * precondition: class instance exists
 * postcondition: sprite is set and scaled
 *
*/
void Level::setRightEdgeSprite(char filename[], ifstream& inFile, int scale){

    rightEdgeSprite.loadImage(filename, inFile);
    rightEdgeSprite.setScale(scale);

}

/*
 * description: used to tell if the file contains sprites
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
bool Level::containsEdgeSprites(){

    if (leftEdgeSprite.getTotalFrames() == 0 ||
    rightEdgeSprite.getTotalFrames() == 0){

        return false;

    }

    return true;

}


/*
 * description: gets sprite by reference
 * return: Sprite
 * precondition: class instance exists
 * postcondition: sprite is passed by reference
 *
*/
Sprite& Level::getSprite(){

    return blockSprite;

}

/*
 * description: block sprite is gotten and passed by reference
 * return: Sprite
 * precondition: class instance exists
 * postcondition: sprite gotten by reference
 *
*/
Sprite& Level::getSprite(BlockType type){

    switch (type){

    case leftEdge:
        return  leftEdgeSprite;

    case rightEdge:
        return rightEdgeSprite;

    default:
        return getSprite();

    }

}

/*
 * description: sets the location for the platform
 * return: void
 * precondition: class instance exists
 * postcondition: x, y, and number of blocks are set to input
 *
*/
void Level::placePlatform(int x, int y, int numOfBlocks){

    Platform platform(x, y);

    int width = 0;

    int numOfColumns = 0;

    if (containsEdgeSprites()){

        platform.addBlock(leftEdgeSprite);

        numOfColumns += platform.getBlock(0).getWave().numberOfColumns(0);

        width += leftEdgeSprite.getScaledWidth(0);

        for (int b = 1; b < numOfBlocks - 1; b++){

            platform.addBlock(blockSprite);
            numOfColumns += platform.getBlock(b).getWave().numberOfColumns(0);
            width += blockSprite.getScaledWidth(0);

        }

        platform.addBlock(rightEdgeSprite);

        Block& rightEdge = platform.getBlock(numOfBlocks - 1);

        numOfColumns += rightEdge.getWave().numberOfColumns(0);

        width += rightEdgeSprite.getScaledWidth(0);
    }

    else {

        for (int b = 0; b < numOfBlocks; b++){

            platform.addBlock(blockSprite);
            numOfColumns += platform.getBlock(b).getWave().numberOfColumns(0);
            width += blockSprite.getScaledWidth(0);

        }
    }

    platform.getColLocations().resize(numOfColumns, 0);

    platform.getCollisionBox().setWidth(width);
    platform.getCollisionBox().setHeight(blockSprite.getScaledHeight(0));
    platform.getCollisionBox().resetAtLocation(x, y);

    platform.getCollisionBox().type = "platform";
    platform.getCollisionBox().ID = platforms.size();

    platforms.push_back(platform);

}

/*
 * description: gets the number of platforms
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Level::numOfPlatforms(){

    return platforms.size();

}

/*
 * description: platform is gotten and passed by reference
 * return: Platform
 * precondition: class instance exists and int passed in
 * postcondition: gets Platform by reference
 *
*/
Platform& Level::getPlatform(int index){

    return platforms[index];

}

/*
 * description: adds the wave animation
 * return: void
 * precondition: class instance exists and two ints are passed in
 * postcondition: wave animation is added
 *
*/
void Level::addWaveAnimation(int platNumber, int startX){

    WaveAnimation wa(platNumber, startX);

    waveAnimations.push_back(wa);

}

/*
 * description: adds the freeze animation
 * return: void
 * precondition: class instance exists and two ints are passed in
 * postcondition: freeze animation is added
 *
*/
void Level::addFreezeAnimation(int platNumber, int startX){

}
