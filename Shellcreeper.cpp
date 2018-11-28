#include "Shellcreeper.h"
#include <cstdlib>
#include <cmath>
using namespace std;

Shellcreeper::Shellcreeper(char filename[], ifstream& inFile, int scale, int pipe){

    sprite.loadImage(filename, inFile);
    sprite.setScale(scale);

    if (pipe == 0){
        spawnX = 64;
        spawnY = 50;
        x = spawnX;
        y = spawnY;
        xVelocity = 0.75;
    }
    else{
        spawnX = 800-64-34;
        spawnY = 50;
        x = spawnX;
        y = spawnY;
        xVelocity = -0.75;
        sprite.setMirrored(true);
    }

    this->pipe = pipe;
    pipeQueue = queueUpdated.size();
    queueUpdated.push_back(false);

    sprite.setLocation(x, y);

    cBox.setWidth(34);
    cBox.setHeight(sprite.getScaledHeight(0));
    hitBox.setWidth(34);
    hitBox.setHeight(24);

    cBox.type == "enemy";

    cBox.resetAtLocation(x, y);
    hitBox.resetAtLocation(x, y + cBox.getHeight());

    falling = true;
    spawning = true;
    bumped = false;
    dead = false;

    a = 0.0;
    animationSpeed = 0.1;

    yVelocity = 0.0;
    yAccel = 0.1;

    groundStart = 0;
    groundEnd= 800;

    speedFactor = 1;

    exitX = 740;
    exitY = 320;

    turningAround = false;

}

double Shellcreeper::getX(){
    return x;
}
double Shellcreeper::getY(){
    return y;
}
double Shellcreeper::getXVel(){
    return xVelocity;
}
double Shellcreeper::getYVel(){
    return yVelocity;
}
double Shellcreeper::getYAccel(){
    return yAccel;
}

void Shellcreeper::setX(double x){
    this->x = x;
}
void Shellcreeper::setY(double y){
    this->y = y;
}
void Shellcreeper::setXVel(double xVelocity){
    this->xVelocity = xVelocity;
}
void Shellcreeper::setYVel(double yVelocity){
    this->yVelocity = yVelocity;
}
void Shellcreeper::setYAccel(double yAccel){
    this->yAccel = yAccel;
}

void Shellcreeper::setExit(double x, double y){

    exitX = x;
    exitY = y;

}

void Shellcreeper::setFalling(bool falling){
    this->falling = falling;
}
bool Shellcreeper::isFalling(){
    return falling;
}

Sprite& Shellcreeper::getSprite(){
    return sprite;
}

void Shellcreeper::draw(SDL_Plotter& p){

    if (dead && y > 350){
        return;
    }

    if (!falling && a > 1 && !bumped){
        int cf = sprite.getCurrentFrame();
        sprite.setCurrentFrame(cf+1);
        if (sprite.getCurrentFrame()>3){
            sprite.setCurrentFrame(0);
        }
        a = 0;

    }

    sprite.setLocation(x, y);
    sprite.draw(p);
    a += animationSpeed;
}

CollisionBox& Shellcreeper::getCBox(){
    return cBox;
}

void Shellcreeper::solidCollisions(vector<CollisionBox>& solids, Level& level){

    if (dead){
        return;
    }

    for (int i = 0; i < solids.size(); i++){

        CollisionBox& b = solids[i];

        if (b.type == "enemy"){
            if (cBox.hitLeftOf(b)){
                cBox.solidInteraction(b, 180);
                xVelocity*=-1;
                sprite.setMirrored(true);
            }
            if (cBox.hitRightOf(b)){
                cBox.solidInteraction(b, 0);
                xVelocity*=-1;
                sprite.setMirrored(false);
            }
            continue;

        }

        if (cBox.jumpedOn(b)){
            cout << "Landed" << endl;
            falling = false;
            if (!bumped){
                sprite.setCurrentFrame(0);
            }
            yVelocity = 0;
            cBox.solidInteraction(b,-90);
            groundStart = b.get_x();
            groundEnd = b.get_x()+b.getWidth();
        }
        if (cBox.hitHeadUnder(b)){
            yVelocity = 0;
            cBox.solidInteraction(b,90);
        }

//        if (cBox.hitLeftOf(b)){
//            sprite.setMirrored(true);
//            xVelocity = -0.75;
//        }
//        if (cBox.hitRightOf(b)){
//            sprite.setMirrored(false);
//            xVelocity = 0.75;
//        }


    }
    x = cBox.get_x();
    y = cBox.get_y();
}

void Shellcreeper::updateLocation(){

    if (dead && y > 350){
        yAccel = 0;
        xVelocity = 0;
        yVelocity = 0;
        //sprite.setCurrentFrame(sprite.getTotalFrames()-1);
        return;
    }

    if (abs(static_cast<double>(x)) > exitX && abs(static_cast<double>(y)) > exitY){

        if (x < 400.0){
            spawnX = 800-64-34;
            pipe = 1;
            xVelocity = -0.75;
            sprite.setMirrored(true);
        }
        else{
            spawnX = 64;
            pipe = 0;
            xVelocity = 0.75;
            sprite.setMirrored(false);
        }

        x = spawnX;
        y = spawnY;
        spawning = true;
        falling = true;

    }

    if (spawning == true){
        if (pipe == 0){
            if (x > spawnX + cBox.getWidth()){
                spawning = false;
            }
        }
        else{
            if (x + cBox.getWidth() < spawnX){
                spawning = false;
            }
        }
    }



    if (spawning){
        spawn();
    }

    if (falling && yVelocity < 5){
            yVelocity += yAccel;
        }

        if (((cBox.get_x() + cBox.getWidth() < groundStart) ||
            (cBox.get_x() > groundEnd)) && !falling){

            falling = true;

            sprite.setCurrentFrame(0);

            groundStart = 0;
            groundEnd = 800;
        }

        x += xVelocity * speedFactor;
        y += yVelocity * speedFactor;

        if (x < 0){
            x = 800 + x;
            y -= 4;
            falling = true;

        }
        if (x >= 800){
            x = x - 800;
            y -= 4;
            falling = true;
        }


        cBox.moveToLocation(x, y);
        hitBox.moveToLocation(x, y + cBox.getHeight());

}

void Shellcreeper::turnAround(){



}

void Shellcreeper::spawn(){

    x += xVelocity/2.0;
    cBox.moveToLocation(x, y);
    return;
}

CollisionBox& Shellcreeper::getHitBox(){

    return hitBox;
}
bool Shellcreeper::getBumped(){
    return bumped;
}
void Shellcreeper::setBumped(bool value){
    bumped = value;
}
bool Shellcreeper::getDead(){
    return dead;
}
void Shellcreeper::setDead(bool value){
    dead = value;
}
