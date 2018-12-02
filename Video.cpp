#include "Video.h"
#include "DrawingFunctions.h"
Video::Video(char filename[]){

    inFile.open(filename);

    inFile >> totalFrames >> width >> height;

}

void Video::goToBeginning(){

    inFile.clear();

    inFile.seekg(0L, ios::beg);

    int buffer;

    inFile >> buffer >> buffer >> buffer;

}

void Video::drawNextFrame(SDL_Plotter& p){

    for (int r = 0; r < height; r++){

        for (int c = 0; c < width; c++){

            int r, g, b;

            inFile >> r >> g >> b;

            if (inFile.eof()){

                endOfVideo = true;

                goToBeginning();

                return;
            }
            p.plotPixel(x + c, y + r, r, g, b);
            //plotSquare(x + (c*scale), y + (r*scale), scale, r, g, b, p);

        }

    }

}

bool Video::reachedEndOfVideo(){

    return endOfVideo;

}
