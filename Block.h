#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "Sprite.h"
#include "CollisionBox.h"
#include "SDL_Plotter.h"
#include "Wave.h"
#include <fstream>

enum BlockType {leftEdge, middle, rightEdge};

class Block{

private:
    CollisionBox cBox;
    int x, y;
    int width, height;
    BlockType type;
    Wave wave;
    bool icy;

public:

/*
 * description: constructor for Block
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
    Block(int x, int y, int width, int height);

/*
 * description: constructor for Block
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
    Block(int x, int y, int width, int height, BlockType type);

/*
 * description: uses SDL to draw to the screen
 * return: void
 * precondition: class instance exists and SDL is passed in
 * postcondition: information drawn on screen
 *
*/
    void draw(SDL_Plotter& p);


/*
 * description: gets wave by reference
 * return: Wave
 * precondition: class instance exists and header files are linked
 * postcondition: wave has been passed by reference
 *
*/
    Wave& getWave();

/*
 * description: returns the state of Icy
 * return: bool
 * precondition: class instance exists
 * postcondition: bool returned and nothing is changed
 *
*/
    bool isIcy();

/*
 * description: returns the state of Icy
 * return: bool
 * precondition: class instance exists
 * postcondition: bool returned and nothing is changed
 *
*/
    void setIcy(bool value);

/*
 * description: returns x variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
    int get_x();

/*
 * description: returns y variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
    int get_y();

/*
 * description: returns width variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
    int getWidth();

/*
 * description: returns height variable
 * return: int
 * precondition: class instance exists
 * postcondition: int returned and nothing is changed
 *
*/
    int getHeight();

};

#endif // BLOCK_H_INCLUDED
