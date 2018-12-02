#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "SDL_Plotter.h"
#include "Block.h"
#include <fstream>
#include <vector>
#include "WaveAnimation.h"
class Platform{

private:

    int x, y;

    vector<Block> blocks;
    vector<int> columnLocations;

    CollisionBox cBox;

    bool frozen;

public:

/*
 * description: constructor for Platform
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
    Platform(int x, int y);

/*
 * description: gets and passes box by reference
 * return: Block
 * precondition: class instance exists and int passed in
 * postcondition: block is passed by reference
 *
*/
    Block& getBlock(int index);

/*
 * description: gets the number of blocks
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int numOfBlocks();

/*
 * description: gets the number of columns
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int numOfColumns();

/*
 * description: gets x variable
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int get_x();

/*
 * description: gets y variable
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int get_y();

/*
 * description: adds a block to save pixels into
 * return: void
 * precondition: class instance exists and header files are linked
 * postcondition: sprite has been added
 *
*/
    void addBlock(Sprite& sprite);

/*
 * description: gets column locations by reference
 * return: vector<int>
 * precondition: class instance exists and header files linked
 * postcondition: column locations passed by reference into vector<int>
 *
*/
    vector<int>& getColLocations();

/*
 * description: gets collision box by reference
 * return: CollisionBox
 * precondition: class instance exists and header files linked
 * postcondition: collision box passed by reference
 *
*/
    CollisionBox& getCollisionBox();

/*
 * description: gets the state of frozen
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    bool isFrozen();

/*
 * description: sets the variable frozen
 * return: void
 * precondition: class instance exists and header files linked
 * postcondition: frozen variable set
 *
*/
    void setFrozen();

};

class Level{

private:
    vector<Platform> platforms;
    Sprite blockSprite;
    Sprite leftEdgeSprite;
    Sprite rightEdgeSprite;
    vector<WaveAnimation> waveAnimations;

public:

/*
 * description: constructor for Level
 * return: NA
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    Level();

/*
 * description: draws input to the screen
 * return: void
 * precondition: class instance exists and SDL is passed in
 * postcondition: input is drawn to the screen
 *
*/
    void draw(SDL_Plotter& p);

/*
 * description: sets the location for the platform
 * return: void
 * precondition: class instance exists
 * postcondition: x, y, and number of blocks are set to input
 *
*/
    void placePlatform(int x, int y, int numOfBlocks);

/*
 * description: loads the sprite image
 * return: void
 * precondition: class instance exists
 * postcondition: sprite is set and scaled
 *
*/
    void setBlockSprite(char[], ifstream&, int scale);

/*
 * description: loads the left edge sprite image
 * return: void
 * precondition: class instance exists
 * postcondition: sprite is set and scaled
 *
*/
    void setLeftEdgeSprite(char[], ifstream&, int scale);

/*
 * description: loads the right edge sprite image
 * return: void
 * precondition: class instance exists
 * postcondition: sprite is set and scaled
 *
*/
    void setRightEdgeSprite(char[], ifstream&, int scale);

/*
 * description: used to tell if the file contains sprites
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    bool containsEdgeSprites();

/*
 * description: gets sprite by reference
 * return: Sprite
 * precondition: class instance exists
 * postcondition: sprite is passed by reference
 *
*/
    Sprite& getSprite();

/*
 * description: block sprite is gotten and passed by reference
 * return: Sprite
 * precondition: class instance exists
 * postcondition: sprite gotten by reference
 *
*/
    Sprite& getSprite(BlockType type);

/*
 * description: gets the number of platforms
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int numOfPlatforms();

/*
 * description: platform is gotten and passed by reference
 * return: Platform
 * precondition: class instance exists and int passed in
 * postcondition: gets Platform by reference
 *
*/
    Platform& getPlatform(int index);

/*
 * description: adds the wave animation
 * return: void
 * precondition: class instance exists and two ints are passed in
 * postcondition: wave animation is added
 *
*/
    void addWaveAnimation(int platNumber, int startX);

/*
 * description: adds the freeze animation
 * return: void
 * precondition: class instance exists and two ints are passed in
 * postcondition: freeze animation is added
 *
*/
    void addFreezeAnimation(int platNumber, int startX);

};

#endif // LEVEL_H_INCLUDED
