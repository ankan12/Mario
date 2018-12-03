#include "TextBox.h"
#include <cctype>

/*
 * description: constructor for TextBox
 * return: NA
 * precondition: instance of TextBox exists
 * postcondition: variables are set to input
 *
*/
TextBox::TextBox(int x, int y, string text, char filename[], ifstream& inFile){

    set_x(x);
    set_y(y);
    setText(text);
    scale = 1;

    sprite.loadImage(filename, inFile);
    sprite.setScale(scale);
}

/*
 * description: constructor for TextBox
 * return: NA
 * precondition: instance of TextBox exists
 * postcondition: variables are set to input
 *
*/
TextBox::TextBox(char filename[], ifstream& inFile){
    scale = 1;

    sprite.loadImage(filename, inFile);

    sprite.setScale(scale);
}

/*
 * description: sets text to be displayed
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variable is set
 *
*/
void TextBox::setText(string text){

    this->text = text;

}

/*
 * description: sets x variable
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variable is set
 *
*/
void TextBox::set_x(int x){
    this->x = x;
}

/*
 * description: sets y variable
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variable is set
 *
*/
void TextBox::set_y(int y){
    this->y = y;
}

/*
 * description: sets location of text
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: variables are set
 *
*/
void TextBox::setLocation(int x, int y){
    set_x(x);
    set_y(y);
}

/*
 * description: gets x variable
 * return: int
 * precondition: instance of TextBox exists
 * postcondition: x variable is returned
 *
*/
int TextBox::get_x(){
    return x;
}

/*
 * description: gets y variable
 * return: int
 * precondition: instance of TextBox exists
 * postcondition: y variable is returned
 *
*/
int TextBox::get_y(){
    return y;
}

/*
 * description: sets the scale of text
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: scale is set
 *
*/
void TextBox::setScale(int scale){
    this->scale = scale;
    sprite.setScale(scale);

}

/*
 * description: draws to the screen
 * return: void
 * precondition: instance of TextBox exists
 * postcondition: no variables changed, draws to screen
 *
*/
void TextBox::draw(SDL_Plotter& p){

    int xLoc = x;
    int yLoc = y;

    for (int c = 0; c < text.size(); c++){

        sprite.setLocation(xLoc, yLoc);

        char ch = text[c];

        if (ch == '\n'){
            yLoc += sprite.getScaledHeight(0);
            xLoc = x;
            continue;
        }

        if (isalpha(ch)){
            ch = toupper(ch);
            sprite.setCurrentFrame(1 + (ch - 65));
        }
        else if (isdigit(ch)){
            sprite.setCurrentFrame(27 + (ch - 48));
        }
        else if (ch == '!'){
            sprite.setCurrentFrame(37);
        }
        else{
            sprite.setCurrentFrame(0);
        }

        sprite.draw(p);
        xLoc += sprite.getScaledWidth(sprite.getCurrentFrame());
    }

}
