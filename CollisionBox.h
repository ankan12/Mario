#ifndef COLLISIONBOX_H_INCLUDED
#define COLLISIONBOX_H_INCLUDED

#include "SDL_Plotter.h"
#include <vector>
#include "Sprite.h"

using namespace std;

class CollisionBox{
 private:
    double x, y;
    int width, height;
    double past_x, past_y;
    bool solid;
    double direction;

 public:

/*
 * description: constructor for CollisionBox
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
     CollisionBox(int width, int height, double x, double y);

/*
 * description: default constructor for Block
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set
 *
*/
     CollisionBox();

     string type;
     int ID;

/*
 * description: gets the value of width
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     int getWidth();

/*
 * description: gets the value of height
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     int getHeight();

/*
 * description: gets the value of x
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     double get_x();

/*
 * description: gets the value of y
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     double get_y();

/*
 * description: gets the value of past x
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     double get_past_x();

/*
 * description: gets the value of past y
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     double get_past_y();


/*
 * description: sets the value of width
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: width is changed
 *
*/
     void setWidth(int);

/*
 * description: sets the value of height
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: Height is changed
 *
*/
     void setHeight(int);

/*
 * description: sets the location to move to
 * return: void
 * precondition: class instance exists and two doubles are passed in
 * postcondition: changes x and y
 *
*/
     void moveToLocation(double,double);

/*
 * description: sets the location to reset to
 * return: void
 * precondition: class instance exists and two doubles are passed in
 * postcondition: changes x and y
 *
*/
     void resetAtLocation(double,double);

/*
 * description: determines if its touching a collision box
 * return: bool
 * precondition: class instance exists and a collision box is passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
     bool isTouching(CollisionBox& b);

/*
 * description: determines if there was a hit on top of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
     bool jumpedOn(CollisionBox& b);

/*
 * description: determines if there was a hit on under of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
     bool hitHeadUnder(CollisionBox& b);

/*
 * description: determines if there was a hit on the side of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
     bool hitTheSideOf(CollisionBox& b);

/*
 * description: determines if there was a hit on the left of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
     bool hitLeftOf(CollisionBox& b);

/*
 * description: determines if there was a hit on the right of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
     bool hitRightOf(CollisionBox& b);

/*
 * description: sets the variable solid
 * return: void
 * precondition: class instance exists and bool is passed in
 * postcondition: solid is set
 *
*/
     void setSolid(bool);

/*
 * description: gets the variable solid
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     bool getSolid();

/*
 * description: sets the variable direction
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: direction is set
 *
*/
     void setDirection(int);

/*
 * description: gets the variable direction
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
     int getDirection();

/*
 * description: determines if two solids are touching
 * return: bool
 * precondition: class instance exists and collision box and double are passed in
 * postcondition: resets location and sets a boolean to true
 *
*/
     bool solidInteraction(CollisionBox& b, double);

/*
 * description: scales box to sprite
 * return: void
 * precondition: class instance exists and sprite is passed in
 * postcondition: resets size of collision box
 *
*/
     void fitToSprite(Sprite& sprite);

/*
 * description: draws the box (for debugging purposes)
 * return: void
 * precondition: class instance exists and plotter is passed in
 * postcondition: draws box to screen
 *
*/
     void drawBox(SDL_Plotter& p);

/*
 * description: draws the past box (for debugging purposes)
 * return: void
 * precondition: class instance exists and plotter is passed in
 * postcondition: draws box to screen
 *
*/
     void drawPastBox(SDL_Plotter& p);
 };

 enum CollisionType {hitLeftOf, hitRightOf, jumpedOn, hitHeadUnder, none};

 struct CollisionEvent{

    CollisionType collisionType;

    CollisionBox collider;

    CollisionBox collidee;

    CollisionEvent(CollisionBox&, CollisionBox&);

 };


void removeCollisionBox(vector<CollisionBox>& cBoxes, string type);


#endif // COLLISIONBOX_H_INCLUDED
