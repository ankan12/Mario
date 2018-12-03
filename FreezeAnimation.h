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
    FreezeAnimation(char[], char[], char[], ifstream&, int scale, int start);

    void setNextFrame(Platform& platform);

    bool finished();

    void setPlatformNumber(int);

    int getPlatformNumber();

};


#endif // FREEZEANIMATION_H_INCLUDED
