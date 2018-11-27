#include "FreezeAnimation.h"

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

bool FreezeAnimation::finished(){

    return hasFinished;

}

void FreezeAnimation::setPlatformNumber(int platformNumber){

    this->platformNumber = platformNumber;

}

int FreezeAnimation::getPlatformNumber(){

    return platformNumber;

}
