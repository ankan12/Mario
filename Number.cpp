#include "Number.h"

using namespace std;

Number::Number(char filename[], ifstream& inFile){
    number = 0;
    x = 0;
    y = 0;
    scale = 1;

    sprite.loadImage(filename, inFile);

}

void Number::setNumber(int number){
    number = 0;
    x = 0;
    y = 0;
    scale = 1;

    this->number = number;

    if (number == 0){
        digits.resize(1, 0);
        return;
    }

    digits.resize(0);

    int temp = number;

    while(temp != 0){

        int digit = temp % 10;

        digits.insert(digits.begin(), digit);

        temp /= 10;

    }

}

int Number::getNumber(){

    return number;

}

void Number::setLocation(int x, int y){

    this->x = x;
    this->y = y;

}

void Number::draw(SDL_Plotter& p){

    sprite.setLocation(x,y);

    for (int d = 0; d < digits.size(); d++){

        sprite.setCurrentFrame(digits[d]);

        sprite.draw(p);

        int cf = sprite.getCurrentFrame();

        sprite.set_x(sprite.get_x() + sprite.getScaledWidth(cf));

    }

}

Sprite& Number::getSprite(){

    return sprite;

}

void Number::setScale(int scale){

    sprite.setScale(scale);

}

int Number::getScale(){

    return scale;

}
