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
     CollisionBox(int width, int height, double x, double y);
     CollisionBox();

     string type;
     int ID;

     int getWidth();
     int getHeight();
     double get_x();
     double get_y();
     double get_past_x();
     double get_past_y();

     void setWidth(int);
     void setHeight(int);
     void moveToLocation(double,double);
     void resetAtLocation(double,double);


     bool isTouching(CollisionBox& b);
     bool jumpedOn(CollisionBox& b);
     bool hitHeadUnder(CollisionBox& b);
     bool hitTheSideOf(CollisionBox& b);

     bool hitLeftOf(CollisionBox& b);
     bool hitRightOf(CollisionBox& b);

     void setSolid(bool);
     bool getSolid();

     void setDirection(int);
     int getDirection();

     bool solidInteraction(CollisionBox& b, double);

     void fitToSprite(Sprite& sprite);

     //For debugging purposes
     void drawBox(SDL_Plotter& p);
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
