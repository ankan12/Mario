/*Authors:
Anupama Kannan
Brandon Alcaraz
Miranda Montroy
Samuel Kim
Thomas Cho
*Assignment Title: Mario Bros.
*Assignment Description: Recreate Mario Bros.
*Due Date 12/2/2018
*Date Created 11/4/2018
*Date Last Modified 12/2/2018
*/
#include "Sprite.h"
#include <vector>
#include <iostream>

using namespace std;

/*
 * description: determines if something color contains color values
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
bool Color::isEqualTo(const Color& color){

    if (r == color.r && g == color.g && b == color.b){
        return true;
    }
    return false;

}

/*
 * description: constructor for sprite class
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables set
 *
*/
Sprite::Sprite(){
    x = 0;
    y = 0;
    t = 0;
    currentFrame = 0;
    totalFrames = 1;
    scale = 1;
    xCrop = -1;
    yCrop = -1;
    isMirrored = false;
}

/*
 * description: constructor for sprite class
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables set to input
 *
*/
Sprite::Sprite(char filename[], ifstream& inFile){
    x = 0;
    y = 0;
    t = 0;
    currentFrame = 0;
    totalFrames = 1;
    scale = 1;
    xCrop = -1;
    yCrop = -1;
    isMirrored = false;

    loadImage(filename, inFile);

}

/*
 * description: sets the x value
 * return: void
 * precondition: class instance exists and int passed in
 * postcondition: set_x is set
 *
*/
void Sprite::set_x(int x){

    this->x = x;

}

/*
 * description: sets the y value
 * return: void
 * precondition: class instance exists and int passed in
 * postcondition: set_y is set
 *
*/
void Sprite::set_y(int y){

    this->y = y;

}

/*
 * description: sets the location of the sprite on the screen
 * return: void
 * precondition: class instance exists and two ints passed in
 * postcondition: x and y of location are set
 *
*/
void Sprite::setLocation(int x, int y){

    set_x(x);
    set_y(y);

}

/*
 * description: gets the value of x
 * return: Int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Sprite::get_x(){

    return x;

}

/*
 * description: gets the value of y
 * return: Int
 * precondition: class instance exists
 * postcondition: nothing is created
 *
*/
int Sprite::get_y(){

    return y;

}

/*
 * description: gets the current frame number
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Sprite::getCurrentFrame(){

    return currentFrame;

}

/*
 * description: loads the next frame
 * return: void
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
void Sprite::nextFrame(){

    currentFrame++;

    if (currentFrame == totalFrames){
        currentFrame = 0;
    }

}

/*
 * description: loads next frame with a delay
 * return: void
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
void Sprite::nextFrame(int wait){


    if (t == wait){
        nextFrame();
        t = 0;
    }

    t++;

}

/*
 * description: sets the current frame
 * return: void
 * precondition: class instance exists
 * postcondition: frame number is set
 *
*/
void Sprite::setCurrentFrame(int currentFrame){

    this->currentFrame = currentFrame % totalFrames;

}

/*
 * description: gets the scale for the sprites
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Sprite::getScale(){

    return scale;

}

/*
 * description: sets the scale for sprites
 * return: void
 * precondition: class instance exists
 * postcondition: scale variable is set
 *
*/
void Sprite::setScale(int scale){

    this->scale = scale;

}

/*
 * description: this function draws a square
 * return: void
 * precondition: class instance exists and three ints, a Color, and a SDL are passed in
 * postcondition: nothing is changed
 *
*/
void Sprite::plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p){

    for (int c = 0; c < scale; c++){

        if (yCrop != -1 && (y + c) > (this->y + yCrop)){
            return;
        }

        if ( (y + c >= 400) || (y + c < 0)){
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

/*
 * description: loads the image for the sprite
 * return: void
 * precondition: class instance exists
 * postcondition: sprite saved into vectors
 *
*/
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

/*
 * description: gets the color from characters
 * return: Color
 * precondition: class instance exists
 * postcondition: saves data into arrays
 *
*/
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

/*
 * description: sets the offSet variable for sprites
 * return: void
 * precondition: class instance exists and three ints are passed in
 * postcondition: sets the offset for frameNumber
 *
*/
void Sprite::setOffset(int frameNumber, int x, int y){

    if (pixels.empty()){
        cout << "setOffset requires the image to be loaded." << endl;
        return;
    }

    offset[frameNumber] = {x,y};

}

/*
 * description: gets the height variable
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: private variables set
 *
*/
int Sprite::getHeight(int frameNumber){
    return pixels[frameNumber].size();
}

/*
 * description: gets the width variable
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: private variables set
 *
*/
int Sprite::getWidth(int frameNumber){
    return pixels[frameNumber][0].size();
}

/*
 * description: determines if the sprite is mirrored or not
 * return: void
 * precondition: class instance exists and bool is passed in
 * postcondition: changes a bool variable
 *
*/
void Sprite::setMirrored(bool input){
    isMirrored = input;
}

/*
 * description: gets the pixels for the frame in rows and columns
 * return: Color
 * precondition: class instance exists and three ints are passed in
 * postcondition: returns the colors of the frame
 *
*/
Color Sprite::getPixel(int frameNumber, int col, int row){

    return pixels[frameNumber][row][col];

}

/*
 * description: gets the numbers of pixels in a frame
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: nothing is changed
 *
*/
int Sprite::pixelsInFrame(int frameNumber){

    int f = frameNumber;

    int output = 0;

    for (int r = 0; r < pixels[f].size(); r++){
        output += pixels[f][r].size();
    }

    return output;

}

/*
 * description: draws input to the screen
 * return: void
 * precondition: class instance exists and SDL is passed in
 * postcondition: input drawn on screen
 *
*/
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

/*
 * description: returns the offset frame number
 * return: Point
 * precondition: class instance exists and int passed in
 * postcondition: nothing is changed
 *
*/
Point Sprite::getOffset(int frameNumber){

    return offset[frameNumber];

}

/*
 * description: gets the state of the mirrored variable
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
bool Sprite::mirrored(){

    return isMirrored;

}

/*
 * description: gets the amount of total frames
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
int Sprite::getTotalFrames(){

    return pixels.size();

}

/*
 * description: copies pixels into another sprite by reference
 * return: void
 * precondition: class instance exists and sprite is passed in
 * postcondition: passes sprites by reference
 *
*/
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


/*
 * description: sets the xCrop variable
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: changes dimensions of the sprites
 *
*/
void Sprite::set_xCrop(int xCrop){

    this->xCrop = xCrop;

}

/*
 * description: sets the yCrop variable
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: changes y dimensions
 *
*/
void Sprite::set_yCrop(int yCrop){

    this->yCrop = yCrop;

}

/*
 * description: gets the scaled width
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: nothing is changed
 *
*/
int Sprite::getScaledWidth(int frameNumber){

    return pixels[frameNumber][0].size() * scale;

}


/*
 * description: gets the scaled height
 * return: int
 * precondition: class instance exists and bool is passed in
 * postcondition: nothing is changed
 *
*/
int Sprite::getScaledHeight(int frameNumber){

    return pixels[frameNumber].size() * scale;

}

void Sprite::shiftRGBvalues(int r, int g, int b){

    int cf = getCurrentFrame();

    for (int y = 0; y < pixels[cf].size(); y++){

        for (int x = 0; x < pixels[cf][y].size(); x++){

            Color& c = pixels[cf][y][x];
            c.r += r;
            c.g += g;
            c.b += b;

        }

    }

}
