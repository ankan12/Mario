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

void plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p){

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

void Sprite::plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p){

    for (int c = 0; c < scale; c++){

        if (yCrop != -1 && (y + c) > (this->y + yCrop)){
            return;
        }

        for (int c2 = 0; c2 < scale; c2++){

            if (xCrop != -1 && (x + c2) > (this->x + xCrop)){
                break;
            }

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

    pixels.resize(0);

    inFile.getline(buffer, 99);

    for (int f = 0; f < totalFrames; f++){

        int width = 0, widthCounter = 0;

        vector<Color> row;

        vector<vector<Color> > grid;

        char ch;

        ch = inFile.get();

        int c = 0;

        while (ch != '\\' && c < 250000){

            if (ch == '\n'){

                if (!row.empty()){
                    grid.push_back(row);
                }

                row.resize(0);

                if (widthCounter > width){
                    width = widthCounter;
                }

                widthCounter = 0;
            }
            else{
                row.push_back(colorFromCharacter(ch));
                widthCounter++;
            }

            ch = inFile.get();

            c++;
        }

        inFile.getline(buffer, 99);

        for (int r = 0; r < grid.size(); r++){

            grid[r].resize(width, {-1,-1,-1});

        }

        pixels.push_back(grid);

    }

    inFile.clear();
    inFile.close();

    offset.resize(pixels.size(), {0,0});

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

void Sprite::setOffset(int frameNumber, int x, int y){

    if (pixels.empty()){
        cout << "setOffset requires the image to be loaded." << endl;
        return;
    }

    offset[frameNumber] = {x,y};

}

int Sprite::getHeight(int frameNumber){
    return pixels[frameNumber].size();
}
int Sprite::getWidth(int frameNumber){
    return pixels[frameNumber][0].size();
}

void Sprite::setMirrored(bool input){
    isMirrored = input;
}

Color Sprite::getPixel(int frameNumber, int col, int row){

    return pixels[frameNumber][row][col];

}

int Sprite::pixelsInFrame(int frameNumber){

    int f = frameNumber;

    int output = 0;

    for (int r = 0; r < pixels[f].size(); r++){
        output += pixels[f][r].size();
    }

    return output;

}

void Sprite::draw(SDL_Plotter& p){

    if (pixels.empty()){
        cout << "draw requires the image to be loaded." << endl;
    }

    int px, py = 0;

    int cf = currentFrame;

    int offx = offset[cf].x, offy = offset[cf].y;

    for (int r = 0; r < pixels[cf].size(); r++){

        px = isMirrored ? pixels[cf][r].size() -1 : 0;

        for (int c = 0; c < pixels[cf][r].size(); c++){

            if(pixels[cf][r][c].r == -1){
                px += isMirrored ? -1 : 1;
                continue;
            }

            plotSquare(x + (px + offx) * scale, y + (py + offy) * scale,
                       scale, pixels[cf][r][c], p);

            px += isMirrored ? -1 : 1;

        }

        py++;

    }

}

Point Sprite::getOffset(int frameNumber){

    return offset[frameNumber];

}

bool Sprite::mirrored(){

    return isMirrored;

}

int Sprite::getTotalFrames(){

    return pixels.size();

}

void Sprite::copyPixelsOnto(Sprite& sprite){

    if (pixels.empty()){

        cout << "The pixels have to be set for the function to work." << endl;

    }

    sprite.pixels.resize(0);

    sprite.offset.resize(pixels.size(), {0,0});

    for (int f = 0; f < pixels.size(); f++){

        sprite.offset[f].x = offset[f].x;
        sprite.offset[f].y = offset[f].y;

    }

    for (int f = 0; f < pixels.size(); f++){

        vector<vector<Color> > grid;

        for (int r = 0; r < pixels[f].size(); r++){

            vector<Color> row;

            for (int c = 0; c < pixels[f][r].size(); c++){

                row.push_back(pixels[f][r][c]);

            }

            grid.push_back(row);

        }

        sprite.pixels.push_back(grid);

    }
}

void Sprite::set_xCrop(int xCrop){

    this->xCrop = xCrop;

}

void Sprite::set_yCrop(int yCrop){

    this->yCrop = yCrop;

}

int Sprite::getScaledWidth(int frameNumber){

    return pixels[frameNumber][0].size() * scale;

}

int Sprite::getScaledHeight(int frameNumber){

    return pixels[frameNumber].size() * scale;

}
