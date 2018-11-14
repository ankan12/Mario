#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include "Sprite.h"
#include "CollisionBox.h"
#include "Wave.h"
#include "Number.h"
#include "Video.h"
#include "Level.h"
#include "DrawingFunctions.h"
using namespace std;

int main(int argc, char ** argv)
{
    const int screenWidth = 800, screenHeight = 800;

    SDL_Plotter p(screenWidth, screenHeight);

    ifstream inFile;

    Sprite spawnPipeLeft("animatedPipe.txt", inFile);
    spawnPipeLeft.setScale(2);

    Sprite spawnPipeRight("animatedPipe.txt", inFile);
    spawnPipeRight.setMirrored(true);
    spawnPipeRight.setScale(2);
    spawnPipeRight.set_x(screenWidth - spawnPipeRight.getWidth(0) *
                         spawnPipeRight.getScale());

    Sprite brickFloor("brickFloor.txt", inFile);
    brickFloor.setScale(2);
    brickFloor.set_y(screenHeight - brickFloor.getHeight(0) *
                           brickFloor.getScale());

    Level level1;
    level1.setBlockSprite("blueBlock.txt", inFile);



    while (!p.getQuit()){


        if (p.kbhit()){
            switch(p.getKey()){

            }
        }

        p.clear();

        drawBlackBackground(screenWidth, screenHeight, p);

        spawnPipeLeft.draw(p);
        spawnPipeRight.draw(p);

        horizontalTile(brickFloor, 0, screenWidth, p);

        p.update();

        p.Sleep(1);

    }

    return 0;
}
