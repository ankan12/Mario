#include "Platform.h"

Platform::Platform(int x, int y){

    this->x = x;
    this->y = y;

    frozen = false;
    blue = false;

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

void Platform::clearBlocks(){
    blocks.clear();
}

vector<int>& Platform::getColLocations(){

    return columnLocations;

}

CollisionBox& Platform::getCollisionBox(){

    return cBox;

}

int Platform::numOfColumns(){

    return columnLocations.size();

}

bool Platform::isFrozen(){

    return frozen;

}

void Platform::setFrozen(){

    frozen = true;

}

bool Platform::isBlue(){
    return blue;
}

void Platform::setBlue(){
    blue = true;
}

