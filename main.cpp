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

    int square_x = 395,square_y = 150;
    CollisionBox test(20,20,square_x,square_y);
    bool jumping = false, hit_max_jump = false;
    bool falling = true, touching_side_left = false, touching_side_right = false, hit_head = false;
    int jump_measure;
    CollisionBox top_left(350,16,0,110), top_right(350,16,450,110), center_middle(420,16,190,200),
                 center_left(140,16,0,210), center_right(140,16,660,210), Screen_top (800,10,0,0),
                 bottom_left(280,16,0,290), bottom_right(280,16,520,290), floor(800,30,0,370);
    CollisionBox top_left_pipe (98,110,0,0), top_right_pipe (98,110,702,0),
                 bottom_left_pipe (65,64,0,306), bottom_right_pipe (65,64,735,306);

    while (!p.getQuit()){


        if (p.kbhit()){
            switch(p.getKey()){
            }
        }
        p.clear();

        // Draw Black
        drawBlackBackground(screenWidth, screenHeight, p);

        // Draw Player
        plotSquare(square_x,square_y,20,100,200,100,p);

        // Test Falling
        if (test.isTouching(floor) && !jumping){
            falling = false;
        }
        else if (test.isTouching(top_left) && !jumping){
            falling = false;
        }
        else if (test.isTouching(top_right) && !jumping){
            falling = false;
        }
        else if (test.isTouching(center_middle) && !jumping){
            falling = false;
        }
        else if (test.isTouching(center_left) && !jumping){
            falling = false;
        }
        else if (test.isTouching(center_right) && !jumping){
            falling = false;
        }
        else if (test.isTouching(bottom_left) && !jumping){
            falling = false;
        }
        else if (test.isTouching(bottom_right) && !jumping){
            falling = false;
        }
        else if(jumping){
            falling = false;
        }
        else {
            falling = true;
        }

        // Test Side Collision
        if (test.hitTheSideOf(top_left)){
            touching_side_right = false;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(top_right)){
            touching_side_right = true;
            touching_side_left = false;
        }
        else if (test.hitTheSideOf(center_left)){
            touching_side_right = false;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(center_right)){
            touching_side_right = true;
            touching_side_left = false;
        }
        else if (test.hitTheSideOf(center_left)){
            touching_side_right = false;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(center_right)){
            touching_side_right = true;
            touching_side_left = false;
        }
        else if (test.hitTheSideOf(bottom_left)){
            touching_side_right = false;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(bottom_right)){
            touching_side_right = true;
            touching_side_left = false;
        }
        else if (test.hitTheSideOf(center_middle)){
            touching_side_right = true;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(top_left_pipe)){
            touching_side_right = false;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(top_right_pipe)){
            touching_side_right = true;
            touching_side_left = false;
        }
        else if (test.hitTheSideOf(bottom_left_pipe)){
            touching_side_right = false;
            touching_side_left = true;
        }
        else if (test.hitTheSideOf(bottom_right_pipe)){
            touching_side_right = true;
            touching_side_left = false;
        }
        else {
            touching_side_right = false;
            touching_side_left = false;
        }

        // Test Hit Head
        if (test.hitHeadUnder(top_left)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(top_right)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(center_left)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(center_middle)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(center_right)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(bottom_left)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(bottom_right)){
            hit_head = true;
        }
        else if (test.hitHeadUnder(Screen_top)) {
            hit_head = true;
        }
        else {
            hit_head = false;
        }

        // Get User Input
        key_pressed = p.getKey();

        // Side to Side Movement
        if (!touching_side_right){
            if (key_pressed == 'D'){
                square_x += 2;
            }
        }
        else square_x -= 2;

        if (!touching_side_left){
            if (key_pressed == 'A'){
                square_x -= 2;
            }
        }
        else square_x += 2;

        // Jumping
        if (!falling){
            if(!jumping){
                if (key_pressed == 'W'){
                    jumping = true;
                    square_y -= 4;
                    jump_measure = 4;
                }
            }
            if (jumping && !hit_max_jump){
                square_y -= 3;
                jump_measure += 3;
                if (hit_head){
                    hit_max_jump = true;
                    jumping = false;
                    square_y += 10;
                }
                else if (jump_measure >= 105){
                    hit_max_jump = true;
                    jumping = false;
                }
            }
            if (jumping && hit_max_jump){
                jump_measure -= 3;
                if (jump_measure <= 0){
                    hit_max_jump = false;
                }
            }
        }
        else if (falling){
            square_y += 2;
        }


        // Drawing
        test.moveToLocation(square_x,square_y);

        spawnPipeLeft.draw(p);
        spawnPipeRight.draw(p);

        bottomLeftPipe.draw(p);
        bottomRightPipe.draw(p);

        horizontalTile(brickFloor, 0, screenWidth, p);

        level1.draw(p);

        // Debug
        if (square_x <= 2){
            square_x = 780;
            square_y -= 4;
        }
        if (square_x >= 800){
            square_x = 20;
            square_y -= 4;
        }

        // Update Screen
        p.update();

        p.Sleep(1);

    }

    return 0;
}
