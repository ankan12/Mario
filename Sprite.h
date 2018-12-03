#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <fstream>
#include "SDL_Plotter.h"
#include <vector>

using namespace std;

struct Color{

    int r, g, b;

/*
 * description: determines if something color contains color values
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    bool isEqualTo(const Color& color);

};

struct Point{

    int x, y;

};


class Sprite{

private:

    int x, y;
    int currentFrame;
    int totalFrames;
    int scale;
    int xCrop, yCrop;

    int t;

    vector<Point> offset;

    vector<Color> colors;

    vector<char> characters;

/*
 * description: gets the color from characters
 * return: Color
 * precondition: class instance exists
 * postcondition: saves data into arrays
 *
*/
    Color colorFromCharacter(char input);

    bool isMirrored;

    vector<vector<vector<Color> > > pixels;

public:

/*
 * description: constructor for sprite class
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables set
 *
*/
    Sprite();

/*
 * description: constructor for sprite class
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables set to input
 *
*/
    Sprite(char filename[], ifstream& inFile);

/*
 * description: loads the image for the sprite
 * return: void
 * precondition: class instance exists
 * postcondition: sprite saved into vectors
 *
*/
    void loadImage(char filename[], ifstream& inFile);

/*
 * description: gets the value of x
 * return: Int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int get_x();

/*
 * description: gets the value of y
 * return: Int
 * precondition: class instance exists
 * postcondition: nothing is created
 *
*/
    int get_y();

/*
 * description: sets the x value
 * return: void
 * precondition: class instance exists and int passed in
 * postcondition: set_x is set
 *
*/
    void set_x(int x);

/*
 * description: sets the y value
 * return: void
 * precondition: class instance exists and int passed in
 * postcondition: set_y is set
 *
*/
    void set_y(int y);

/*
 * description: sets the location of the sprite on the screen
 * return: void
 * precondition: class instance exists and two ints passed in
 * postcondition: x and y of location are set
 *
*/
    void setLocation(int x, int y);

/*
 * description: loads the next frame
 * return: void
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    void nextFrame();

/*
 * description: loads next frame with a delay
 * return: void
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    void nextFrame(int wait);

/*
 * description: sets the current frame
 * return: void
 * precondition: class instance exists
 * postcondition: frame number is set
 *
*/
    void setCurrentFrame(int currentFrame);

/*
 * description: gets the current frame number
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int getCurrentFrame();

/*
 * description: gets the scale for the sprites
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int getScale();

/*
 * description: sets the scale for sprites
 * return: void
 * precondition: class instance exists
 * postcondition: scale variable is set
 *
*/
    void setScale(int);

/*
 * description: sets the offSet variable for sprites
 * return: void
 * precondition: class instance exists and three ints are passed in
 * postcondition: sets the offset for frameNumber
 *
*/
    void setOffset(int frameNumber, int x, int y);

/*
 * description: returns the offset frame number
 * return: Point
 * precondition: class instance exists and int passed in
 * postcondition: nothing is changed
 *
*/
    Point getOffset(int frameNumber);

/*
 * description: gets the height variable
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: private variables set
 *
*/
    int getHeight(int frameNumber);

/*
 * description: gets the width variable
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: private variables set
 *
*/
    int getWidth(int frameNumber);

/*
 * description: determines if the sprite is mirrored or not
 * return: void
 * precondition: class instance exists and bool is passed in
 * postcondition: changes a bool variable
 *
*/
    void setMirrored(bool);

/*
 * description: gets the pixels for the frame in rows and columns
 * return: Color
 * precondition: class instance exists and three ints are passed in
 * postcondition: returns the colors of the frame
 *
*/
    Color getPixel(int frameNumber, int col, int row);

/*
 * description: gets the numbers of pixels in a frame
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: nothing is changed
 *
*/
    int pixelsInFrame(int frameNumber);

/*
 * description: draws input to the screen
 * return: void
 * precondition: class instance exists and SDL is passed in
 * postcondition: input drawn on screen
 *
*/
    void draw(SDL_Plotter& p);

/*
 * description: gets the state of the mirrored variable
 * return: bool
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    bool mirrored();

/*
 * description: gets the amount of total frames
 * return: int
 * precondition: class instance exists
 * postcondition: nothing is changed
 *
*/
    int getTotalFrames();

/*
 * description: copies pixels into another sprite by reference
 * return: void
 * precondition: class instance exists and sprite is passed in
 * postcondition: passes sprites by reference
 *
*/
    void copyPixelsOnto(Sprite& sprite);

/*
 * description: sets the xCrop variable
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: changes dimensions of the sprites
 *
*/
    void set_xCrop(int xCrop);

/*
 * description: sets the yCrop variable
 * return: void
 * precondition: class instance exists and int is passed in
 * postcondition: changes y dimensions
 *
*/
    void set_yCrop(int yCrop);

/*
 * description: this function draws a square
 * return: void
 * precondition: class instance exists and three ints, a Color, and a SDL are passed in
 * postcondition: nothing is changed
 *
*/
    void plotSquare(int x, int y, int scale, Color color, SDL_Plotter& p);

/*
 * description: gets the scaled width
 * return: int
 * precondition: class instance exists and int is passed in
 * postcondition: nothing is changed
 *
*/
    int getScaledWidth(int frameNumber);

/*
 * description: gets the scaled height
 * return: int
 * precondition: class instance exists and bool is passed in
 * postcondition: nothing is changed
 *
*/
    int getScaledHeight(int frameNumber);

};

#endif // SPRITE_H_INCLUDED
