#include "Level.h"
#include <vector>

Platform::Platform(int x, int y){

    this->x = x;
    this->y = y;

}

int Platform::get_x(){

    return x;

}

int Platform::get_y(){

    return y;

}

Block& Platform::getBlock(int index){

    return blocks[index];

}

int Platform::numOfBlocks(){

    return blocks.size();

}

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

vector<int>& Platform::getColLocations(){

    return columnLocations;

}

Level::Level(){
}

void Level::draw(SDL_Plotter& p){

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

    int numOfColumns = 0;

    if (containsEdgeSprites()){

        platform.addBlock(leftEdgeSprite);

        numOfColumns += platform.getBlock(0).getWave().numberOfColumns(0);

        for (int b = 1; b < numOfBlocks - 1; b++){

            platform.addBlock(blockSprite);
            numOfColumns += platform.getBlock(b).getWave().numberOfColumns(0);

        }

        platform.addBlock(rightEdgeSprite);

        Block& rightEdge = platform.getBlock(numOfBlocks - 1);

        numOfColumns += rightEdge.getWave().numberOfColumns(0);

    }

    else {

        for (int b = 0; b < numOfBlocks; b++){

            platform.addBlock(blockSprite);
            numOfColumns += platform.getBlock(b).getWave().numberOfColumns(0);

        }
    }

    platform.getColLocations().resize(numOfColumns, 0);

    platforms.push_back(platform);

}

int Level::numOfPlatforms(){

    return platforms.size();

}

Platform& Level::getPlatform(int index){

    return platforms[index];

}
