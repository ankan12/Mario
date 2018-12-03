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
#ifndef SHELLCREEPER_H_INCLUDED
#define SHELLCREEPER_H_INCLUDED

#include <fstream>
#include "Sprite.h"
#include "SDL_Plotter.h"
#include "CollisionBox.h"
#include <vector>
#include "Level.h"
#include "EnemyState.h"
#include "Pipe.h"

using namespace std;

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

    CollisionBox cBox;
    CollisionBox hurtBox;

    Pipe pipe0, pipe1;
    Pipe pipeThatIAmIn;

    double pipeSpeed;

    string directionInsidePipe;

    EnemyState state;

    double distanceInPipe;

public:


/*
 * description: constructor for the shellcreeper class
 * return: NA
 * precondition: instance of shellcreeper exists
 * postcondition: all variables initialized to input
 *
*/

    Shellcreeper(char[], ifstream&, int scale, int pipe, Pipe& pipe0, Pipe& pipe1);

/*
 * description: returns x
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    double getX();

/*
 * description: returns y
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    double getY();

/*
 * description: returns x velocity
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    double getXVel();

/*
 * description: returns y velocity
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    double getYVel();

/*
 * description: returns y acceleration
 * return: double
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    double getYAccel();


/*
 * description: sets x
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: x is set
 *
*/
    void setX(double);

/*
 * description: sets y
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: y is set
 *
*/
    void setY(double);

/*
 * description: sets x velocity
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: x velocity is set
 *
*/
    void setXVel(double);

/*
 * description: sets y velocity
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: y velocity is set
 *
*/
    void setYVel(double);

/*
 * description: sets y acceleration
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: y velocity is set
 *
*/
    void setYAccel(double);


/*
 * description: sets boolean Falling
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: falling boolean is set
 *
*/
    void setFalling(bool);

/*
 * description: returns falling boolean
 * return: bool
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    bool isFalling();

/*
 * description: gets sprite by reference
 * return: sprite
 * precondition: instance of shellcreeper exists
 * postcondition: sprite is returned
 *
*/
    Sprite& getSprite();


 /*
 * description: draws to the screen
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    void draw(SDL_Plotter& p);





/*
 * description: gets collision box and passes by reference
 * return: Collision box
 * precondition: instance of shellcreeper exists
 * postcondition: CBox is passed by reference
 *
*/
    CollisionBox& getCBox();

    CollisionBox& getHurtBox();
/*
 * description: determins sprite action based on collision
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: sprite variables are set to as needed
 *
*/
    void solidCollisions(vector<CollisionBox>& solids);


/*
 * description: gets collision box and passes by reference
 * return: Collision box
 * precondition: instance of shellcreeper exists
 * postcondition: HitBox is passed by reference
 *
*/
    CollisionBox& getHitBox();


/*
 * description: sets state of class
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: variables are set
 *
*/
    void setState(EnemyState state);

/*
 * description: returns enemy state
 * return: EnemyState
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    EnemyState getState();

/*
 * description: this function updates the location variables
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: variables are set
 *
*/
    void updateLocation();


/*
 * description: prints the state of the class
 * return: void
 * precondition: instance of shellcreeper exists
 * postcondition: nothing is changed
 *
*/
    void printState();

};

#endif // SHELLCREEPER_H_INCLUDED
