#ifndef PLUMBER_H_INCLUDED
#define PLUMBER_H_INCLUDED

#include <fstream>
#include "Sprite.h"
#include "SDL_Plotter.h"
#include "CollisionBox.h"
#include <vector>
#include "Level.h"
using namespace std;

class Plumber{
private:
    double x, y;
    Sprite sprite;
    bool falling;
    int groundStart, groundEnd;
    double xVelocity, yVelocity;
    double yAccel;

    double animationSpeed;
    double a;

    bool dead;

    bool invincible;

    int invincibleTimer;

    CollisionBox cBox;

public:
    Plumber(char[], ifstream&, int scale, int x, int y);

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

    void solidCollisions(vector<CollisionBox>& solids, Level& level);

    void updateLocation();

    void onKeyPress(char keyPress);

    void setDead(bool);
    bool getDead();

    void setInvincible(bool);
    bool getInvincible();

};

#endif // PLUMBER_H_INCLUDED
