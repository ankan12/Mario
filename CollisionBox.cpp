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
#include "CollisionBox.h"
#include <cmath>
using namespace std;

const double PI = 3.14159;


/*
 * description: constructor for CollisionBox
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set to input
 *
*/
CollisionBox::CollisionBox(){
    x = 0;
    y = 0;
    past_x = 0;
    past_y = 0;

    ID = 0;
    type = "";
    solid = true;

    direction = 0;

}

/*
 * description: default constructor for Block
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set
 *
*/
 CollisionBox::CollisionBox(int width, int height, double x, double y){
    past_x = 0;
    past_y = 0;
    setWidth(width);
    setHeight(height);
    resetAtLocation(x, y);

    ID = 0;
    type = "";
    solid = true;

    direction = 0;

 }

/*
 * description: gets the value of width
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
 int CollisionBox::getWidth(){
     return width;
 }

/*
 * description: gets the value of height
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
 int CollisionBox::getHeight(){
     return height;
 }

/*
 * description: gets the value of x
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
 double CollisionBox::get_x(){
     return x;
 }

/*
 * description: gets the value of y
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
 double CollisionBox::get_y(){
     return y;
 }

/*
 * description: gets the value of past x
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
 double CollisionBox::get_past_x(){
     return past_x;
 }

/*
 * description: gets the value of past y
 * return: double
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
 double CollisionBox::get_past_y(){
     return past_y;
 }

/*
 * description: sets the value of width
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: width is changed
 *
*/
 void CollisionBox::setWidth(int width){
     this->width = width;
 }

/*
 * description: sets the value of height
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: Height is changed
 *
*/
 void CollisionBox::setHeight(int height){
     this->height = height;
 }

/*
 * description: sets the location to move to
 * return: void
 * precondition: class instance exists and two doubles are passed in
 * postcondition: changes x and y
 *
*/
 void CollisionBox::moveToLocation(double x, double y){
     past_x = this->x;
     past_y = this->y;

     this->x = x;
     this->y = y;
 }

/*
 * description: sets the location to reset to
 * return: void
 * precondition: class instance exists and two doubles are passed in
 * postcondition: changes x and y
 *
*/
 void CollisionBox::resetAtLocation(double x, double y){
     past_x = x;
     past_y = y;
     this->x = x;
     this->y = y;
 }

/*
 * description: determines if its touching a collision box
 * return: bool
 * precondition: class instance exists and a collision box is passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
 bool CollisionBox::isTouching(CollisionBox& b){

     if ((x < b.get_x() + b.getWidth()-1 && y < b.get_y() + b.getHeight()-1)
         && (x + width-1 > b.get_x() && y + height-1 > b.get_y())){
         return true;

         }

     return false;
 }

/*
 * description: determines if there was a hit on top of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
 bool CollisionBox::jumpedOn(CollisionBox& b){

     if (isTouching(b) && (past_y + height-1 < b.get_y())){
         return true;
     }
     return false;


}

/*
 * description: determines if there was a hit on under of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
bool CollisionBox::hitHeadUnder(CollisionBox& b){

    if (isTouching(b) && (past_y > b.get_y() + b.getHeight()-1)){
        return true;
    }
    return false;
}

/*
 * description: determines if there was a hit on the side of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
bool CollisionBox::hitTheSideOf(CollisionBox& b){
     return hitLeftOf(b) || hitRightOf(b);
}

/*
 * description: determines if there was a hit on the left of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
bool CollisionBox::hitLeftOf(CollisionBox& b){

    if (isTouching(b)){
        if (past_x + width-1 < b.get_x()){
            return true;
        }
    }
    return false;

}

/*
 * description: determines if there was a hit on the right of a collision box
 * return: bool
 * precondition: class instance exists and collision box passed in
 * postcondition: nothing is changed except boolean switches to true or false
 *
*/
bool CollisionBox::hitRightOf(CollisionBox& b){

    if (isTouching(b)){
        if (past_x > b.get_x() + b.getWidth()-1){
            return true;
        }
    }
    return false;

}


/*
 * description: sets the variable solid
 * return: void
 * precondition: class instance exists and bool is passed in
 * postcondition: solid is set
 *
*/
void CollisionBox::setSolid(bool solid){

    this->solid = solid;

}

/*
 * description: gets the variable solid
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
bool CollisionBox::getSolid(){
    return solid;
}

/*
 * description: sets the variable direction
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: direction is set
 *
*/
void CollisionBox::setDirection(int d){

    direction = d;

}

/*
 * description: gets the variable direction
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int CollisionBox::getDirection(){

    return direction;

}

/*
 * description: determines if two solids are touching
 * return: bool
 * precondition: class instance exists and collision box and double are passed in
 * postcondition: resets location and sets a boolean to true
 *
*/
bool CollisionBox::solidInteraction(CollisionBox& b, double direction){

    if (!isTouching(b)){
        return false;
    }

    while (isTouching(b)){

        x += cos((direction + 180.0) * (PI / 180.0));
        y -= sin((direction + 180.0) * (PI / 180.0));

    }
    resetAtLocation(x, y);
    return true;

}

/*
 * description: scales box to sprite
 * return: void
 * precondition: class instance exists and sprite is passed in
 * postcondition: resets size of collision box
 *
*/
void CollisionBox::fitToSprite(Sprite& sprite){

    int cf = sprite.getCurrentFrame();
    setWidth(sprite.getScaledWidth(cf));
    setHeight(sprite.getScaledHeight(cf));
    resetAtLocation(sprite.get_x(), sprite.get_y());

}

/*
 * description: draws the box (for debugging purposes)
 * return: void
 * precondition: class instance exists and plotter is passed in
 * postcondition: draws box to screen
 *
*/
 void CollisionBox::drawBox(SDL_Plotter& p){

     for (int c = x; c < x + width; c++){
         p.plotPixel(c, y, 255, 0, 0);
         p.plotPixel(c, y + height-1, 255, 0, 0);
     }
     for (int c = y; c < y + height; c++){
         p.plotPixel(x, c, 255, 0, 0);
         p.plotPixel(x + width-1, c, 255, 0, 0);
     }
 }

/*
 * description: draws the past box (for debugging purposes)
 * return: void
 * precondition: class instance exists and plotter is passed in
 * postcondition: draws box to screen
 *
*/
 void CollisionBox::drawPastBox(SDL_Plotter& p){
    for (int c = past_x; c < past_x + width; c++){
         p.plotPixel(c, past_y, 0, 0, 255);
         p.plotPixel(c, past_y + height-1, 0, 0, 255);
     }
     for (int c = past_y; c < past_y + height; c++){
         p.plotPixel(past_x, c, 0, 0, 255);
         p.plotPixel(past_x + width-1, c, 0, 0, 255);
     }

 }

CollisionEvent::CollisionEvent(CollisionBox& collider, CollisionBox& collidee){

    this->collider = collider;
    this->collidee = collidee;

    if (collider.jumpedOn(collidee)){
        collisionType = jumpedOn;
        return;
    }
    if (collider.hitHeadUnder(collidee)){
        collisionType = hitHeadUnder;
        return;
    }
    if (collider.hitLeftOf(collidee)){
        collisionType = hitLeftOf;
        return;
    }
    if (collider.hitRightOf(collidee)){
        collisionType = hitRightOf;
        return;
    }
    collisionType = none;

}

void removeCollisionBox(vector<CollisionBox>& cBoxes, string type){
    for (int i = 0; i < cBoxes.size(); i++){
        if (cBoxes[i].type == type){
            cBoxes.erase(cBoxes.begin() + i);
        }
    }
}
