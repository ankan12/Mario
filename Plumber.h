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

    CollisionBox fist;

    bool onIce;

public:

/*
 * description: constructor for Plumber
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
    Plumber(char[], ifstream&, int scale, int x, int y);

/*
 * description: gets the x value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    double getX();

/*
 * description: gets the y value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    double getY();

/*
 * description: gets the x velocity value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    double getXVel();

/*
 * description: gets the y velocity value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    double getYVel();

/*
 * description: gets the y acceleration value
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    double getYAccel();

/*
 * description: sets the x value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: x value is set
 *
*/
    void setX(double);

/*
 * description: sets the y value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: y value is set
 *
*/
    void setY(double);

/*
 * description: sets the x velocity value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: x velocity value is set
 *
*/
    void setXVel(double);

/*
 * description: sets the y velocity value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: y velocity value is set
 *
*/
    void setYVel(double);

/*
 * description: sets the y acceleration value
 * return: void
 * precondition: class instance exists and double passed in
 * postcondition: y acceleration value is set
 *
*/
    void setYAccel(double);


/*
 * description: assigns boolean value to falling
 * return: void
 * precondition: class instance exists and bool passed in
 * postcondition: falling variable is set to true or false
 *
*/
    void setFalling(bool);

/*
 * description: returns the value of falling
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    bool isFalling();

/*
 * description: passes sprite by reference
 * return: Sprite
 * precondition: class instance exists and sprite linked
 * postcondition: sprite passed by reference
 *
*/
    Sprite& getSprite();

/*
 * description: uses SDL to draw to screen
 * return: void
 * precondition: class instance exists and plotter passed in
 * postcondition: information is printed to the screen
 *
*/
    void draw(SDL_Plotter& p);

/*
 * description: gets a collision box
 * return: CollisionBox
 * precondition: class instance exists and collisionbox file is linked
 * postcondition: Collision box is passed by reference
 *
*/
    CollisionBox& getCBox();

/*
 * description: uses collision boxes to determine movement and animation
 * return: void
 * precondition: class instance exists and header files linked
 * postcondition: nothing is returned
 *
*/
    void solidCollisions(vector<CollisionBox>& solids, Level& level);


/*
 * description: updates variables related to location
 * return: void
 * precondition: class instance exists and header files linked
 * postcondition: nothing is returned and variables are changed
 *
*/
    void updateLocation();

/*
 * description: determines sprite settings based on user input
 * return: void
 * precondition: class instance exists and header files linked, and char passed in
 * postcondition: nothing is returned
 *
*/
    void onKeyPress(char keyPress);

/*
 * description: sets the variable dead
 * return: void
 * precondition: class instance exists and header files linked, accepts a bool
 * postcondition: nothing is returned
 *
*/
    void setDead(bool);

/*
 * description: gets the variable dead
 * return: bool
 * precondition: class instance exists and header files linked
 * postcondition: bool is returned, nothing is changed
 *
*/
    bool getDead();

/*
 * description: sets the variable invincible
 * return: void
 * precondition: class instance exists and header files linked, bool passed in
 * postcondition: invincible variable is set
 *
*/
    void setInvincible(bool);

/*
 * description: gets the variable invincible
 * return: bool
 * precondition: class instance exists and header files linked
 * postcondition: nothing is changed and a bool is returned
 *
*/
    bool getInvincible();

    void placeCharacterInCenter();

    CollisionBox& getFist();

};

#endif // PLUMBER_H_INCLUDED
