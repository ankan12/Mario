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
#include "Slipice.h"
#include <cstdlib>
#include <cmath>
using namespace std;

Slipice::Slipice(char filename[], ifstream& inFile, int scale, int pipe, Pipe& pipe0, Pipe& pipe1){

    sprite.loadImage(filename, inFile);
    sprite.setScale(scale);

    cBox.fitToSprite(sprite);
    cBox.type = "enemy";
    hurtBox.setWidth(cBox.getWidth());
    hurtBox.setHeight(24);

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

    selfDestruct = false;
    deadTimer = 0;

    platNumber = -1;

}

double Slipice::getX(){
    return x;
}
double Slipice::getY(){
    return y;
}
double Slipice::getXVel(){
    return xVelocity;
}
double Slipice::getYVel(){
    return yVelocity;
}
double Slipice::getYAccel(){
    return yAccel;
}

void Slipice::setX(double x){
    this->x = x;
}
void Slipice::setY(double y){
    this->y = y;
}
void Slipice::setXVel(double xVelocity){
    this->xVelocity = xVelocity;
}
void Slipice::setYVel(double yVelocity){
    this->yVelocity = yVelocity;
}
void Slipice::setYAccel(double yAccel){
    this->yAccel = yAccel;
}

void Slipice::setFalling(bool falling){
    this->falling = falling;
}
bool Slipice::isFalling(){
    return falling;
}

Sprite& Slipice::getSprite(){
    return sprite;
}

void Slipice::draw(SDL_Plotter& p){

    if (state == deadAndInvisible){
        return;
    }
    int cf = sprite.getCurrentFrame();

    if (selfDestruct){

        if (a > 5){
            a = 0;
            sprite.setCurrentFrame(cf+1);
            if (sprite.getCurrentFrame() == 5){
                state = deadAndInvisible;
                return;
            }
        }

    }

    switch (state){

    case aliveAndFalling:
        if (cf != 0){
            sprite.setCurrentFrame(0);
            a = 0;
        }
        break;

    case grounded:{
        if (cf != 0){
            sprite.setCurrentFrame(0);
            a = 0;
        }

        int r = rand() % 1000;

        if (r == 0 && platNumber != -1){
            selfDestruct = true;
            state = turningAround;
            a = 0;
        }

        break;
    }
    case bumpedAndFalling:
        break;

    case bumpedAndGrounded:
        break;

    case turningAround:
        break;

    case deadAndFalling:
        if (a > 5){

            a = 0;

            int f = cf+1;

            if (f > 8){
                state = deadAndInvisible;
                break;
            }

            sprite.setCurrentFrame(cf+1);

        }
        break;

    case enteringPipe:
        if (cf != 0){
            sprite.setCurrentFrame(0);
            a = 0;
        }
        break;

    case exitingPipe:
        if (cf != 0){
            sprite.setCurrentFrame(0);
            a = 0;
        }
        break;

    default:
        break;
    }

    sprite.setLocation(x, y);
    sprite.draw(p);
    a += animationSpeed;

}

CollisionBox& Slipice::getCBox(){
    return cBox;
}

void Slipice::solidCollisions(vector<CollisionBox>& solids){

    if (!(state == aliveAndFalling || state == grounded || state == bumpedAndFalling)){
        return;
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

            if (b.type == "platform"){
                platNumber = b.ID;
            }
            else{
                platNumber = -1;
            }

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

            if (state == grounded){
                state = turningAround;
                return;
            }

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

            if (state == grounded){
                state = turningAround;
                return;
            }

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

void Slipice::updateLocation(){

    if (selfDestruct){
        return;
    }

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
        break;

    case bumpedAndGrounded:
        break;

    case deadAndFalling:
        if (yVelocity < 5){
            yVelocity += yAccel;
        }
        x += xVelocity;
        y += yVelocity;

        if (y > 400){
            state = deadAndInvisible;
        }

        break;

    case deadAndInvisible:
        if (yVelocity != 0){
            yVelocity = 0;
        }
        if (xVelocity != 0){
            xVelocity = 0;
        }
        deadTimer++;
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
    hurtBox.moveToLocation(x, y + cBox.getHeight());

}

CollisionBox& Slipice::getHurtBox(){
    return hurtBox;
}

void Slipice::setState(EnemyState state){
    this->state = state;
}

EnemyState Slipice::getState(){
    return state;
}

void Slipice::printState(){

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

int Slipice::getDeadTimer(){
    return deadTimer;
}

bool Slipice::getSelfDestruct(){
    return selfDestruct;
}
