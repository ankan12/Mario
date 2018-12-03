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

    Level();

    void draw(SDL_Plotter& p);

    void placePlatform(int x, int y, int numOfBlocks);

    void setBlockSprite(char[], ifstream&, int scale);
    void setLeftEdgeSprite(char[], ifstream&, int scale);
    void setRightEdgeSprite(char[], ifstream&, int scale);

    bool containsEdgeSprites();

    Sprite& getSprite();
    Sprite& getSprite(BlockType type);

    int numOfPlatforms();

    Platform& getPlatform(int index);

    void addWaveAnimation(int platNumber, int startX);
    void addFreezeAnimation(char[], char[], char[], ifstream&, int scale, int platNumber, int startX);

    void clearPlatforms();

    void replaceBlocks(int sizeChange);

    void givePlatformIcicles(int platNumber);

    void setLeftBlueSprite(char[], ifstream&, int scale);
    void setMidBlueSprite(char[], ifstream&, int scale);
    void setRightBlueSprite(char[], ifstream&, int scale);

};

#endif // LEVEL_H_INCLUDED
