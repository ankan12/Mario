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
#include "Level.h"
#include <vector>


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

    for (int f = 0; f < freezeAnimations.size(); f++){

        FreezeAnimation& fa = freezeAnimations[f];

        if (fa.finished()){
            freezeAnimations.erase(freezeAnimations.begin() + f);
            continue;
        }

        Platform& p = platforms[fa.getPlatformNumber()];

        fa.setNextFrame(p);

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


void Level::clearPlatforms(){
    platforms.clear();
}

void Level::replaceBlocks(int sizeChange){

    vector<Platform> oldPlatforms;

    for (int i = 0; i < numOfPlatforms(); i++){
        oldPlatforms.push_back(platforms[i]);
    }

    platforms.clear();

    for (int i = 0; i < oldPlatforms.size(); i++){

        Platform& p = oldPlatforms[i];
        int numOfBlocks = p.numOfBlocks();
        int x = p.get_x();
        int y = p.get_y();
        placePlatform(x, y, numOfBlocks + sizeChange);

    }

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


void Level::givePlatformIcicles(int platNumber){

    Platform& p = platforms[platNumber];

    leftBlueSprite.copyPixelsOnto(p.getBlock(0).getWave().getSprite());

    for (int i = 1; i < p.numOfBlocks()-1; i++){

        midBlueSprite.copyPixelsOnto(p.getBlock(i).getWave().getSprite());

    }

    int i = p.numOfBlocks()-1;

    rightBlueSprite.copyPixelsOnto(p.getBlock(i).getWave().getSprite());

    p.setBlue();

}

void Level::setLeftBlueSprite(char filename[], ifstream& inFile, int scale){
    leftBlueSprite.loadImage(filename, inFile);
    leftBlueSprite.setScale(scale);
}
void Level::setMidBlueSprite(char filename[], ifstream& inFile, int scale){
    midBlueSprite.loadImage(filename, inFile);
    midBlueSprite.setScale(scale);
}
void Level::setRightBlueSprite(char filename[], ifstream& inFile, int scale){
    rightBlueSprite.loadImage(filename, inFile);
    rightBlueSprite.setScale(scale);
}

void Level::addFreezeAnimation(char left[], char mid[], char right[], ifstream& inFile, int scale, int platNumber, int startX){

    FreezeAnimation fa(left, mid, right, inFile, 2, startX);
    fa.setPlatformNumber(platNumber);

    freezeAnimations.push_back(fa);

    platforms[platNumber].setFrozen();
}
/*
 * description: adds the freeze animation
 * return: void
 * precondition: class instance exists and two ints are passed in
 * postcondition: freeze animation is added
 *
*/

