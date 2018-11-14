#include "Level.h"


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

Level::Level(){
}

void Level::draw(SDL_Plotter& p){

    for (int i = 0; i < platforms.size(); i++){

        for (int b = 0; b < platforms[i].numOfBlocks(); b++){

            platforms[i].getBlock(b).draw(p);

        }
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

    if (containsEdgeSprites()){

        platform.addBlock(leftEdgeSprite);

        for (int b = 1; b < numOfBlocks; b++){

            platform.addBlock(blockSprite);

        }

        platform.addBlock(rightEdgeSprite);

    }

    else {

        for (int b = 0; b < numOfBlocks; b++){

            platform.addBlock(blockSprite);

        }
    }

    platforms.push_back(platform);

}

int Level::numOfPlatforms(){

    return platforms.size();

}

Platform& Level::getPlatform(int index){

    return platforms[index];

}
