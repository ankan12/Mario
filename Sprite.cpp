#include "Sprite.h"
#include <vector>
#include <iostream>

using namespace std;


bool Color::isEqualTo(const Color& color){

    if (r == color.r && g == color.g && b == color.b){
        return true;
    }
    return false;

}

Sprite::Sprite(){



}

Sprite::Sprite(char filename[], ifstream& inFile){

    loadImage(filename, inFile);

}

void Sprite::set_x(int x){

    this->x = x;

}

void Sprite::set_y(int y){

    this->y = y;

}

void Sprite::setLocation(int x, int y){

    set_x(x);
    set_y(y);

}

int Sprite::get_x(){

    return x;

}

int Sprite::get_y(){

    return y;

}

int Sprite::getCurrentFrame(){

    return currentFrame;

}

void Sprite::nextFrame(){

    currentFrame++;

    if (currentFrame == totalFrames){
        currentFrame = 0;
    }

}

void Sprite::setCurrentFrame(int currentFrame){

    this->currentFrame = currentFrame % totalFrames;

}

int Sprite::getScale(){

    return scale;

}

void Sprite::setScale(int scale){

    this->scale = scale;

}

void Sprite::plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p){

    for (int c = 0; c < scale; c++){

        for (int c2 = 0; c2 < scale; c2++){

            int r, g, b;
            r = color.r;
            g = color.g;
            b = color.b;

            p.plotPixel(x + c2, y + c, r, g, b);

        }

    }

}

void Sprite::loadImage(char filename[], ifstream& inFile){

    inFile.open(filename);

    if (inFile.fail()){

        cout << "File \"" << filename << "\" not found." << endl;

    }

    char buffer[100];

    inFile >> buffer;

    int numberOfColors;

    inFile >> numberOfColors;

    colors.resize(numberOfColors);
    characters.resize(numberOfColors);

    for (int c = 0; c < colors.size(); c++){

        inFile >> characters[c];

        int r, g, b;

        inFile >> r >> g >> b;

        colors[c] = {r,g,b};

    }

    inFile >> buffer;

    inFile >> totalFrames;

    frames.resize(0);

    height.resize(0);
    width.resize(0);

    inFile.getline(buffer, 99);

    for (int f = 0; f < totalFrames; f++){

        int frameHeight = 0, widthCounter = 0;
        width.push_back(0);

        vector<Color> image;

        char ch;

        ch = inFile.get();

        int c = 0;

        while (ch != '\\' && c < 250000){

            image.push_back(colorFromCharacter(ch));

            if (image[image.size() -1].r == -2){

                if (widthCounter > width[width.size() -1]){
                    width[width.size() -1] = widthCounter;
                }

                widthCounter = 0;
                frameHeight++;
            }
            else{
                widthCounter++;
            }

            ch = inFile.get();

            c++;
        }
        Color finalColor = image[image.size() -1];

        height.push_back(frameHeight);

        frames.push_back(image);

        inFile.getline(buffer, 99);

    }

    inFile.clear();
    inFile.close();

    offset.resize(frames.size(), {0,0});

}

Color Sprite::colorFromCharacter(char input){


    if (input == '\n'){
        return {-2, -2, -2};
    }

    int index;
    for (index = 0; index < characters.size(); index++){

        if (characters[index] == input){
            break;
        }

        if (index == characters.size() - 1){
            return {-1, -1, -1};
        }
    }

    return colors[index];
}

void Sprite::draw(SDL_Plotter& plotter){

    if (frames.empty()){
        cout << "draw requires the image to be loaded." << endl;
        return;
    }

    if (isMirrored){
        mirroredDraw(plotter);
        return;
    }


    int f = currentFrame;

    int col = 0, row = 0;

    int offx = offset[f].x, offy = offset[f].y;

    for (int c = 0; c < frames[f].size(); c++){

        Color color = frames[f][c];

        if (color.r == -1){
            col++;
            continue;
        }

        if (color.r == -2){
            col = 0;
            row++;
            continue;
        }

        plotSquare(x + (col+offx)*scale,
                   y + (row+offy)*scale, scale, color, plotter);

        col++;
    }

}

void Sprite::setOffset(int frameNumber, int x, int y){

    if (frames.empty()){
        cout << "setOffset requires the images to be loaded." << endl;
        return;
    }

    offset[frameNumber] = {x,y};

}

int Sprite::getHeight(int frameNumber){
    return height[frameNumber];
}
int Sprite::getWidth(int frameNumber){
    return width[frameNumber];
}

void Sprite::setMirrored(bool input){
    isMirrored = input;
}

void Sprite::mirroredDraw(SDL_Plotter& plotter){

    int f = currentFrame;

    int col = width[f] - 1, row = 0;

    int offx = offset[f].x, offy = offset[f].y;

    for (int c = 0; c < frames[f].size(); c++){

        Color color = frames[f][c];

        if (color.r == -1){
            col--;
            continue;
        }

        if (color.r == -2){
            col = width[f] - 1;
            row++;
            continue;
        }

        plotSquare(x + (col+offx)*scale,
                   y + (row+offy)*scale, scale, color, plotter);

        col--;
    }

}

Color Sprite::getPixel(int frameNumber, int index){

    return frames[frameNumber][index];

}

int Sprite::pixelsInFrame(int frameNumber){

    return frames[frameNumber].size();

}
