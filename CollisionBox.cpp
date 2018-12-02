#include "CollisionBox.h"
#include <cmath>
using namespace std;

const double PI = 3.14159;

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

 int CollisionBox::getWidth(){
     return width;
 }
 int CollisionBox::getHeight(){
     return height;
 }
 double CollisionBox::get_x(){
     return x;
 }
 double CollisionBox::get_y(){
     return y;
 }
 double CollisionBox::get_past_x(){
     return past_x;
 }
 double CollisionBox::get_past_y(){
     return past_y;
 }

 void CollisionBox::setWidth(int width){
     this->width = width;
 }
 void CollisionBox::setHeight(int height){
     this->height = height;
 }
 void CollisionBox::moveToLocation(double x, double y){
     past_x = this->x;
     past_y = this->y;

     this->x = x;
     this->y = y;
 }

 void CollisionBox::resetAtLocation(double x, double y){
     past_x = x;
     past_y = y;
     this->x = x;
     this->y = y;
 }

 bool CollisionBox::isTouching(CollisionBox& b){

     if ((x < b.get_x() + b.getWidth()-1 && y < b.get_y() + b.getHeight()-1)
         && (x + width-1 > b.get_x() && y + height-1 > b.get_y())){
        //cout<<"Touching"<<endl;
         return true;

         }

     return false;
 }

 bool CollisionBox::jumpedOn(CollisionBox& b){

     if (isTouching(b) && (past_y + height-1 < b.get_y())){
         return true;
     }
     return false;

  //  for (int y = past_y; y <= )

}
bool CollisionBox::hitHeadUnder(CollisionBox& b){

//    cout << past_y << endl;
//    cout << isTouching(b) << endl;
//    cout << b.y << endl;

    if (isTouching(b) && (past_y > b.get_y() + b.getHeight()-1)){
        cout<<"HitHeadUnder"<<endl;
        return true;
    }
    return false;
}
bool CollisionBox::hitTheSideOf(CollisionBox& b){
     return hitLeftOf(b) || hitRightOf(b);
}

bool CollisionBox::hitLeftOf(CollisionBox& b){

    if (isTouching(b)){
        if (past_x + width-1 < b.get_x()){
            return true;
        }
    }
    return false;

}

bool CollisionBox::hitRightOf(CollisionBox& b){

    if (isTouching(b)){
        if (past_x > b.get_x() + b.getWidth()-1){
            return true;
        }
    }
    return false;

}

void CollisionBox::setSolid(bool solid){

    this->solid = solid;

}

bool CollisionBox::getSolid(){
    return solid;
}

void CollisionBox::setDirection(int d){

    direction = d;

}

int CollisionBox::getDirection(){

    return direction;

}

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

void CollisionBox::fitToSprite(Sprite& sprite){

    int cf = sprite.getCurrentFrame();
    setWidth(sprite.getScaledWidth(cf));
    setHeight(sprite.getScaledHeight(cf));
    resetAtLocation(sprite.get_x(), sprite.get_y());

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

void createCollisionEvents(vector<CollisionEvent>& events,
                           vector<CollisionBox>& boxes){

    events.clear();

    for (int i = 0; i < boxes.size(); i++){


        for (int j = 0; j < boxes.size(); j++){

            if (i == j){
                continue;
            }

            CollisionEvent event(boxes[i],boxes[j]);

            if (event.collisionType != none){
                events.push_back(event);
            }

        }

    }
}

//void solidInteraction(CollisionEvent& event){
//
//    CollisionBox& c = event.collider;
//    CollisionBox& box = event.collidee;
//
//    switch(event.collisionType){
//
//    case jumpedOn:
//        while(c.isTouching(box)){
//            c.moveToLocation(c.get_x(),c.get_y()-1);
//        }
//        return;
//
//    case hitHeadUnder:
//        while(c.isTouching(box)){
//            c.moveToLocation(c.get_x(),c.get_y()+1);
//        }
//        return;
//
//    case hitLeftOf:
//        while(c.hitLeftOf(box)){
//            c.moveToLocation(c.get_x()-1,c.get_y());
//        }
//        return;
//
//    case hitRightOf:
//        while(c.hitRightOf(box)){
//            c.moveToLocation(c.get_x()+1,c.get_y());
//        }
//        return;
//    }
//
//}
