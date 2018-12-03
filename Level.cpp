#include "Level.h"
#include <vector>

Level::Level(){
}

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


void Level::setBlockSprite(char filename[], ifstream& inFile, int scale){

    blockSprite.loadImage(filename, inFile);
    blockSprite.setScale(scale);
}

void Level::setLeftEdgeSprite(char filename[], ifstream& inFile, int scale){

    leftEdgeSprite.loadImage(filename, inFile);
    leftEdgeSprite.setScale(scale);

}

void Level::setRightEdgeSprite(char filename[], ifstream& inFile, int scale){

    rightEdgeSprite.loadImage(filename, inFile);
    rightEdgeSprite.setScale(scale);

}

bool Level::containsEdgeSprites(){

    if (leftEdgeSprite.getTotalFrames() == 0 ||
    rightEdgeSprite.getTotalFrames() == 0){

        return false;

    }

    return true;

}

Sprite& Level::getSprite(){

    return blockSprite;

}

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

int Level::numOfPlatforms(){

    return platforms.size();

}

Platform& Level::getPlatform(int index){

    return platforms[index];

}

void Level::addWaveAnimation(int platNumber, int startX){

    cout << "Add waveAnimation" << endl;
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
