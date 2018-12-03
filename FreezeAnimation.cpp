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
#include "FreezeAnimation.h"

/*
 * description: constructor for freeze animation
 * return: NA
 * precondition: instance of FreezeAnimation exists
 * postcondition: variables set to input
 *
*/
FreezeAnimation::FreezeAnimation(char left[], char middle[], char right[],
                                 ifstream& inFile, int scale, int startBlock){

        a = 0;

        leftIceBlock.loadImage(left, inFile);
        leftIceBlock.setScale(scale);

        middleIceBlock.loadImage(middle, inFile);
        middleIceBlock.setScale(scale);

        rightIceBlock.loadImage(right, inFile);
        rightIceBlock.setScale(scale);

        this->startBlock = startBlock;

}

/*
 * description: function that sets the next frame
 * return: void
 * precondition: instance of FreezeAnimation
 * postcondition: platform returned by reference
 *
*/
void FreezeAnimation::setNextFrame(Platform& platform){

    if (hasFinished){
        return;
    }

    for (int b = 0; b < platform.numOfBlocks(); b++){

        if (b >= startBlock - a && b <= startBlock + a){

            Sprite& s = platform.getBlock(b).getWave().getSprite();

            if (b == 0){
                leftIceBlock.copyPixelsOnto(s);
            }
            else if (b == platform.numOfBlocks()-1){
                rightIceBlock.copyPixelsOnto(s);
            }
            else{
                middleIceBlock.copyPixelsOnto(s);
            }

        }

    }

    if (a > startBlock && a > (platform.numOfBlocks() - startBlock)){
        hasFinished = true;
    }
    else{
        a+=0.1;
    }
}

/*
 * description: function that returns boolean
 * return: bool
 * precondition: instance of FreezeAnimation
 * postcondition: returns a bool
 *
*/
bool FreezeAnimation::finished(){

    return hasFinished;

}

/*
 * description: sets the platform number
 * return: void
 * precondition: instance of FreezeAnimation
 * postcondition: platform number is sent
 *
*/
void FreezeAnimation::setPlatformNumber(int platformNumber){

    this->platformNumber = platformNumber;

}

/*
 * description: returns the platform number
 * return: int
 * precondition: instance of FreezeAnimation
 * postcondition: nothing is changed
 *
*/
int FreezeAnimation::getPlatformNumber(){

    return platformNumber;

}
