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
#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "SDL_Plotter.h"
#include "Block.h"
#include "Platform.h"

#include <fstream>
#include <vector>
#include "WaveAnimation.h"

#include "FreezeAnimation.h"

class Level{

private:
    vector<Platform> platforms;
    Sprite blockSprite;
    Sprite leftEdgeSprite;
    Sprite rightEdgeSprite;
    vector<WaveAnimation> waveAnimations;
    vector<FreezeAnimation> freezeAnimations;

    Sprite leftBlueSprite;
    Sprite midBlueSprite;
    Sprite rightBlueSprite;

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
    void addFreezeAnimation(char[], char[], char[], ifstream&, int scale, int platNumber, int startX);

    void clearPlatforms();

    void replaceBlocks(int sizeChange);

    void givePlatformIcicles(int platNumber);

    void setLeftBlueSprite(char[], ifstream&, int scale);
    void setMidBlueSprite(char[], ifstream&, int scale);
    void setRightBlueSprite(char[], ifstream&, int scale);




};

#endif // LEVEL_H_INCLUDED
