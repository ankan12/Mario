#include "Plumber.h"


using namespace std;

Music newLife("mb_new.wav"); //load music files for player
Music jump("mb_jump.wav");
Music walking("walking.wav", 30);

/*
 * description: constructor for Plumber
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
Plumber::Plumber(char filename[], ifstream& inFile, int scale, int x, int y){

    sprite.loadImage(filename, inFile);
    sprite.setScale(scale);
    this->x = x;
    this->y = y;

    sprite.setLocation(x, y);

    cBox.setWidth(sprite.getScaledWidth(0));
    cBox.setHeight(sprite.getScaledHeight(0));

    cBox.resetAtLocation(x, y);

    falling = true;
    a = 0.0;
    animationSpeed = 0.1;

    xVelocity = 0.0;
    yVelocity = 0.0;
    yAccel = 0.05;

    groundStart = 0;
    groundEnd= 800;

    dead = false;

    invincible = false;

    invincibleTimer = 0;

}


/*
 * description: gets the x value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
double Plumber::getX(){
    return x;
}

/*
 * description: gets the y value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
double Plumber::getY(){
    return y;
}

/*
 * description: gets the x velocity value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
double Plumber::getXVel(){
    return xVelocity;
}

/*
 * description: gets the y velocity value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
double Plumber::getYVel(){
    return yVelocity;
}

/*
 * description: gets the y acceleration value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
double Plumber::getYAccel(){
    return yAccel;
}

/*
 * description: sets the x value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: x value is set
 *
*/
void Plumber::setX(double x){
    this->x = x;
}

/*
 * description: sets the y value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: y value is set
 *
*/
void Plumber::setY(double y){
    this->y = y;
}

/*
 * description: sets the x velocity value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: x velocity value is set
 *
*/
void Plumber::setXVel(double xVelocity){
    this->xVelocity = xVelocity;
}

/*
 * description: sets the y velocity value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: y velocity value is set
 *
*/
void Plumber::setYVel(double yVelocity){
    this->yVelocity = yVelocity;
}

/*
 * description: sets the y acceleration value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: y acceleration value is set
 *
*/
void Plumber::setYAccel(double yAccel){
    this->yAccel = yAccel;
}


/*
 * description: assigns boolean value to falling
 * return: void
 * precondition: class instance exists and bool passed in
 * postcondition: falling variable is set to true or false
 *
*/
void Plumber::setFalling(bool falling){
    this->falling = falling;
}

/*
 * description: returns the value of falling
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
bool Plumber::isFalling(){
    return falling;
}

/*
 * description: passes sprite by reference
 * return: Sprite
 * precondition: class instance exists and sprite linked
 * postcondition: sprite passed by reference
 *
*/
Sprite& Plumber::getSprite(){
    return sprite;
}

/*
 * description: uses SDL to draw to screen
 * return: void
 * precondition: class instance exists and plotter passed in
 * postcondition: information is printed to the screen
 *
*/
void Plumber::draw(SDL_Plotter& p){

    sprite.setLocation(x, y);

    if (invincible){
        if (invincibleTimer % 5 == 0){
            sprite.draw(p);
        }
        invincibleTimer++;
        a += animationSpeed;

        if (invincibleTimer > 100){
            invincible = false;
            invincibleTimer = 0;
        }

        return;
    }

    sprite.draw(p);
    a += animationSpeed;
}

/*
 * description: gets a collision box
 * return: CollisionBox
 * precondition: class instance exists and collisionbox file is linked
 * postcondition: Collision box is passed by reference
 *
*/
CollisionBox& Plumber::getCBox(){
    return cBox;
}

/*
 * description: uses collision boxes to determine movement and animation
 * return: void
 * precondition: class instance exists and header files linked
 * postcondition: nothing is returned
 *
*/
void Plumber::solidCollisions(vector<CollisionBox>& solids, Level& level){

    if (dead){
        return;
    }

    for (int i = 0; i < solids.size(); i++){

        CollisionBox& b = solids[i];

        if (cBox.hitHeadUnder(b)){
            yVelocity = 0;
            cBox.solidInteraction(b,90);
            if (b.type == "platform"){
                if (!sprite.mirrored()){
                    level.addWaveAnimation(b.ID, (x - b.get_x())/2);
                }
                else{
                   level.addWaveAnimation(b.ID, (x + cBox.getWidth() - b.get_x())/2);
                }

            }

        }

        if (cBox.hitLeftOf(b)){
            xVelocity = 0;
            cBox.solidInteraction(b,0);
        }
        if (cBox.hitRightOf(b)){
            xVelocity = 0;
            cBox.solidInteraction(b,180);
        }

        if (cBox.jumpedOn(b)){
            falling = false;
            sprite.setCurrentFrame(0);
            yVelocity = 0;
            cBox.solidInteraction(b,-90);
            groundStart = b.get_x();
            groundEnd = b.get_x()+b.getWidth();
        }


    }
    x = cBox.get_x();
    y = cBox.get_y();
}

/*
 * description: updates variables related to location
 * return: void
 * precondition: class instance exists and header files linked
 * postcondition: nothing is returned and variables are changed
 *
*/
void Plumber::updateLocation(){

    if (dead && y > 400){
        dead = false;
        newLife.playSound(); //play new life sound
        x = 395;
        y = 150;
        cBox.resetAtLocation(x, y);
        falling = true;
        xVelocity = 0.0;
        yVelocity = 0.0;
        yAccel = 0.05;

        groundStart = 0;
        groundEnd= 800;

        sprite.setCurrentFrame(0);

        invincible = true;

    }

    if (falling && yVelocity < 5){
            yVelocity += yAccel;
        }

        if (((cBox.get_x() + cBox.getWidth() < groundStart) ||
            (cBox.get_x() > groundEnd)) && !falling){

            falling = true;

            sprite.setCurrentFrame(5);

            groundStart = 0;
            groundEnd = 800;
        }

        x += xVelocity;
        y += yVelocity;

        if (x < 0){
            x = 800 + x;
            y -= 4;
            falling = true;
        }
        if (x > 800){
            x = x - 800;
            y -= 4;
            falling = true;
        }
        cBox.moveToLocation(x, y);
}

/*
 * description: determines sprite settings based on user input
 * return: void
 * precondition: class instance exists and header files linked, and char passed in
 * postcondition: nothing is returned
 *
*/
void Plumber::onKeyPress(char key_pressed){

    if (dead){
        return;
    }

    if (key_pressed != 'D' && key_pressed != 'A'){
        if (!falling){
            sprite.setCurrentFrame(0);
        }
        xVelocity = 0;
    }

    int counter = 0; //counter variable

    while((key_pressed == 'D' || key_pressed == 'A') && !falling && counter < 9000) {
        counter++; //created to delay the walking sound effect
    }

    if((key_pressed == 'D' || key_pressed == 'A') && !falling) {
        walking.playSound(); //play walking when A or D pressed and not in air
    }

    // Side to Side Movement
    if (key_pressed == 'D'){

        xVelocity = 2;

        if(!sprite.mirrored()){
            sprite.setMirrored(true);
        }
        if (a >=1 && !falling){
            sprite.setCurrentFrame(sprite.getCurrentFrame()+1);
            if (sprite.getCurrentFrame() == 4){
                sprite.setCurrentFrame(1);
            }
            a = 0;

        }
    }

    if (key_pressed == 'A'){

        xVelocity = -2;;

        if (sprite.mirrored()){
            sprite.setMirrored(false);
        }

        if (a >= 1 && !falling){
            sprite.setCurrentFrame(sprite.getCurrentFrame()+1);
            if (sprite.getCurrentFrame() == 4){
                sprite.setCurrentFrame(1);
            }
            a = 0;
        }
    }


    if (key_pressed == 'W'&& !falling){
        jump.playSound();
        sprite.setCurrentFrame(5);
        yVelocity = -3.5;
        falling = true;
    }
}

/*
 * description: sets the variable dead
 * return: void
 * precondition: class instance exists and header files linked, accepts a bool
 * postcondition: nothing is returned
 *
*/
void Plumber::setDead(bool value){

    dead = value;

}

/*
 * description: gets the variable dead
 * return: bool
 * precondition: class instance exists and header files linked
 * postcondition: bool is returned, nothing is changed
 *
*/
bool Plumber::getDead(){

    return dead;

}

/*
 * description: sets the variable invincible
 * return: void
 * precondition: class instance exists and header files linked, bool passed in
 * postcondition: invincible variable is set
 *
*/
void Plumber::setInvincible(bool value){
    invincible = value;
}


/*
 * description: gets the variable invincible
 * return: bool
 * precondition: class instance exists and header files linked
 * postcondition: nothing is changed and a bool is returned
 *
*/
bool Plumber::getInvincible(){
    return invincible;
}
