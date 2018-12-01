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
    cout << "Hello world!" << endl;

    SDL_Plotter p(800, 800);

    drawBlackBackground(800, 800, p);

    Video video("video.txt");

    video.drawNextFrame(p);

    while (!video.reachedEndOfVideo()){

        p.Sleep(1);

        p.update();

        video.drawNextFrame(p);

    }

    ifstream inFile;

    Sprite logo("marioBrosLogo.txt", inFile);

    logo.setLocation(40, 40);

    logo.setScale(4);

    logo.set_xCrop(50);
    logo.set_yCrop(50);

    logo.draw(p);

    Sprite sprite("example_sprite", inFile);
    CollisionBox box(100,100,250,250);
    box.resetAtLocation(50, 50);

    Sprite sprite2("example_sprite",inFile);

    Wave wave("example_sprite", inFile);
    wave.getSprite().setScale(5);

    cout << "height1: " << sprite.getHeight(2) << endl;
    cout << "width1: " << sprite.getWidth(2) << endl;

    sprite.setMirrored(true);

    wave.setSpriteLocation(100, 100);

    sprite.setLocation(250, 250);
    sprite2.setLocation(250,250);

    sprite.setScale(4);
    sprite2.setScale(4);

    sprite.draw(p);
    sprite2.draw(p);

    Number number("digits.txt", inFile);

    for (int c = 0; c < wave.getSprite().getWidth(0); c++){

        wave.offsetColumn(c, c);

    }

    for (int c = 0; c < 50; c++){

        p.plotPixel(30, c, 0, 0, 0);

    }

    Sprite sprite3;

    sprite2.copyPixelsOnto(sprite3);

    sprite3.setLocation(400, 400);
    sprite3.setScale(5);
    number.setScale(5);

    Sprite floor("platform1.txt", inFile);
    Sprite floor2("platform2.txt", inFile);

    floor2.setLocation(0, 9 * 3);
    floor2.setScale(3);
    //floor2.draw(p);

    floor.setScale(3);


    //floor.draw(p);

    Sprite brickFloor("brickFloor.txt", inFile);

    brickFloor.setScale(4);

    brickFloor.setLocation(0, 400);

    brickFloor.set_xCrop(800);

    brickFloor.draw(p);

    Sprite pipe("enemySpawnPipe_processing.txt", inFile);
    Sprite animatedPipe("animatedPipe.txt", inFile);
    animatedPipe.setScale(3);

    animatedPipe.setLocation(0,200);

    pipe.setScale(5);

    //pipe.draw(p);

    //p.update();


    Level level;

//    level.setBlockSprite("blueBlock.txt", inFile);

//    level.placeBlock(0, 0);
//    level.placeBlock(100, 100);

    level.draw(p);

    int num = 0;

    while (!p.getQuit()){

        if (p.kbhit()){

            switch (p.getKey()){

            case ' ':
                p.clear();

                animatedPipe.nextFrame();
                animatedPipe.draw(p);
                sprite.nextFrame();
                sprite2.nextFrame();
                wave.getSprite().setMirrored(wave.getSprite().mirrored() ? false : true);
                sprite.draw(p);
                sprite2.draw(p);
                box.drawBox(p);
                wave.draw(p);
                sprite3.draw(p);
                number.setNumber(num);
                num++;
                number.draw(p);


                break;

            }

        }

        p.update();

    }

    return 0;
}
