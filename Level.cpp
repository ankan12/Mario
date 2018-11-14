#include "Level.h"

Level::Level(){
}

void Level::draw(SDL_Plotter& p){

    for (int i = 0; i < blocks.size(); i++){

        blocks[i].draw(p);

    }
}

void Level::placeBlock(int x, int y, Sprite& sprite){

    int width = sprite.getWidth(0) * sprite.getScale();
    int height = sprite.getHeight(0) * sprite.getScale();

    Block block(x, y, width, height);

    sprite.copyPixelsOnto(block.getWave().getSprite());

    block.getWave().resetColumnLocations();

    blocks.push_back(block);


}

void Level::placeBlock(int x, int y){

    placeBlock(x, y, blockSprite);

}

void Level::placeBlock(int x, int y, BlockType type){

    switch(type){

    case leftEdge:
        placeBlock(x, y, leftEdgeSprite);
        return;

    case rightEdge:
        placeBlock(x, y, rightEdgeSprite);
        return;

    case middle:
        placeBlock(x, y);
        return;

    }

}

Block& Level::getBlock(int index){

    return blocks[index];

}

Block& Level::getBlock(int x, int y){

    for (int i = 0; i < blocks.size(); i++){

        if (blocks[i].get_x() == x && blocks[i].get_y() == y){

            return blocks[i];

        }

    }

}

void Level::setBlockSprite(char filename[], ifstream& inFile){

    blockSprite.loadImage(filename, inFile);

}

void Level::setLeftEdgeSprite(char filename[], ifstream& inFile){

    leftEdgeSprite.loadImage(filename, inFile);

}

void Level::setRightEdgeSprite(char filename[], ifstream& inFile){

    rightEdgeSprite.loadImage(filename, inFile);

}
