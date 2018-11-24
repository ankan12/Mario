#ifndef COLLISIONBOX_H_INCLUDED
#define COLLISIONBOX_H_INCLUDED

#include "SDL_Plotter.h"

class CollisionBox{

private:
    int x, y;
    int width, height;
    int past_x, past_y;

public:
    CollisionBox(int width, int height, int x, int y);
    CollisionBox();

    int getWidth();
    int getHeight();
    int get_x();
    int get_y();
    int get_past_x();
    int get_past_y();

    void setWidth(int);
    void setHeight(int);
    void moveToLocation(int,int);
    void resetAtLocation(int,int);


    bool isTouching(const CollisionBox& b);
    bool jumpedOn(const CollisionBox& b);
    bool hitHeadUnder(const CollisionBox& b);
    bool hitTheSideOf(const CollisionBox& b);

    //For debugging purposes
    void drawBox(SDL_Plotter& p);
};

#endif // COLLISIONBOX_H_INCLUDED
