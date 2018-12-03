#include "Shellcreeper.h"
#include <cstdlib>
#include <cmath>
using namespace std;


/*
 * description: constructor for the shellcreeper class
 * return: NA
 * precondition: instance of shellcreeper exists
 * postcondition: all variables initialized to input
 *
*/
Shellcreeper::Shellcreeper(char filename[], ifstream& inFile, int scale, int pipe, Pipe& pipe0, Pipe& pipe1){

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

}

/*
 * description: returns x
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
double Shellcreeper::getX(){
    return x;
}

/*
 * description: returns y
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
double Shellcreeper::getY(){
    return y;
}

/*
 * description: returns x velocity
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
double Shellcreeper::getXVel(){
    return xVelocity;
}

/*
 * description: returns y velocity
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
double Shellcreeper::getYVel(){
    return yVelocity;
}

/*
 * description: returns y acceleration
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
double Shellcreeper::getYAccel(){
    return yAccel;
}

/*
 * description: sets x
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: x is set
 *
*/
void Shellcreeper::setX(double x){
    this->x = x;
}

/*
 * description: sets y
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: y is set
 *
*/
void Shellcreeper::setY(double y){
    this->y = y;
}

/*
 * description: sets x velocity
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: x velocity is set
 *
*/
void Shellcreeper::setXVel(double xVelocity){
    this->xVelocity = xVelocity;
}

/*
 * description: sets y velocity
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: y velocity is set
 *
*/
void Shellcreeper::setYVel(double yVelocity){
    this->yVelocity = yVelocity;
}

/*
 * description: sets y acceleration
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: y velocity is set
 *
*/
void Shellcreeper::setYAccel(double yAccel){
    this->yAccel = yAccel;
}

/*
 * description: sets boolean Falling
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: falling boolean is set
 *
*/
void Shellcreeper::setFalling(bool falling){
    this->falling = falling;
}

/*
 * description: returns falling boolean
 * return: bool
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
bool Shellcreeper::isFalling(){
    return falling;
}

/*
 * description: gets sprite by reference
 * return: sprite
 * precondition: instance of shellcreeper exists
 * postcondition: sprite is returned
 *
*/
Sprite& Shellcreeper::getSprite(){
    return sprite;
}


/*
 * description: draws to the screen
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
void Shellcreeper::draw(SDL_Plotter& p){
=======

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

/*
 * description: gets collision box and passes by reference
 * return: Collision box
 * precondition: instance of shellcreeper exists
 * postcondition: CBox is passed by reference
 *
*/
CollisionBox& Shellcreeper::getCBox(){
    return cBox;
}


  /*
 * description: determins sprite action based on collision
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: sprite variables are set to as needed
 *
*/
void Shellcreeper::solidCollisions(vector<CollisionBox>& solids){


void Shellcreeper::solidCollisions2(vector<CollisionBox>& solids){
    Music sc("mb_sc.wav"); //initialize sound for shell creeper spawning


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

        sc.playSound(); //play spawn sound

        pipeThatIAmIn.assignToPipe(pipe0);
        state = enteringPipe;
        speedFactor += 0.2;
        xVelocity = 0.75 * speedFactor;
        sprite.setMirrored(false);
        cBox.type = "ignore";
    }

    if (cBox.isTouching(pipe1.entrance)){
        sc.playSound(); //play spawn sound

        pipeThatIAmIn.assignToPipe(pipe1);
        state = enteringPipe;
        speedFactor += 0.2;
        xVelocity = -0.75 * speedFactor;
        sprite.setMirrored(true);
        cBox.type = "ignore";
    }

}


/*
 * description: this function updates the location variables
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: variables are set
 *
*/
void Shellcreeper::updateLocation(){

    Music sc("mb_sc.wav"); //initialize sound for shell creeper spawning


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
            sc.playSound(); //play spawn sound


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


/*
 * description: gets collision box and passes by reference
 * return: Collision box
 * precondition: instance of shellcreeper exists
 * postcondition: HitBox is passed by reference
 *
*/
CollisionBox& Shellcreeper::getHurtBox(){


    return hurtBox;
}

/*
 * description: sets state of class
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: variables are set
 *
*/
void Shellcreeper::setState(EnemyState state){
    this->state = state;
}

/*
 * description: returns enemy state
 * return: EnemyState
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
EnemyState Shellcreeper::getState(){
    return state;
}

/*
 * description: prints the state of the class
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
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
