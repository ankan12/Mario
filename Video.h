#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <fstream>
#include "SDL_Plotter.h"

class Video{

private:
    ifstream inFile;
    int x = 0, y = 0;
    int width, height, totalFrames;
    int scale = 1;
    bool endOfVideo = false;

public:
    Video(char filename[]);

    void goToBeginning();

    void drawNextFrame(SDL_Plotter& p);

    bool reachedEndOfVideo();

};


#endif // VIDEO_H_INCLUDED
