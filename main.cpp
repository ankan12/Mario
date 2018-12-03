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
#include "Music.h"
using namespace std;

/*This function causes a Level object to place 7 platforms in a symmetrical
pattern*/
void createLevel(Level& level);

#include "Music.h"

using namespace std;


int main(int argc, char ** argv)
{
    //Create the music objects
    Music die("mb_die.wav");
    Music coin("mb_coin.wav");
    Music touch("mb_touch.wav");
    bgMusic bg("bg_music.wav", 1000);

    bg.playMusic();

    char key_pressed;

    const int screenWidth = 800, screenHeight = 400;
    SDL_Plotter p(screenHeight, screenWidth);

    ifstream inFile;

    //Create the background
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
    level1.setBlockSprite("blueBlock.txt",inFile,2);
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


    //Create the object that the player will control
    Plumber player("mario_sprite_sheet.txt", inFile, 2, 395, 150);

    //Create collisionBoxes for the pipes
    CollisionBox cPipe1, cPipe2, cPipe3, cPipe4, cFloor;
    cPipe1.fitToSprite(spawnPipeLeft);
    cPipe2.fitToSprite(spawnPipeRight);
    cPipe3.fitToSprite(bottomLeftPipe);
    cPipe4.fitToSprite(bottomRightPipe);

    cFloor.fitToSprite(brickFloor);
    cFloor.setWidth(800);

    CollisionBox cCeiling(800,5,0,0);

    //Vector of CollisionBoxes that contains all of the solids in the game
    vector<CollisionBox> solids;

    solids.push_back(cFloor);
    solids.push_back(cCeiling);

    //pipe0 and pipe1 are used for transporting the enemies
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

    //Add all of the platforms to the vector of solids
    for (int i = 0; i < level1.numOfPlatforms(); i++){
        solids.push_back(level1.getPlatform(i).getCollisionBox());
    }

    //This is used for controlling the amount of time between enemy spawns
    int enemySpawnTimer = 0;

    //Create a sprite and collision box for the pow block
    Sprite pow("pow.txt", inFile);
    pow.setScale(2);
    pow.setLocation(400-16, 250);
    CollisionBox powBox;
    powBox.fitToSprite(pow);
    powBox.type = "pow";

    //Sprite used for drawing Mario's lives
    Sprite life("life.txt",inFile);
    life.setScale(2);
    int lives = 10;

    //Create a Number object that displays the score
    int score = 0;
    Number scoreDisplay("digits.txt", inFile);
    scoreDisplay.setLocation(100, 0);
    scoreDisplay.setScale(2);
    TextBox center("letters.txt", inFile);
    center.setScale(2);
    center.setLocation(350,150);

    //Create a TextBox object that displays when the next phase occurs.
    TextBox topTextBox("letters.txt",inFile);
    topTextBox.setScale(2);
    topTextBox.setLocation(350, 50);

    //Boolean values to let the program know when the next phase or level occurs.
    bool nextPhase = true;
    bool nextLevel = true;

    //When this is true, the program stops spawning enemies.
    bool waitForPhaseToEnd = false;

    //Integer values that hold the current level and phase.
    int level = 0;
    int phase = 0;

    //Object that reads a file that contains a list of enemies
    EnemySpawner enemySpawner;

    //Object that controls every aspect of every enemy
    Enemies allEnemies(pipe0, pipe1);

    //Object that deals with scores
    Score scoreKeeper;

    //Draw the introductory screen
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
    //Wait until the player presses x
    while (p.getKey() != 'X'){
        p.kbhit();
        if (p.getQuit()){
            return 1;
        }
    }

    //The loop of the game
    while (!p.getQuit()){

        //This code is executed during a level transition
        if (nextLevel){
            level++;
            //Set the visuals of the level to correspond with the level number
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

                //End screen, for when level is greater than 5
                drawBlackBackground(800,400,p);
                ostringstream writer;
                writer << "Thanks for playing!\nYour score is ";
                writer << score;

                scoreKeeper.storeScores();

                //Set the top score
                if (score > scoreKeeper.getScore(0)){
                    scoreKeeper.setScore(score, 0);
                }

                scoreKeeper.storeScores();

                //Display the top score
                writer << "\nTop score is " << scoreKeeper.getScore(0);
                center.setLocation(100,200);
                center.setText(writer.str());
                center.draw(p);
                p.update();
                //Wait for the player to exit the program
                while (!p.getQuit()){
                    p.kbhit();
                }
            }

            //Exit the program after the end screen
            if (level > 5){
                return 1;
            }


            //Code that is executed at the start of every level

            //Show the player that a new level is starting
            p.clear();
            drawBlackBackground(800, 400, p);
            ostringstream writer;
            writer << "Level " << level;
            writer.flush();
            center.setText(writer.str());
            center.draw(p);
            p.update();
            p.Sleep(1000);

            //Reset everything about the level
            nextLevel = false;
            lives = 10;
            pow.setCurrentFrame(0);
            enemySpawnTimer = 0;
            allEnemies.clearEnemies();
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

        //This code is executed every frame

        //Spawn an enemy every 150 frames
        if (enemySpawnTimer == 150 && !waitForPhaseToEnd){

            waitForPhaseToEnd = allEnemies.addEnemy(enemySpawner.getNextEnemy(), inFile);
            enemySpawnTimer = 0;
        }

        enemySpawnTimer++;

        //Update the player's location
        player.updateLocation();

        //This code executes if a player hits his head under a pow box.
        if (player.getCBox().hitHeadUnder(powBox) && pow.getCurrentFrame() < 3){

            //Create random waves on the platforms
            for (int t = 0; t < 300; t++){

                int randPlat = rand()%level1.numOfPlatforms();
                int randX = rand()&level1.getPlatform(randPlat).numOfColumns();
                level1.addWaveAnimation(randPlat,randX);

            }

            //bump all of the enemies
            for (int ID = 0; ID < allEnemies.getEnemyCBoxes().size(); ID++){
                if (allEnemies.stateOfEnemy(ID) == grounded || allEnemies.stateOfEnemy(ID) == bumpedAndGrounded || allEnemies.stateOfEnemy(ID) == aliveAndFalling){
                    allEnemies.bumpEnemy(ID);
                }
            }

            //Pause the screen for a short amount of time
            p.Sleep(10);

            //Shorten the pow block every time it is used
            pow.nextFrame();
            if (pow.getCurrentFrame() == 3){
                removeCollisionBox(solids, "pow");
            }
        }

        /*Check if the player has touched any solid objects, and prevent the player
        from passing through them.*/
        player.solidCollisions(solids, level1);

        //Check the player's collisions with enemies
        if (!player.getDead()){
            for (int i = 0; i < allEnemies.getEnemyCBoxes().size(); i++){

                //Create reference variables with shorter names
                CollisionBox& hurtBox = allEnemies.getEnemyHurtBoxes()[i];
                CollisionBox& hitBox = allEnemies.getEnemyCBoxes()[i];
                CollisionBox& c = player.getCBox();

                //This code executes if the player's fist hits the enemy's hurtBox, which is below the platform.
                if (player.getFist().hitHeadUnder(hurtBox) && (allEnemies.stateOfEnemy(hurtBox.ID) == grounded || allEnemies.stateOfEnemy(hurtBox.ID) == bumpedAndGrounded)){
                    allEnemies.bumpEnemy(hurtBox.ID);
                }

                //This code executes if the player touches the enemy.
                if (c.isTouching(hitBox)){

                    touch.playSound();

                    //If the enemy has been bumped and is on the ground, kick the enemy down and increase your score.
                    if (allEnemies.stateOfEnemy(hitBox.ID) == bumpedAndGrounded){
                        allEnemies.kickEnemyIfBumped(hitBox.ID, player.getXVel()/2.0);
                        score += 800;

                    }

                    //If the enemy has not been bumped, take one life away from the player.
                    else if ( !player.getInvincible() && (allEnemies.stateOfEnemy(hitBox.ID) == grounded || allEnemies.stateOfEnemy(hitBox.ID) == aliveAndFalling) ){
                        player.setYVel(-2);
                        player.setXVel(0);
                        player.setFalling(true);
                        player.getSprite().setCurrentFrame(6);
                        player.setDead(true);
                        lives--;
                        die.playSound();

                        //This codes executes if the player loses all of their lives.
                        if (lives == 0){

                            //Draw the game over screen
                            drawBlackBackground(800,400,p);
                            TextBox gameOver("letters.txt",inFile);
                            gameOver.setLocation(350,50);
                            gameOver.setScale(2);
                            gameOver.setText("Game over");
                            gameOver.draw(p);
                            gameOver.setLocation(250,100);
                            gameOver.setText("press x to keep playing");
                            gameOver.draw(p);
                            gameOver.setLocation(250,150);
                            gameOver.setText("Score");
                            gameOver.draw(p);
                            Number halfScore("digits.txt",inFile);
                            halfScore.setScale(2);
                            halfScore.setLocation(350,150);
                            halfScore.setNumber(score);
                            halfScore.draw(p);
                            p.update();
                            while(p.getKey() != 'X'){
                                p.kbhit();
                                if (p.getQuit()){
                                    return 1;
                                }
                            }

                            //Show that the player's score gets divided in half when they lose all of their lives.
                            int originalScore = score;
                            score /= 2;
                            for (int c = originalScore; c >= score; c-=(originalScore-score)/100 ){
                                if (c < score){
                                    c = score;
                                }
                                p.clear();
                                drawBlackBackground(800,400,p);
                                gameOver.setLocation(350,50);
                                gameOver.setScale(2);
                                gameOver.setText("Game over");
                                gameOver.draw(p);
                                gameOver.setLocation(250,100);
                                gameOver.setText("press x to keep playing");
                                gameOver.draw(p);
                                gameOver.setLocation(250,150);
                                gameOver.setText("Score");
                                gameOver.draw(p);
                                halfScore.setNumber(c);
                                halfScore.draw(p);
                                p.update();
                                p.Sleep(2);
                            }

                            p.Sleep(1000);

                            lives = 10;

                        }

                    }

                }

            }
        }

        //Check if there are zero enemies, and if all of the enemies in the phase have been spawned already.
        //If that is the case, set nextPhase to true.
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

        //Update the locations of all of the enemies.
        allEnemies.updateLocations();

        //Update a vector of collision boxes for all of the enemies
        allEnemies.updateCollisionBoxes();

        //Make sure that none of the enemies pass through any solids
        allEnemies.solidCollisions(solids);

        //Add freeze animations where any slip ices have self-destructed
        for (int i = 0; i < allEnemies.getSlipices().size(); i++){

            Slipice& slip = allEnemies.getSlipices()[i];

            Platform& p = level1.getPlatform(slip.platNumber);

            if (slip.getSelfDestruct() && slip.getSprite().getCurrentFrame() == 4){
                level1.addFreezeAnimation("leftIce.txt","middleIce.txt","rightIce.txt",inFile,2,slip.platNumber,
                                          (slip.getX() - p.get_x())/p.getBlock(0).getWave().getSprite().getScaledWidth(0) );
            }

        }


        // Draw Black
        drawBlackBackground(screenWidth, screenHeight, p);

        // Get User Input
        p.kbhit();
        key_pressed = p.getKey();
        player.onKeyPress(key_pressed);

        //This is a back door to be able to see the other levels easily.
        if (key_pressed == ' '){
            nextLevel = true;
        }

        //This is a back door to be able to easily increase your score.
        //This resets the pow block, which normally resets at the beginning of
        //each level.
        if (key_pressed == 'P'){
            removeCollisionBox(solids,"pow");
            solids.push_back(powBox);
            pow.setCurrentFrame(0);
        }

        //Draw the brick floor
        horizontalTile(brickFloor, 0, screenWidth, p);

        //Draw each enemy
        allEnemies.draw(p);

        //Draw the two upper pipes.
        spawnPipeLeft.draw(p);
        spawnPipeRight.draw(p);

        //Draw the two lower pipes.
        bottomLeftPipe.draw(p);
        bottomRightPipe.draw(p);

        //Draw all of the platforms, which are contained in a Level class.
        level1.draw(p);

        //Draw the pow block
        pow.draw(p);

        //Draw the player
        player.draw(p);

        //Draw the player's lives in the upper left corner
        drawLives(life, 0, 0, lives, p);

        //Update and draw the player's score at the top of the screen
        scoreDisplay.setNumber(score);
        scoreDisplay.draw(p);

        //Indicate to the player when a new phase has begun
        if (nextPhase){
            ostringstream writer;
            writer << "Phase " << phase;
            topTextBox.setText(writer.str());
            topTextBox.draw(p);
            if (enemySpawnTimer == 100){
                nextPhase = false;
            }
        }

        //Update the plotter
        p.update();

        //Pause the game for 2 milliseconds
        p.Sleep(2);

    }

    return 0;
}

/*This function causes a Level object to place 7 platforms in a symmetrical
pattern*/
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
