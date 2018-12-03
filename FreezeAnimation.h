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
#ifndef FREEZEANIMATION_H_INCLUDED
#define FREEZEANIMATION_H_INCLUDED

#include <fstream>
#include "Sprite.h"
#include "Platform.h"

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
