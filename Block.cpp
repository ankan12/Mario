#include "Block.h"

/*
 * description: constructor for Block
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
Block::Block(int x, int y, int width, int height){

    type = middle;
    icy = false;

    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;

    wave.setSpriteLocation(x, y);

    cBox.setWidth(width);
    cBox.setHeight(height);
    cBox.resetAtLocation(x, y);

}

/*
 * description: constructor for Block
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
Block::Block(int x, int y, int width, int height, BlockType type){

    type = middle;
    icy = false;

    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;

    cBox.setWidth(width);
    cBox.setHeight(height);
    cBox.resetAtLocation(x, y);

    wave.setSpriteLocation(x, y);

    this->type = type;

}

/*
 * description: uses SDL to draw to the screen
 * return: void
 * precondition: class instance exists and SDL is passed in
 * postcondition: information drawn on screen
 *
*/
void Block::draw(SDL_Plotter& p){

    wave.draw(p);

}

/*
 * description: gets wave by reference
 * return: Wave
 * precondition: class instance exists and header files are linked
 * postcondition: wave has been passed by reference
 *
*/
Wave& Block::getWave(){

    return wave;

}

/*
 * description: returns the state of Icy
 * return: bool
 * precondition: class instance exists
 * postcondition: bool returned and nothing is changed
 *
*/
bool Block::isIcy(){

    return icy;

}

/*
 * description: returns the state of Icy
 * return: bool
 * precondition: class instance exists
 * postcondition: bool returned and nothing is changed
 *
*/
void Block::setIcy(bool value){

    icy = value;

}

/*
 * description: returns x variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
int Block::get_x(){

    return x;

}

/*
 * description: returns y variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
int Block::get_y(){

    return y;

}

/*
 * description: returns width variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
int Block::getWidth(){

    return width;

}

/*
 * description: returns height variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
int Block::getHeight(){

    return height;

}
