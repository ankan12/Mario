#ifndef COLLISIONBOX_H_INCLUDED
#define COLLISIONBOX_H_INCLUDED

#include "SDL_Plotter.h"

class CollisionBox{

private:
    int x = 0, y = 0;
    int width, height;
    int past_x = 0, past_y = 0;

    int horizontalWrap = -1;
    int verticalWrap = -1;

    int xWrap(int);
    int yWrap(int);

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

    void setHorizontalWrap(int screenWidth);
    void setVerticalWrap(int screenHeight);

    bool isTouching(const CollisionBox& b);
    bool jumpedOn(const CollisionBox& b);
    bool hitHeadUnder(const CollisionBox& b);
    bool hitTheSideOf(const CollisionBox& b);
    bool hitTheLeftOf(const CollisionBox& b);
    bool hitTheRightOf(const CollisionBox& b);

    //For debugging purposes
    void drawBox(SDL_Plotter& p);
};

#endif // COLLISIONBOX_H_INCLUDED
