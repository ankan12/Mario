#ifndef FREEZEANIMATION_H_INCLUDED
#define FREEZEANIMATION_H_INCLUDED

#include <fstream>
#include "Sprite.h"
#include "Level.h"

class FreezeAnimation{

private:
    double a;

    int startBlock;

    Sprite leftIceBlock, middleIceBlock, rightIceBlock;

    bool hasFinished = false;

    int platformNumber;

public:

/*
 * description: constructor for freeze animation
 * return: NA
 * precondition: instance of FreezeAnimation exists
 * postcondition: variables set to input
 *
*/
    FreezeAnimation(char[], char[], char[], ifstream&, int scale, int start);

/*
 * description: function that sets the next frame
 * return: void
 * precondition: instance of FreezeAnimation
 * postcondition: platform returned by reference
 *
*/
    void setNextFrame(Platform& platform);

/*
 * description: function that returns boolean
 * return: bool
 * precondition: instance of FreezeAnimation
 * postcondition: returns a bool
 *
*/
    bool finished();

/*
 * description: sets the platform number
 * return: void
 * precondition: instance of FreezeAnimation
 * postcondition: platform number is sent
 *
*/
    void setPlatformNumber(int);

/*
 * description: returns the platform number
 * return: int
 * precondition: instance of FreezeAnimation
 * postcondition: nothing is changed
 *
*/
    int getPlatformNumber();

};


#endif // FREEZEANIMATION_H_INCLUDED
