/*
 * SDL_Plotter.h
 * Version 2.1
 *  1/26/2018
 *  Dr. Booth
 */

#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_

//Windows Library
#include <SDL.h>
#include <SDL_mixer.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>
using namespace std;

const char UP_ARROW    = 1;
const char DOWN_ARROW  = 2;
const char LEFT_ARROW  = 3;
const char RIGHT_ARROW = 4;
const int RED_SHIFT   = 65536;
const int GREEN_SHIFT = 256;
const int BLUE_SHIFT  = 1;
const int ALPHA_SHIFT = 16777216;
const int WHITE = 255;
const int MAX_THREAD = 100;

#define MUS_PATH "scratch.wav"

//sample threaded sound function
static int Sound(void *data);

struct param{
	bool play;
	bool running;
	bool pause;
	SDL_Thread*  threadID;
	SDL_cond *cond;
	SDL_mutex *mut;
	string name;

	param(){
		play = false;
		running = false;
		pause = false;
	}
};

class SDL_Plotter{
private:
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	SDL_Window * window;

	bool leftMouseButtonDown;
    Uint32 * pixels;
    const Uint8* currentKeyStates;

    int row, col;
    bool quit;
    SDL_Event event;

    //Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

public:



    SDL_Plotter(int r=480, int c=640, bool WITH_SOUND = true);


    ~SDL_Plotter();

    void update();

    bool getQuit();

    bool kbhit();

    char getKey();

    void plotPixel(int x, int y, int r, int g, int b);

    void clear();

    int getRow();

    int getCol();

    void initSound(string sound);

    void setQuit(bool flag);

    void playSound(string sound);

    void quitSound(string sound);

    void Sleep(int ms);

    bool getMouseClick(int& x, int& y);

    bool getMouseDown(int& x, int& y);

    bool getMouseUp(int& x, int& y);

    bool getMouseMotion(int& x, int& y);

    void getMouseLocation(int& x, int& y);

};

#endif /* SDL_PLOTTER_H_ */
