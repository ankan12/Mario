#include "Sidestepper.h"
#include <cstdlib>
#include <cmath>
using namespace std;

Sidestepper::Sidestepper(char filename[], ifstream& inFile, int scale, int pipe, Pipe& pipe0, Pipe& pipe1){

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

    angerCounter = 0;

}

double Sidestepper::getX(){
    return x;
}
double Sidestepper::getY(){
    return y;
}
double Sidestepper::getXVel(){
    return xVelocity;
}
double Sidestepper::getYVel(){
    return yVelocity;
}
double Sidestepper::getYAccel(){
    return yAccel;
}

void Sidestepper::setX(double x){
    this->x = x;
}
void Sidestepper::setY(double y){
    this->y = y;
}
void Sidestepper::setXVel(double xVelocity){
    this->xVelocity = xVelocity;
}
void Sidestepper::setYVel(double yVelocity){
    this->yVelocity = yVelocity;
}
void Sidestepper::setYAccel(double yAccel){
    this->yAccel = yAccel;
}

void Sidestepper::setFalling(bool falling){
    this->falling = falling;
}
bool Sidestepper::isFalling(){
    return falling;
}

Sprite& Sidestepper::getSprite(){
    return sprite;
}

void Sidestepper::draw(SDL_Plotter& p){

    if (state == deadAndInvisible){
        return;
    }

    int cf = sprite.getCurrentFrame();

    switch (state){

    case aliveAndFalling:
        if (angerCounter > 0){
            if (cf != 2){
                sprite.setCurrentFrame(2);
            }
            break;
        }

        if (cf != 0){
            sprite.setCurrentFrame(0);
            a = 0;
        }
        break;

    case grounded:
        if (angerCounter > 0){
            if (a > 1){
                if (cf == 2){
                    sprite.setCurrentFrame(3);
                }
                else{
                    sprite.setCurrentFrame(2);
                }
                a = 0;
            }
            break;
        }

        if (a > 1){
            sprite.setCurrentFrame(cf+1);
            if (sprite.getCurrentFrame() > 1){
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
            sprite.setCurrentFrame(4);
            a = 0;
        }
        break;

    case bumpedAndGrounded:
        if ( ((int)a) % 5 == 0){
            if (a > 35){
                sprite.setCurrentFrame(0);
                state = grounded;

                if (xVelocity > 0){
                    sprite.setMirrored(false);
                }
                else{
                    sprite.setMirrored(true);
                }
            }
            else{
                if (sprite.getCurrentFrame() == 5){
                    sprite.setCurrentFrame(6);
                }
                else{
                    sprite.setCurrentFrame(5);
                }
            }
        }
        break;

    case turningAround:

        if (a < 2){
            sprite.setCurrentFrame(7);
        }
        else if (a < 4){
            sprite.setCurrentFrame(8);
        }
        else if (a < 6){
            sprite.setCurrentFrame(7);
        }
        else{
            sprite.setCurrentFrame(0);
            state = grounded;
            if (sprite.mirrored()){
                sprite.setMirrored(false);
            }
            else{
                sprite.setMirrored(true);
            }
        }
        break;

    case deadAndFalling:
        if (cf != 4){
            sprite.setCurrentFrame(4);
        }
        break;

    case enteringPipe:
        if (angerCounter > 0){
            if (cf != 2){
                sprite.setCurrentFrame(2);
            }
            break;
        }

        if (cf != 0){
            sprite.setCurrentFrame(0);
        }
        break;

    case exitingPipe:
        if (angerCounter > 0){
            if (cf != 2){
                sprite.setCurrentFrame(2);
            }
            break;
        }


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

CollisionBox& Sidestepper::getCBox(){
    return cBox;
}

void Sidestepper::solidCollisions(vector<CollisionBox>& solids){

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

void Sidestepper::updateLocation(){
    printState();
    cout << cBox.ID << endl;

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
    hurtBox.moveToLocation(x, y + cBox.getHeight());

}


CollisionBox& Sidestepper::getHurtBox(){

    return hurtBox;
}

void Sidestepper::setState(EnemyState state){
    this->state = state;
}

EnemyState Sidestepper::getState(){
    return state;
}

void Sidestepper::printState(){

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

void Sidestepper::setSpeedFactor(int input){
    speedFactor = input;
}

int Sidestepper::getSpeedFactor(){
    return speedFactor;
}

void Sidestepper::setAngerCounter(int input){
    angerCounter = input;
}

int Sidestepper::getAngerCounter(){
    return angerCounter;
}

