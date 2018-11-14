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

    this->x = x;
    this->y = y;
}

void CollisionBox::resetAtLocation(int x, int y){
    past_x = x;
    past_y = y;
    this->x = x;
    this->y = y;
}

bool CollisionBox::isTouching(const CollisionBox& b){

    if ((x < b.x + b.width-1 && y < b.y + b.height-1)
        && (x + width-1 > b.x && y + height-1 > b.y)){

        return true;

        }

    return false;
}

bool CollisionBox::jumpedOn(const CollisionBox& b){

    if (isTouching(b) && (past_y + height-1 < b.y)){
        return true;
    }
    return false;
}
bool CollisionBox::hitHeadUnder(const CollisionBox& b){

    if (isTouching(b) && (past_y > b.y + b.height-1)){
        return true;
    }
    return false;
}
bool CollisionBox::hitTheSideOf(const CollisionBox& b){

    if (isTouching(b)){
        if (past_x + width-1 < b.x){
            return true;
        }
        if (past_x > b.x + b.width-1){
            return true;
        }
    }
    return false;
}

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
