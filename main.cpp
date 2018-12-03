

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
#include <ctime>
#include "TextBox.h"
#include <sstream>
#include "EnemySpawner.h"
#include "Enemies.h"
#include "FreezeAnimation.h"
#include "Slipice.h"
#include "Scores.h"
using namespace std;

void createLevel(Level& level);

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

    cout << spawnPipeLeft.get_y() +
                         spawnPipeLeft.getScaledHeight(0) << endl;

    level1.placePlatform(0, spawnPipeLeft.get_y() +
                         spawnPipeLeft.getScaledHeight(0), 25);

    level1.placePlatform(800 - 25 * 14, level1.getPlatform(0).get_y(), 25);

    cout << (200 -level1.getPlatform(0).get_y()) << endl;

    level1.placePlatform(400 - 15 * 14, 200, 30);

    level1.placePlatform(0, 290, 20);
    level1.placePlatform(800 - 20 * 14, 290, 20);

    level1.placePlatform(0, 210, 10);
    level1.placePlatform(800 - 10 * 14, 210, 10);

    createLevel(level1);

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

//    solids.push_back(cPipe1);
//    solids.push_back(cPipe2);
//    solids.push_back(cPipe3);
//    solids.push_back(cPipe4);
    solids.push_back(cFloor);
    solids.push_back(cCeiling);

    Pipe pipe0;
    pipe0.direction = "right";
    pipe0.entrance.resetAtLocation(cPipe4.get_x() - 2, cPipe4.get_y());
    pipe0.entrance.setWidth(2);
    pipe0.entrance.setHeight(cPipe4.getHeight());
    pipe0.entranceX = cPipe4.get_x();
    pipe0.entranceY = cPipe4.get_y() + 1;
    pipe0.exitX = cPipe1.get_x() + cPipe1.getWidth();
    pipe0.exitY = cPipe1.get_y();

    Pipe pipe1;
    pipe1.direction = "left";
    pipe1.entrance.resetAtLocation(cPipe3.get_x() + cPipe3.getWidth(), cPipe3.get_y());
    pipe1.entrance.setWidth(2);
    pipe1.entrance.setHeight(cPipe3.getHeight());
    pipe1.entranceX = cPipe3.get_x() + cPipe3.getWidth();
    pipe1.entranceY = cPipe3.get_y() + 1;
    pipe1.exitX = cPipe2.get_x();
    pipe1.exitY = cPipe2.get_y();


    for (int i = 0; i < level1.numOfPlatforms(); i++){
        solids.push_back(level1.getPlatform(i).getCollisionBox());
    }

    int enemySpawnTimer = 0;
    int enemies = 0;

    Sprite pow("pow.txt", inFile);
    pow.setScale(2);
    pow.setLocation(400-16, 250);
    CollisionBox powBox;
    powBox.fitToSprite(pow);
    powBox.type = "pow";

    Sprite life("life.txt",inFile);
    life.setScale(2);
    int lives = 10;

    int score = 0;
    Number scoreDisplay("digits.txt", inFile);
    scoreDisplay.setLocation(100, 0);
    scoreDisplay.setScale(2);
    TextBox center("letters.txt", inFile);
    center.setScale(2);
    center.setLocation(350,150);

    TextBox topTextBox("letters.txt",inFile);
    topTextBox.setScale(2);
    topTextBox.setLocation(350, 50);

    bool nextPhase = true;
    bool nextLevel = true;

    bool waitForPhaseToEnd = false;

    int level = 0;
    int phase = 0;

    bool startScreen = true;

    EnemySpawner enemySpawner;
    Enemies allEnemies(pipe0, pipe1);

    Score scoreKeeper;

    drawBlackBackground(800, 400, p);
    Sprite logo("marioBrosLogo.txt",inFile);
    logo.setScale(2);
    logo.setLocation(400 - logo.getScaledWidth(0)/2, 50);
    logo.draw(p);
    TextBox xToContinue("letters.txt",inFile);
    xToContinue.setText("Press x to continue");
    xToContinue.setLocation(logo.get_x()+70, 300);
    xToContinue.setScale(2);
    xToContinue.draw(p);
    p.update();
    while (p.getKey() != 'X'){
        p.kbhit();
        p.Sleep(5);
    }

    while (!p.getQuit()){

        if (nextLevel){
            level++;

            switch(level){
            case 1:
                level1.setBlockSprite("blueBlock.txt",inFile,2);
                createLevel(level1);
                enemySpawner.readFile("level1enemies.txt",inFile);
                break;
            case 2:
                level1.setBlockSprite("platform2.txt",inFile,2);
                createLevel(level1);
                enemySpawner.readFile("level2enemies.txt",inFile);
                break;
            case 3:
                level1.setBlockSprite("platform1.txt",inFile,2);
                createLevel(level1);
                enemySpawner.readFile("level3enemies.txt",inFile);
                break;
            case 4:
                level1.setBlockSprite("middleYellow.txt",inFile,2);
                level1.setLeftEdgeSprite("leftYellow.txt",inFile,2);
                level1.setRightEdgeSprite("rightYellow.txt",inFile,2);
                createLevel(level1);
                enemySpawner.readFile("level4enemies.txt",inFile);
                break;
            case 5:
                level1.setLeftBlueSprite("leftBlue.txt",inFile,2);
                level1.setMidBlueSprite("middleBlue.txt",inFile,2);
                level1.setRightBlueSprite("rightBlue.txt",inFile,2);
                level1.givePlatformIcicles(0);
                level1.givePlatformIcicles(1);
                enemySpawner.readFile("level5enemies.txt",inFile);
                break;
            default:

                drawBlackBackground(800,400,p);
                ostringstream writer;
                writer << "Thanks for playing!\nYour score is ";
                writer << score;

                scoreKeeper.storeScores();

                if (score > scoreKeeper.getScore(0)){
                    scoreKeeper.setScore(score, 0);
                }

                scoreKeeper.storeScores();

                writer << "\nTop score is " << scoreKeeper.getScore(0);
                center.setLocation(100,200);
                center.setText(writer.str());
                center.draw(p);
                p.update();
                while (!p.getQuit()){
                    p.kbhit();
                    p.Sleep(5);
                }

                break;
            }

            if (level > 5){
                break;
            }

            phase = 1;
            p.clear();
            drawBlackBackground(800, 400, p);
            ostringstream writer;
            writer << "Level " << level;
            writer.flush();
            center.setText(writer.str());
            center.draw(p);
            p.update();
            p.Sleep(1000);
            nextLevel = false;
            lives = 10;
            pow.setCurrentFrame(0);
            enemySpawnTimer = 0;
            allEnemies.clearEnemies();
            enemies = 0;
            player.placeCharacterInCenter();
            solids.clear();
            solids.push_back(powBox);
            for (int i = 0; i < level1.numOfPlatforms(); i++){
                solids.push_back(level1.getPlatform(i).getCollisionBox());
            }
            solids.push_back(cCeiling);
            solids.push_back(cFloor);

            phase = 1;
            nextPhase = true;
            waitForPhaseToEnd = false;

        }

        if (enemySpawnTimer == 150 && !waitForPhaseToEnd){

            waitForPhaseToEnd = allEnemies.addEnemy(enemySpawner.getNextEnemy(), inFile);
            enemySpawnTimer = 0;
            enemies++;
        }

        enemySpawnTimer++;

        player.updateLocation();

        if (player.getCBox().hitHeadUnder(powBox) && pow.getCurrentFrame() < 3){

            for (int t = 0; t < 300; t++){

                int randPlat = rand()%level1.numOfPlatforms();
                int randX = rand()&level1.getPlatform(randPlat).numOfColumns();
                level1.addWaveAnimation(randPlat,randX);

            }

            for (int ID = 0; ID < allEnemies.getEnemyCBoxes().size(); ID++){
                if (allEnemies.stateOfEnemy(ID) == grounded || allEnemies.stateOfEnemy(ID) == bumpedAndGrounded || allEnemies.stateOfEnemy(ID) == aliveAndFalling){
                    allEnemies.bumpEnemy(ID);
                }
            }

            p.Sleep(10);
            pow.nextFrame();
            if (pow.getCurrentFrame() == 3){
                removeCollisionBox(solids, "pow");
            }
        }

        player.solidCollisions(solids, level1);
        if (!player.getDead()){
            for (int i = 0; i < allEnemies.getEnemyCBoxes().size(); i++){

                CollisionBox& hurtBox = allEnemies.getEnemyHurtBoxes()[i];
                CollisionBox& hitBox = allEnemies.getEnemyCBoxes()[i];
                CollisionBox& c = player.getCBox();

                if (player.getFist().hitHeadUnder(hurtBox) && (allEnemies.stateOfEnemy(hurtBox.ID) == grounded || allEnemies.stateOfEnemy(hurtBox.ID) == bumpedAndGrounded)){
                    allEnemies.bumpEnemy(hurtBox.ID);
                }

                if (c.isTouching(hitBox)){
                    cout << "touched" << endl;

                    if (allEnemies.stateOfEnemy(hitBox.ID) == bumpedAndGrounded){
                        allEnemies.kickEnemyIfBumped(hitBox.ID, player.getXVel()/2.0);
                        score += 800;
                    }

                    else if ( !player.getInvincible() && (allEnemies.stateOfEnemy(hitBox.ID) == grounded || allEnemies.stateOfEnemy(hitBox.ID) == aliveAndFalling) ){
                        player.setYVel(-2);
                        player.setXVel(0);
                        player.setFalling(true);
                        player.getSprite().setCurrentFrame(6);
                        player.setDead(true);
                        lives--;
                    }

                }

            }
        }

        if (allEnemies.getEnemyCBoxes().size() == 0 && waitForPhaseToEnd){
            waitForPhaseToEnd = false;
            nextPhase = true;
            enemySpawnTimer = 0;
            phase++;
            if (phase > enemySpawner.getNumOfPhases()){
                nextLevel = true;
                nextPhase = false;
            }
        }

        allEnemies.updateLocations();
        allEnemies.updateCollisionBoxes();

//        for (int i = 0; i < allEnemies.getEnemyCBoxes().size(); i++){
//            solids.push_back(allEnemies.getEnemyCBoxes()[i]);
//        }

        allEnemies.solidCollisions(solids);

        for (int i = 0; i < allEnemies.getSlipices().size(); i++){

            Slipice& slip = allEnemies.getSlipices()[i];

            Platform& p = level1.getPlatform(slip.platNumber);

            if (slip.getSelfDestruct() && slip.getSprite().getCurrentFrame() == 4){
                level1.addFreezeAnimation("leftIce.txt","middleIce.txt","rightIce.txt",inFile,2,slip.platNumber,
                                          (slip.getX() - p.get_x())/p.getBlock(0).getWave().getSprite().getScaledWidth(0) );
            }

        }


//        removeCollisionBox(solids, "enemy");

        // Draw Black
        drawBlackBackground(screenWidth, screenHeight, p);

        // Get User Input
        p.kbhit();
        key_pressed = p.getKey();
        player.onKeyPress(key_pressed);
        if (key_pressed == ' '){
            nextLevel = true;
        }

        horizontalTile(brickFloor, 0, screenWidth, p);

        allEnemies.draw(p);

        spawnPipeLeft.draw(p);
        spawnPipeRight.draw(p);

        bottomLeftPipe.draw(p);
        bottomRightPipe.draw(p);

        level1.draw(p);
        pow.draw(p);

        player.draw(p);

        drawLives(life, 0, 0, lives, p);
        scoreDisplay.setNumber(score);
        scoreDisplay.draw(p);

        if (nextPhase){
            ostringstream writer;
            writer << "Phase " << phase;
            topTextBox.setText(writer.str());
            topTextBox.draw(p);
            if (enemySpawnTimer == 100){
                nextPhase = false;
            }
        }

        p.update();

        p.Sleep(10);

    }

    return 0;
}

void createLevel(Level& level){

    level.clearPlatforms();

    int w = level.getSprite().getScaledWidth(0);

    int length = 350;

    int num = length / w;

    level.placePlatform(0, 110, num);

    level.placePlatform(800 - num * w, level.getPlatform(0).get_y(), num);

    level.placePlatform(400 - ( (num+5)/2 ) * w, 200, num + 5);

    level.placePlatform(0, 290, num - 5);
    level.placePlatform(800 - (num-5) * w, 290, num - 5);

    level.placePlatform(0, 210, num - 15);
    level.placePlatform(800 - (num-15) * w, 210, num - 15);

}
