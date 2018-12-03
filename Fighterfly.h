#ifndef FIGHTERFLY_H_INCLUDED
#define FIGHTERFLY_H_INCLUDED

#include <fstream>
#include "Sprite.h"
#include "SDL_Plotter.h"
#include "CollisionBox.h"
#include <vector>
#include "Level.h"
#include "EnemyState.h"
#include "Pipe.h"

using namespace std;

class Fighterfly{

private:
    double x, y;
    Sprite sprite;
    bool falling;
    int groundStart, groundEnd;
    double xVelocity, yVelocity;
    double yAccel;

    double animationSpeed;
    double a;

    double speedFactor;

    CollisionBox cBox;
    CollisionBox hurtBox;

    Pipe pipe0, pipe1;
    Pipe pipeThatIAmIn;

    double pipeSpeed;

    string directionInsidePipe;

    EnemyState state;

    double distanceInPipe;

    double startingSpeed;

public:

    Fighterfly(char[], ifstream&, int scale, int pipe, Pipe& pipe0, Pipe& pipe1);

    double getX();
    double getY();
    double getXVel();
    double getYVel();
    double getYAccel();

    void setX(double);
    void setY(double);
    void setXVel(double);
    void setYVel(double);
    void setYAccel(double);

    void setFalling(bool);
    bool isFalling();

    Sprite& getSprite();

    void draw(SDL_Plotter& p);

    CollisionBox& getCBox();
    CollisionBox& getHurtBox();

    void solidCollisions(vector<CollisionBox>& solids, Level& level);
    void solidCollisions(vector<CollisionBox>& solids);

    void updateLocation();

    void turnAround();

    void setExit(double x, double y);

    bool getBumped();
    void setBumped(bool);

    bool getDead();
    void setDead(bool);

    void setState(EnemyState state);
    EnemyState getState();

    void printState();

    int getSpeedFactor();
    void setSpeedFactor(int);

    int getAngerCounter();

};

#endif // FIGHTERFLY_H_INCLUDED
