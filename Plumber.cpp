#include "Plumber.h"


using namespace std;

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

    fist.setWidth(5);
    fist.setHeight(2);

    onIce = false;

}

double Plumber::getX(){
    return x;
}
double Plumber::getY(){
    return y;
}
double Plumber::getXVel(){
    return xVelocity;
}
double Plumber::getYVel(){
    return yVelocity;
}
double Plumber::getYAccel(){
    return yAccel;
}

void Plumber::setX(double x){
    this->x = x;
}
void Plumber::setY(double y){
    this->y = y;
}
void Plumber::setXVel(double xVelocity){
    this->xVelocity = xVelocity;
}
void Plumber::setYVel(double yVelocity){
    this->yVelocity = yVelocity;
}
void Plumber::setYAccel(double yAccel){
    this->yAccel = yAccel;
}

void Plumber::setFalling(bool falling){
    this->falling = falling;
}
bool Plumber::isFalling(){
    return falling;
}

Sprite& Plumber::getSprite(){
    return sprite;
}

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

CollisionBox& Plumber::getCBox(){
    return cBox;
}

void Plumber::solidCollisions(vector<CollisionBox>& solids, Level& level){

    if (dead){
        return;
    }

    for (int i = 0; i < solids.size(); i++){

        CollisionBox& b = solids[i];

        if (cBox.hitHeadUnder(b)){
            cout << "hit" << endl;
            yVelocity = 0;
            cBox.solidInteraction(b,90);
            if (b.type == "platform"){
                cout << "Platform" << endl;
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
            cout << "Landed" << endl;
            falling = false;
            sprite.setCurrentFrame(0);
            yVelocity = 0;
            cBox.solidInteraction(b,-90);
            groundStart = b.get_x();
            groundEnd = b.get_x()+b.getWidth();

            if (b.type == "platform"){
                if (level.getPlatform(b.ID).isFrozen()){
                    onIce = true;
                }
            }

        }


    }
    x = cBox.get_x();
    y = cBox.get_y();
}

void Plumber::updateLocation(){

    if (dead && y > 400){
        dead = false;
        placeCharacterInCenter();
        invincible = true;

    }

    if (falling && yVelocity < 5){
            yVelocity += yAccel;
        }

        if (((cBox.get_x() + cBox.getWidth() < groundStart) ||
            (cBox.get_x() > groundEnd)) && !falling){

            falling = true;
            onIce = false;

            sprite.setCurrentFrame(5);

            groundStart = 0;
            groundEnd = 800;
        }

        x += xVelocity;
        y += yVelocity;

        if (x < 0){
            cout << x << endl;
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

        if (sprite.mirrored()){
            fist.moveToLocation(cBox.get_x() + cBox.getWidth() - fist.getWidth() , cBox.get_y());
        }
        else{
            fist.moveToLocation(cBox.get_x(), cBox.get_y());
        }
}

void Plumber::onKeyPress(char key_pressed){

    if (dead){
        return;
    }

    if (key_pressed != 'D' && key_pressed != 'A'){
        if (!falling){
            sprite.setCurrentFrame(0);
        }
        if (!onIce){
            xVelocity = 0;
        }
    }

    // Side to Side Movement
    if (key_pressed == 'D'){

        if (onIce){
            xVelocity += 0.01;
        }
        else{
            xVelocity = 2;
        }

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

        if (onIce){
            xVelocity -= 0.01;
        }
        else{
            xVelocity = -2;
        }

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
        sprite.setCurrentFrame(5);
        yVelocity = -3.5;
        falling = true;
        onIce = false;
    }
}

void Plumber::setDead(bool value){

    dead = value;

}

bool Plumber::getDead(){

    return dead;

}

void Plumber::setInvincible(bool value){
    invincible = value;
}

bool Plumber::getInvincible(){
    return invincible;
}

void Plumber::placeCharacterInCenter(){

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
}

CollisionBox& Plumber::getFist(){
    return fist;
}
