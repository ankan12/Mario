#include "CollisionBox.h"

using namespace std;

CollisionBox::CollisionBox(){
}

CollisionBox::CollisionBox(int width, int height, int x, int y){

    setWidth(width);
    setHeight(height);
    resetAtLocation(x, y);

}

int CollisionBox::getWidth(){
    return width;
}
int CollisionBox::getHeight(){
    return height;
}
int CollisionBox::get_x(){
    return x;
}
int CollisionBox::get_y(){
    return y;
}
int CollisionBox::get_past_x(){
    return past_x;
}
int CollisionBox::get_past_y(){
    return past_y;
}

void CollisionBox::setWidth(int width){
    this->width = width;
}
void CollisionBox::setHeight(int height){
    this->height = height;
}
void CollisionBox::moveToLocation(int x, int y){
    past_x = this->x;
    past_y = this->y;

    this->x = xWrap(x);
    this->y = yWrap(y);
}

void CollisionBox::resetAtLocation(int x, int y){
    past_x = xWrap(x);
    past_y = yWrap(y);
    this->x = xWrap(x);
    this->y = yWrap(y);
}

bool CollisionBox::isTouching(const CollisionBox& b){

    if ((xWrap(x) < xWrap(b.x+b.width-1) && yWrap(y) < yWrap(b.y+b.height-1))
        && (xWrap(x+width-1) > xWrap(b.x) && yWrap(y+height-1) > yWrap(b.y))){

        return true;

        }

    return false;
}

bool CollisionBox::jumpedOn(const CollisionBox& b){

    if (isTouching(b) && (yWrap(past_y + height-1) < yWrap(b.y))){
        return true;
    }
    return false;
}
bool CollisionBox::hitHeadUnder(const CollisionBox& b){

    if (isTouching(b) && (yWrap(past_y) > yWrap(b.y + b.height-1))){
        return true;
    }
    return false;
}
bool CollisionBox::hitTheSideOf(const CollisionBox& b){

    if (isTouching(b)){
        if (xWrap(past_x + width-1) < xWrap(b.x)){
            return true;
        }
        if (xWrap(past_x) > xWrap(b.x + b.width-1)){
            return true;
        }
    }
    return false;
}

void CollisionBox::drawBox(SDL_Plotter& p){

    for (int c = x; c < x + width; c++){
        p.plotPixel(xWrap(c), yWrap(y), 255, 0, 0);
        p.plotPixel(xWrap(c), yWrap(y + height-1), 255, 0, 0);
    }
    for (int c = y; c < y + height; c++){
        p.plotPixel(xWrap(x), yWrap(c), 255, 0, 0);
        p.plotPixel(xWrap(x + width-1), yWrap(c), 255, 0, 0);
    }
}

void CollisionBox::setHorizontalWrap(int screenWidth){

    horizontalWrap = screenWidth;

}

void CollisionBox::setVerticalWrap(int screenHeight){

    verticalWrap = screenHeight;

}

int CollisionBox::xWrap(int xValue){

    if (horizontalWrap <= 0){
        return xValue;
    }

    return xValue % horizontalWrap;

}

int CollisionBox::yWrap(int yValue){

    if (verticalWrap <= 0){
        return yValue;
    }

    return yValue & verticalWrap;

}
