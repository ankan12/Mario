#include "Number.h"

using namespace std;

/*
 * description: constructor for Number
 * return: NA
 * precondition: instance of Number
 * postcondition: variables are set to input
 *
*/
Number::Number(char filename[], ifstream& inFile){
    number = 0;
    x = 0;
    y = 0;
    scale = 1;

    sprite.loadImage(filename, inFile);

}

/*
 * description: sets and scales number
 * return: void
 * precondition: instance of Number and int is passed in
 * postcondition: number is resized and set
 *
*/
void Number::setNumber(int number){

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

/*
 * description: returns number
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Number::getNumber(){

    return number;

}

/*
 * description: sets location to output number
 * return: void
 * precondition: class instance exists and two ints are passed
 * postcondition: x and y are set for location
 *
*/
void Number::setLocation(int x, int y){

    this->x = x;
    this->y = y;

}

/*
 * description: uses SDL to draw to the screen
 * return: void
 * precondition: class instance exists and plotter is passed in
 * postcondition: nothing is changed, input drawn to screen
 *
*/
void Number::draw(SDL_Plotter& p){

    sprite.setLocation(x,y);

    for (int d = 0; d < digits.size(); d++){

        sprite.setCurrentFrame(digits[d]);

        sprite.draw(p);

        int cf = sprite.getCurrentFrame();

        sprite.set_x(sprite.get_x() + sprite.getScaledWidth(cf));

    }

}

/*
 * description: gets sprite and passes it by reference
 * return: Sprite
 * precondition: class instance exists
 * postcondition: sprite is gotten and passed by reference
 *
*/
Sprite& Number::getSprite(){

    return sprite;

}

/*
 * description: sets the scale variable =
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: scale variable is set
 *
*/
void Number::setScale(int scale){

    sprite.setScale(scale);

}

/*
 * description: gets the scale variable
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Number::getScale(){

    return scale;

}
