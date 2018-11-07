#ifndef COLLISIONBOX_H_INCLUDED
#define COLLISIONBOX_H_INCLUDED

#include "SDL_Plotter.h"

class CollisionBox{

private:
    int x = 0, y = 0;
    int width, height;
    int past_x = 0, past_y = 0;

public:
    CollisionBox(int width, int height, int x, int y);

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


    bool isTouching(CollisionBox b);
    bool jumpedOn(CollisionBox b);
    bool hitHeadOn(CollisionBox b);
    bool hitTheSideOf(CollisionBox b);

    //For debugging purposes
    void drawBox(SDL_Plotter& p);
};

#endif // COLLISIONBOX_H_INCLUDED
