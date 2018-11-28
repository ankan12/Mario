

#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include "Sprite.h"
#include "CollisionBox.h"
#include "Wave.h"
#include "Number.h"
//#include "Video.h"
#include "Level.h"
#include "DrawingFunctions.h"
#include "Block.h"
#include "WaveAnimation.h"
#include "Shellcreeper.h"
#include <cstdlib>
#include <cmath>
using namespace std;


int main(int argc, char ** argv)
{

    int numbers[5];

    int& x = numbers[1];

    x = 10;

    cout << numbers[1] << endl;

    x = 11;

    cout << numbers[1] << endl;

    int y = numbers[1];

    y = 12;

    cout << numbers[1] << endl;


    char key_pressed;

    const int screenWidth = 800, screenHeight = 400;
    SDL_Plotter p(screenHeight, screenWidth);

    ifstream inFile;

    Sprite spawnPipeLeft("animatedPipe.txt", inFile);
    spawnPipeLeft.set_y(50);
    spawnPipeLeft.setScale(2);

    Sprite spawnPipeRight("animatedPipe.txt", inFile);
    spawnPipeRight.set_y(50);
    spawnPipeRight.setMirrored(true);
    spawnPipeRight.setScale(2);
    spawnPipeRight.set_x(screenWidth - spawnPipeRight.getWidth(0) *
                         spawnPipeRight.getScale());

    Sprite brickFloor("brickFloor.txt", inFile);
    brickFloor.setScale(2);
    brickFloor.set_y(screenHeight - brickFloor.getScaledHeight(0));

    Level level1;
    level1.setBlockSprite("blueBlock.txt", inFile, 2);

    level1.placePlatform(0, spawnPipeLeft.get_y() +
                         spawnPipeLeft.getScaledHeight(0), 25);

    level1.placePlatform(800 - 25 * 14, level1.getPlatform(0).get_y(), 25);

    cout << (200 -level1.getPlatform(0).get_y()) << endl;

    level1.placePlatform(400 - 15 * 14, 200, 30);

    level1.placePlatform(0, 290, 20);
    level1.placePlatform(800 - 20 * 14, 290, 20);

    level1.placePlatform(0, 210, 10);
    level1.placePlatform(800 - 10 * 14, 210, 10);

    Sprite bottomLeftPipe("bottomPipe.txt", inFile);
    Sprite bottomRightPipe("bottomPipe.txt", inFile);

    bottomLeftPipe.setScale(2);
    bottomRightPipe.setScale(2);

    bottomLeftPipe.setMirrored(true);

    bottomLeftPipe.set_y(400 - brickFloor.getScaledHeight(0) -
                         bottomLeftPipe.getScaledHeight(0));
    bottomRightPipe.setLocation(800 - bottomRightPipe.getScaledWidth(0),
                                bottomLeftPipe.get_y());


    bool jumping = false, hit_max_jump = false;
    bool falling = true, touching_side_left = false, touching_side_right = false, hit_head = false;
    int jump_measure;

    Sprite turtle("turtle.txt", inFile);

    Sprite mario("mario_sprite_sheet.txt",inFile);
    mario.setScale(2);

    double square_x = 395,square_y = 150;
    CollisionBox test(mario.getScaledWidth(0),mario.getScaledHeight(0),square_x,square_y);
    test.setDirection(-90);

    Shellcreeper creeper("turtle.txt", inFile, 30, 30, 2);

    int timer = 0;

    double yVelocity = 0;
    double yAccel = 0.05;
    double xVelocity = 0;

    falling = true;

    Number numDirection("digits.txt",inFile);
    numDirection.setScale(1);

    test.setDirection(-90);

    int groundStart=0;
    int groundEnd=800;

    while (!p.getQuit()){

        timer++;
        timer %= 100;

        if (falling && yVelocity < 5){
            yVelocity += yAccel;
        }

        if (((test.get_x() + test.getWidth() < groundStart) ||
            (test.get_x() > groundEnd)) && !falling){

            if (!falling){
                falling = true;
            }
            groundStart = 0;
            groundEnd = 800;
        }

        square_y += yVelocity;
        square_x += xVelocity;
        test.moveToLocation(square_x, square_y);

        WaveAnimation wa(0, 50);
        wa.setSpeed_1sthalf(0.2);
        wa.setSpeed_2ndhalf(0.2);

        vector<WaveAnimation> wAnimations;

        if (p.kbhit()){
            switch(p.getKey()){
            }
        }
        p.clear();



        // Draw Black
        drawBlackBackground(screenWidth, screenHeight, p);

        CollisionBox cBox(100,100,20,0);

        cBox.drawBox(p);
        creeper.draw(p);
        creeper.getSprite().nextFrame(10);



        // Get User Input
        key_pressed = p.getKey();

        if (key_pressed == ' '){
            yVelocity = 0;
        }

        if (key_pressed != 'D' && key_pressed != 'A'){
            mario.setCurrentFrame(0);
            xVelocity = 0;
        }

        // Side to Side Movement
            if (key_pressed == 'D'){
                test.setDirection(0);

                xVelocity = 2;

                if(!mario.mirrored()){
                    mario.setMirrored(true);
                }
                if (timer%10 == 0){
                    mario.setCurrentFrame(mario.getCurrentFrame()+1);
                    if (mario.getCurrentFrame() == 4){
                        mario.setCurrentFrame(1);
                    }

                }
            }

            if (key_pressed == 'A'){

                test.setDirection(180);
                xVelocity = -2;;

                if (mario.mirrored()){
                    mario.setMirrored(false);
                }
                if (timer%10 == 0){
                    mario.setCurrentFrame(mario.getCurrentFrame()+1);
                    if (mario.getCurrentFrame() == 4){
                        mario.setCurrentFrame(1);
                    }
                }
            }


        if (key_pressed == 'W'&& !falling){
            test.setDirection(90);
            yVelocity = -3.5;
            falling = true;
        }

        spawnPipeLeft.draw(p);
        spawnPipeRight.draw(p);

        bottomLeftPipe.draw(p);
        bottomRightPipe.draw(p);


        horizontalTile(brickFloor, 0, screenWidth, p);

        wa.setNextFrame(level1.getPlatform(0).getColLocations());

        for (int w = 0; w < wAnimations.size(); w++){

            WaveAnimation& wa = wAnimations[w];

            if (wa.finished()){
                wAnimations.erase(wAnimations.begin() + w);
                continue;
            }

            Platform& p = level1.getPlatform(wa.platformNum());

            wa.setNextFrame(p.getColLocations());

        }

        level1.draw(p);

        for (int i = 0; i < level1.numOfPlatforms(); i++){
            level1.getPlatform(i).getCollisionBox().drawBox(p);
        }

        for (int i = 0; i < level1.numOfPlatforms(); i++){

            CollisionBox& b = level1.getPlatform(i).getCollisionBox();

            if (test.hitHeadUnder(b)){
                cout << "hit" << endl;
                yVelocity = 0;
                test.solidInteraction(b,90);

            }

            if (test.hitLeftOf(b)){
                xVelocity = 0;
                test.solidInteraction(b,0);
            }
            if (test.hitRightOf(b)){
                xVelocity = 0;
                test.solidInteraction(b,180);
            }

            if (test.jumpedOn(b)){
                falling = false;
                yVelocity = 0;
                test.solidInteraction(b,-90);
                groundStart = b.get_x();
                groundEnd = b.get_x()+b.getWidth();
            }


        }
        square_x = test.get_x();
        square_y = test.get_y();

        // Debug
        if (square_x <= 2){
            square_x = 780;
            square_y -= 4;
        }
        if (square_x >= 800){
            square_x = 20;
            square_y -= 4;
        }


        turtle.nextFrame(100);

        turtle.draw(p);

        mario.setLocation(square_x, square_y);

        mario.draw(p);
        test.drawBox(p);

        //test.setDirection(-90);
        numDirection.draw(p);

        // Update Screen
        p.update();

        p.Sleep(10);

    }

    return 0;
}

//
//#include <iostream>
//#include <fstream>
//#include "SDL_Plotter.h"
//#include "Sprite.h"
//#include "CollisionBox.h"
//#include "Wave.h"
//#include "Number.h"
//#include "Video.h"
//#include "Level.h"
//#include "DrawingFunctions.h"
//#include "WaveAnimation.h"
//#include <cstdlib>
//#include "TextBox.h"
//#include "FreezeAnimation.h"
//using namespace std;
//
//
//int main(int argc, char ** argv)
//{
//    cout << "Hello!" << endl;
//
//    const int screenWidth = 800, screenHeight = 400;
//    SDL_Plotter p(screenHeight, screenWidth);
//
//    ifstream inFile;
//
//    Sprite spawnPipeLeft("animatedPipe.txt", inFile);
//    spawnPipeLeft.set_y(50);
//    spawnPipeLeft.setScale(2);
//
//    Sprite spawnPipeRight("animatedPipe.txt", inFile);
//    spawnPipeRight.set_y(50);
//    spawnPipeRight.setMirrored(true);
//    spawnPipeRight.setScale(2);
//    spawnPipeRight.set_x(screenWidth - spawnPipeRight.getWidth(0) *
//                         spawnPipeRight.getScale());
//
//    Sprite brickFloor("brickFloor.txt", inFile);
//    brickFloor.setScale(2);
//    brickFloor.set_y(screenHeight - brickFloor.getScaledHeight(0));
//
//    Level level1;
//    level1.setBlockSprite("blueBlock.txt", inFile, 2);
//
//    level1.placePlatform(0, spawnPipeLeft.get_y() +
//                         spawnPipeLeft.getScaledHeight(0), 25);
//
//    level1.placePlatform(800 - 25 * 14, level1.getPlatform(0).get_y(), 25);
//
//    cout << (200 -level1.getPlatform(0).get_y()) << endl;
//
//    level1.placePlatform(400 - 15 * 14, 200, 30);
//
//    level1.placePlatform(0, 290, 20);
//    level1.placePlatform(800 - 20 * 14, 290, 20);
//
//    level1.placePlatform(0, 210, 10);
//    level1.placePlatform(800 - 10 * 14, 210, 10);
//
//    Sprite bottomLeftPipe("bottomPipe.txt", inFile);
//    Sprite bottomRightPipe("bottomPipe.txt", inFile);
//
//    bottomLeftPipe.setScale(2);
//    bottomRightPipe.setScale(2);
//
//    bottomLeftPipe.setMirrored(true);
//
//    bottomLeftPipe.set_y(400 - brickFloor.getScaledHeight(0) -
//                         bottomLeftPipe.getScaledHeight(0));
//    bottomRightPipe.setLocation(800 - bottomRightPipe.getScaledWidth(0),
//                                bottomLeftPipe.get_y());
//
//    WaveAnimation wa(0, 50);
//    //wa.setSpeed_1sthalf(0.2);
//    //wa.setSpeed_2ndhalf(0.2);
//
//    vector<WaveAnimation> wAnimations;
//
////    CollisionBox cBox(100, 100, 750, 0);
////    cBox.setHorizontalWrap(800);
//
//    TextBox tBox("letters.txt", inFile);
//
//    tBox.setLocation(10, 0);
//    tBox.setScale(3);
//
//    tBox.setText("ABCDEFG HIJKLMNOPQRSTUVWXYZ\n0123456789!!!!");
//
//    Number num("digits.txt", inFile);
//    num.setScale(3);
//    num.setLocation(700, 0);
//    num.setNumber(100);
//
//    Sprite mario("mario_sprite_sheet.txt", inFile);
//
//    mario.set_x(400);
//    mario.set_y(323);
//    mario.setScale(2);
//
//    Sprite coin("coin.txt", inFile);
//    Sprite coin2("coin.txt", inFile);
//    coin2.setLocation(0, 50);
//
//    vector<FreezeAnimation> fAnimations;
//
//    while (!p.getQuit()){
//
//        if (p.kbhit()){
//            switch(p.getKey()){
//            case ' ':{
//
//                int p = rand() % level1.numOfPlatforms();
//
//                int col = rand() % level1.getPlatform(p).getColLocations().size();
//
//                WaveAnimation wa(p, col);
//
//                wa.setDistance(30);
//
//                //wa.setWaveWidth(20.0/3.14159);
//
//                wa.setSpeed_2ndhalf(0.1);
//
//                //wa.setHeight(16.0);
//
//                wAnimations.push_back(wa);
//
//                mario.nextFrame();
//                break;
//            }
//            case 'F':
//
//                FreezeAnimation f("leftIce.txt","middleIce.txt","rightIce.txt",
//                                  inFile, 2, 5);
//                int p = rand() % level1.numOfPlatforms();
//                f.setPlatformNumber(p);
//
//                fAnimations.push_back(f);
//
//                break;
//
////            case 'W':
////                tBox.setText("w");
////                break;
////
////            case 'D':
////                tBox.setText("d");
////                break;
////
////            case 'A':
////                tBox.setText("a");
////                break;
//
//            }
//        }
//
//        p.clear();
//
//        drawBlackBackground(screenWidth, screenHeight, p);
//
//        spawnPipeLeft.draw(p);
//        spawnPipeRight.draw(p);
//
//        bottomLeftPipe.draw(p);
//        bottomRightPipe.draw(p);
//
//        horizontalTile(brickFloor, 0, screenWidth, p);
//
//        wa.setNextFrame(level1.getPlatform(0).getColLocations());
//
//        for (int w = 0; w < wAnimations.size(); w++){
//
//            WaveAnimation& wa = wAnimations[w];
//
//            if (wa.finished()){
//                wAnimations.erase(wAnimations.begin() + w);
//                continue;
//            }
//
//            Platform& p = level1.getPlatform(wa.platformNum());
//
//            wa.setNextFrame(p.getColLocations());
//
//        }
//
//        for (int i = 0; i < fAnimations.size(); i++){
//
//
//            if (fAnimations[i].finished()){
//                fAnimations.erase(fAnimations.begin() + i);
//                continue;
//            }
//
//            int p = fAnimations[i].getPlatformNumber();
//
//            fAnimations[i].setNextFrame(level1.getPlatform(p));
//
//        }
//
//        level1.draw(p);
//
//
//        for (int i = 0; i < level1.numOfPlatforms(); i++){
//
//            level1.getPlatform(i).getCollisionBox().drawBox(p);
//
//        }
//
////        cBox.drawBox(p);
//
//        num.setNumber(wAnimations.size());
//
//        tBox.draw(p);
//        num.draw(p);
//
//        mario.draw(p);
//
//        coin.nextFrame(20);
//        coin2.nextFrame(10);
//
//        coin2.draw(p);
//
//        coin.draw(p);
//
//        p.update();
//
//        p.Sleep(1);
//
//    }
//
//    return 0;
//}
//>>>>>>> Stashed changes
