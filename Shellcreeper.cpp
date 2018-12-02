#include "Shellcreeper.h"
#include <cstdlib>
#include <cmath>
using namespace std;

Shellcreeper::Shellcreeper(char filename[], ifstream& inFile, int scale, int pipe, Pipe& pipe0, Pipe& pipe1){

    sprite.loadImage(filename, inFile);
    sprite.setScale(scale);

    cBox.fitToSprite(sprite);
    cBox.type = "enemy";
    hitBox.setWidth(cBox.getWidth());
    hitBox.setHeight(24);

    this->pipe0.assignToPipe(pipe0);
    this->pipe1.assignToPipe(pipe1);

    yVelocity = 0;
    yAccel = 0.1;

    groundStart = 0;
    groundEnd = 800;

    distanceInPipe = -1;

    a = 0.0;
    animationSpeed = 0.1;

    pipeSpeed =  0.3;

    speedFactor = 1;

    setState(exitingPipe);

    if (pipe == 0){
        pipeThatIAmIn.assignToPipe(pipe0);
        xVelocity = 0.75;
    }
    else{
        pipeThatIAmIn.assignToPipe(pipe1);
        xVelocity = -0.75;
        sprite.setMirrored(true);
    }

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

void Shellcreeper::setFalling(bool falling){
    this->falling = falling;
}
bool Shellcreeper::isFalling(){
    return falling;
}

Sprite& Shellcreeper::getSprite(){
    return sprite;
}

void Shellcreeper::draw2(SDL_Plotter& p){

    if (state == deadAndInvisible){
        return;
    }

    int cf = sprite.getCurrentFrame();

    switch (state){

    case aliveAndFalling:
        if (cf != 0){
            sprite.setCurrentFrame(0);
            a = 0;
        }
        break;

    case grounded:
        if (a > 1){
            sprite.setCurrentFrame(cf+1);
            if (sprite.getCurrentFrame() > 3){
                sprite.setCurrentFrame(0);
            }
            a = 0;
        }
        break;

    case bumpedAndFalling:

        if (sprite.mirrored()){
            sprite.setMirrored(false);
        }

        if (cf != 8){
            sprite.setCurrentFrame(8);
            a = 0;
        }
        break;

    case bumpedAndGrounded:
        if (a > 3){
            a = 0;
            if (cf == 15){
                sprite.setCurrentFrame(0);
                state = grounded;
                if (xVelocity == 0){
                }
                if (xVelocity > 0){
                    sprite.setMirrored(false);
                }
                else{
                    sprite.setMirrored(true);
                }
            }
            else{
                sprite.setCurrentFrame(cf+1);
            }
        }
        break;

    case turningAround:

        if (a > 2){
            a = 0;
            if (cf == 7){
                sprite.setCurrentFrame(0);
                state = grounded;
                if (sprite.mirrored()){
                    sprite.setMirrored(false);
                }
                else{
                    sprite.setMirrored(true);
                }

            }
            else{
                sprite.setCurrentFrame(cf + 1);
            }
        }
        break;

    case deadAndFalling:
        if (cf != 12){
            sprite.setCurrentFrame(12);
        }
        break;

    case enteringPipe:
        if (cf != 0){
            sprite.setCurrentFrame(0);
        }
        break;

    case exitingPipe:
        if (cf != 0){
            sprite.setCurrentFrame(0);
        }
        break;

    default:
        break;
    }

    sprite.setLocation(x, y);
    sprite.draw(p);
    a += animationSpeed;

}

CollisionBox& Shellcreeper::getCBox(){
    return cBox;
}

void Shellcreeper::solidCollisions2(vector<CollisionBox>& solids){

    if (!(state == aliveAndFalling || state == grounded || state == bumpedAndFalling)){
        return;
    }

    if (state == aliveAndFalling){
    }
    if (state == enteringPipe){
    }

    for (int i = 0; i < solids.size(); i++){

        CollisionBox& b = solids[i];

        if (cBox.type == b.type && cBox.ID == b.ID){
            continue;
        }

        if (b.type == "ignore"){
            continue;
        }

        if (cBox.jumpedOn(b) && state != grounded){
            cBox.solidInteraction(b, -90);
            yVelocity = 0;
            groundStart = b.get_x();
            groundEnd = b.get_x() + b.getWidth();

            switch (state){

            case aliveAndFalling:
                state = grounded;
                sprite.setCurrentFrame(0);
                break;

            case bumpedAndFalling:
                state = bumpedAndGrounded;
                break;

            default:
                break;
            }
            continue;

        }
        if (cBox.hitRightOf(b)){
            cBox.solidInteraction(b, 180);

            xVelocity = 0.75  * speedFactor;

            switch(state){

            case aliveAndFalling:
                if (sprite.mirrored()){
                    sprite.setMirrored(false);
                }
                else{
                    sprite.setMirrored(true);
                }
                break;

            case grounded:
                sprite.setCurrentFrame(5);
                state = turningAround;
                break;

            default:
                break;
            }

        }
        if (cBox.hitLeftOf(b)){
            cBox.solidInteraction(b, 0);

            xVelocity = -0.75 * speedFactor;

            switch(state){

            case aliveAndFalling:
                if (sprite.mirrored()){
                    sprite.setMirrored(false);
                }
                else{
                    sprite.setMirrored(true);
                }
                break;

            case grounded:
                sprite.setCurrentFrame(5);
                state = turningAround;
                break;

            default:
                break;
            }

        }
        if (cBox.hitHeadUnder(b)){
            cBox.solidInteraction(b, 90);
            yVelocity = 0;
        }

    }

    if (cBox.isTouching(pipe0.entrance)){
        pipeThatIAmIn.assignToPipe(pipe0);
        state = enteringPipe;
        speedFactor += 0.2;
        xVelocity = 0.75 * speedFactor;
        sprite.setMirrored(false);
        cBox.type = "ignore";
    }

    if (cBox.isTouching(pipe1.entrance)){
        pipeThatIAmIn.assignToPipe(pipe1);
        state = enteringPipe;
        speedFactor += 0.2;
        xVelocity = -0.75 * speedFactor;
        sprite.setMirrored(true);
        cBox.type = "ignore";
    }

}

void Shellcreeper::updateLocation2(){
    switch (state){
    case aliveAndFalling:

        if (yVelocity < 5){
            yVelocity += yAccel;
        }
        x += xVelocity;
        y += yVelocity;
        break;

    case grounded:

        if (yVelocity != 0){
            yVelocity = 0;
        }

        x += xVelocity;

        if (x > groundEnd || x + cBox.getWidth() < groundStart){
            state = aliveAndFalling;
            groundStart = 0;
            groundEnd = 800;
        }

        break;

    case exitingPipe:
        if (distanceInPipe == -1){
            if (pipeThatIAmIn.direction == "right"){
                x = pipeThatIAmIn.exitX - cBox.getWidth();
                y = pipeThatIAmIn.exitY;
                cBox.resetAtLocation(x, y);
            }
            else {
                x = pipeThatIAmIn.exitX;
                y = pipeThatIAmIn.exitY;
            }

            distanceInPipe = 0;
        }

        if (pipeThatIAmIn.direction == "right"){
            x += pipeSpeed;
        }
        else{
            x-= pipeSpeed;
        }

        distanceInPipe += pipeSpeed;

        if (distanceInPipe > cBox.getWidth()){
            distanceInPipe = -1;
            state = aliveAndFalling;
            cBox.resetAtLocation(x, y);
            cBox.type = "enemy";
        }
        break;

    case enteringPipe:
        if (distanceInPipe == -1){
            if (pipeThatIAmIn.direction == "right"){
                x = pipeThatIAmIn.entranceX - cBox.getWidth();
                y = pipeThatIAmIn.entranceY;
                cBox.resetAtLocation(x, y);
                xVelocity = 0.75 * speedFactor;
            }
            else {
                x = pipeThatIAmIn.entranceX;
                y = pipeThatIAmIn.entranceY;
                xVelocity = -0.75 * speedFactor;
            }

            distanceInPipe = 0;
        }

        if (pipeThatIAmIn.direction == "right"){
            x += pipeSpeed;
        }
        else{
            x-= pipeSpeed;
        }

        distanceInPipe += pipeSpeed;


        if (distanceInPipe > cBox.getWidth()){
            distanceInPipe = -1;
            state = exitingPipe;
        }
        break;

    case bumpedAndFalling:
        if (yVelocity < 5){
            yVelocity += yAccel;
        }
        y += yVelocity;
        break;

    case bumpedAndGrounded:

        if (yVelocity != 0){
            yVelocity = 0;
        }

        break;

    case deadAndFalling:
        if (yVelocity < 5){
            yVelocity += yAccel;
        }
        x += xVelocity;
        y += yVelocity;
        break;

    case deadAndInvisible:
        if (yVelocity != 0){
            yVelocity = 0;
        }
        if (xVelocity != 0){
            xVelocity = 0;
        }
        break;

    default:
        break;

    }

        if (x < 0){
            x = 800 + x;
            y -= 8;
            if (state == grounded){
                state = aliveAndFalling;
            }
        }
        if (x > 800){
            x = x - 800;
            y -= 8;
            if (state == grounded){
                state = aliveAndFalling;
            }
        }

    cBox.moveToLocation(x, y);
    hitBox.moveToLocation(x, y + cBox.getHeight());

}


CollisionBox& Shellcreeper::getHitBox(){

    return hitBox;
}

void Shellcreeper::setState(EnemyState state){
    this->state = state;
}

EnemyState Shellcreeper::getState(){
    return state;
}

void Shellcreeper::printState(){

    switch(state){
    case grounded:
        cout << "grounded" << endl;
        return;
    case aliveAndFalling:
        cout << "aliveAndFalling" << endl;
        return;
    case bumpedAndFalling:
        cout << "bumpedAndFalling" << endl;
        return;
    case bumpedAndGrounded:
        cout << "bumpedAndGrounded" << endl;
        return;
    case enteringPipe:
        cout << "enteringPipe" << endl;
        return;
    case exitingPipe:
        cout << "exitingPipe" << endl;
        return;
    case deadAndFalling:
        cout << "deadAndFalling" << endl;
        return;
    case deadAndInvisible:
        cout << "deadAndInvisible" << endl;
        return;

    }

}
