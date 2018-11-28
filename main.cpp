

#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include "Sprite.h"
#include "CollisionBox.h"
#include "Wave.h"
#include "Number.h"
#include "Level.h"
#include "DrawingFunctions.h"
#include "Block.h"
#include "WaveAnimation.h"
#include "Shellcreeper.h"
#include <cstdlib>
#include <cmath>
#include "Plumber.h"

using namespace std;


int main(int argc, char ** argv)
{

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

    Plumber player("mario_sprite_sheet.txt", inFile, 2, 395, 150);

    CollisionBox cPipe1, cPipe2, cPipe3, cPipe4, cFloor;
    cPipe1.fitToSprite(spawnPipeLeft);
    cPipe2.fitToSprite(spawnPipeRight);
    cPipe3.fitToSprite(bottomLeftPipe);
    cPipe4.fitToSprite(bottomRightPipe);

    cFloor.fitToSprite(brickFloor);
    cFloor.setWidth(800);

    CollisionBox cCeiling(800,5,0,0);

    vector<CollisionBox> solids;

    solids.push_back(cPipe1);
    solids.push_back(cPipe2);
    solids.push_back(cPipe3);
    solids.push_back(cPipe4);
    solids.push_back(cFloor);
    solids.push_back(cCeiling);

    for (int i = 0; i < level1.numOfPlatforms(); i++){
        solids.push_back(level1.getPlatform(i).getCollisionBox());
    }

    vector<CollisionBox> creepBoxes;

    vector<Shellcreeper> creepers;
    int enemySpawnTimer = 0;

    while (!p.getQuit()){

        creepBoxes.clear();
        for (int i = 0; i < creepers.size(); i++){
            creepBoxes.push_back(creepers[i].getCBox());
        }

        if (enemySpawnTimer == 100){
            Shellcreeper creeper("turtle.txt", inFile, 2, rand()%2);
            creepers.push_back(creeper);
            creepBoxes.push_back(creeper.getCBox());
            enemySpawnTimer = 0;
        }

        enemySpawnTimer++;

        player.updateLocation();
        player.solidCollisions(solids, level1);

        for (int i = 0; i < creepers.size(); i++){

            CollisionBox& hBox = creepers[i].getHitBox();
            CollisionBox& c = player.getCBox();

            CollisionBox& b = creepers[i].getCBox();

            if (c.hitHeadUnder(hBox)){
                creepers[i].setXVel(0);
                creepers[i].setYVel(-2);
                creepers[i].getSprite().setCurrentFrame(8);
                creepers[i].setFalling(true);
                creepers[i].setBumped(true);
            }

            if (c.isTouching(b)){

                if (creepers[i].getBumped() && !creepers[i].getDead()){
                    creepers[i].setYVel(-2);
                    creepers[i].setXVel(player.getXVel()/2.0);
                    creepers[i].setYAccel(0.2);
                    creepers[i].setDead(true);
                    creepers[i].setFalling(true);
                }

            }

        }

        for (int i = 0; i < creepers.size(); i++){

            if (creepers[i].getDead() && creepers[i].getY() > 0){
                creepers.erase(creepers.begin() + i);
            }
            creepers[i].updateLocation();
            if (!creepers[i].getDead()){
                creepers[i].solidCollisions(solids, level1);
            }
        }

        // Draw Black
        drawBlackBackground(screenWidth, screenHeight, p);

        // Get User Input
        p.kbhit();
        key_pressed = p.getKey();
        player.onKeyPress(key_pressed);

        for (int i = 0; i < creepers.size(); i++){
            if (!(creepers[i].getDead() && creepers[i].getY() > 350)){
                creepers[i].draw(p);
            }

        }

        spawnPipeLeft.draw(p);
        spawnPipeRight.draw(p);

        bottomLeftPipe.draw(p);
        bottomRightPipe.draw(p);

        horizontalTile(brickFloor, 0, screenWidth, p);

        level1.draw(p);

        player.draw(p);


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
