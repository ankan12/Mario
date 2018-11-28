#ifndef SHELLCREEPER_H_INCLUDED
#define SHELLCREEPER_H_INCLUDED

#include <fstream>
#include "Sprite.h"
#include "SDL_Plotter.h"
#include "CollisionBox.h"
#include <vector>
#include "Level.h"

using namespace std;

static bool enemyExitedPipe = false;

static vector<bool> queueUpdated;

static int totalEnemiesInPipe = 0;

class Shellcreeper{

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

    bool spawning;

    double spawnX, spawnY;
    double exitX, exitY;

    int pipe;
    int pipeQueue;

    CollisionBox cBox;
    CollisionBox hitBox;

    void spawn();

    bool turningAround;
    bool bumped;
    bool dead;

public:
    Shellcreeper(char[], ifstream&, int scale, int pipe);

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
    CollisionBox& getHitBox();

    void solidCollisions(vector<CollisionBox>& solids, Level& level);

    void updateLocation();

    void turnAround();

    void setExit(double x, double y);

    bool getBumped();
    void setBumped(bool);

    bool getDead();
    void setDead(bool);

};

#endif // SHELLCREEPER_H_INCLUDED
