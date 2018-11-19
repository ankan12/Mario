#include "TextBox.h"
#include <cctype>
TextBox::TextBox(int x, int y, string text, char filename[], ifstream& inFile){

    set_x(x);
    set_y(y);
    setText(text);
    scale = 1;

    sprite.loadImage(filename, inFile);
    sprite.setScale(scale);
}

TextBox::TextBox(char filename[], ifstream& inFile){
    scale = 1;

    sprite.loadImage(filename, inFile);

    sprite.setScale(scale);
}

void TextBox::setText(string text){

    this->text = text;

}

void TextBox::set_x(int x){
    this->x = x;
}
void TextBox::set_y(int y){
    this->y = y;
}

void TextBox::setLocation(int x, int y){
    set_x(x);
    set_y(y);
}

int TextBox::get_x(){
    return x;
}
int TextBox::get_y(){
    return y;
}

void TextBox::setScale(int scale){
    this->scale = scale;
    sprite.setScale(scale);

}

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
