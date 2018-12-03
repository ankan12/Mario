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
#include <SDL.h>
#include <SDL_mixer.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>

#include "SDL_Plotter.h"
using namespace std;

//Threaded Function
static int Sound(void *data){
    param *p = (param*)data;
    p->running = true;
    Mix_Chunk *gScratch = NULL;
    gScratch = Mix_LoadWAV( p->name.c_str() );
    while(p->running){
        SDL_mutexP( p->mut );
        SDL_CondWait(p->cond, p->mut);
        Mix_PlayChannel( -1, gScratch, 0 );
        p->play = false;
        SDL_mutexV(p->mut);
    }
    Mix_FreeChunk( gScratch );
    p->running = false;return 0;
}
//Function Definitions
SDL_Plotter::SDL_Plotter(int r, int c, bool WITH_SOUND){
	row = r;
	col = c;
	leftMouseButtonDown = false;
	quit = false;
	SOUND = WITH_SOUND;

	SDL_Init(SDL_INIT_AUDIO);

    window   = SDL_CreateWindow("SDL2 Pixel Drawing",
    		                     SDL_WINDOWPOS_UNDEFINED,
    		                     SDL_WINDOWPOS_UNDEFINED, col, row, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);

    texture  = SDL_CreateTexture(renderer,
    		                     SDL_PIXELFORMAT_ARGB8888,
    		                     SDL_TEXTUREACCESS_STATIC, col, row);

    pixels   = new Uint32[col * row];

    memset(pixels, WHITE, col * row * sizeof(Uint32));

    //SOUND Thread Pool
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    soundCount = 0;

  }


SDL_Plotter::~SDL_Plotter(){
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void SDL_Plotter::update(){
    SDL_UpdateTexture(texture, NULL, pixels, col * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool SDL_Plotter::getQuit(){
	return quit;
}

bool SDL_Plotter::kbhit(){
	bool flag = false;
	if(SDL_PollEvent(&event)){
		if(event.type == SDL_KEYDOWN){
			flag = true;
		}
		else if( event.type == SDL_QUIT )
		{
			quit = true;
		}
		else if(event.type == SDL_MOUSEBUTTONUP){
			SDL_PushEvent(&event);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN){
			SDL_PushEvent(&event);
		}
		else if(event.type == SDL_MOUSEMOTION){
			SDL_PushEvent(&event);
		}
	}
	return flag;
}

char SDL_Plotter::getKey(){

	char key = '\0';


	currentKeyStates = SDL_GetKeyboardState( NULL );
	if(currentKeyStates[SDL_SCANCODE_A]) key = 'A';
	if(currentKeyStates[SDL_SCANCODE_B]) key = 'B';
	if(currentKeyStates[SDL_SCANCODE_C]) key = 'C';
	if(currentKeyStates[SDL_SCANCODE_D]) key = 'D';
	if(currentKeyStates[SDL_SCANCODE_E]) key = 'E';
	if(currentKeyStates[SDL_SCANCODE_F]) key = 'F';
	if(currentKeyStates[SDL_SCANCODE_G]) key = 'G';
	if(currentKeyStates[SDL_SCANCODE_H]) key = 'H';
	if(currentKeyStates[SDL_SCANCODE_I]) key = 'I';
	if(currentKeyStates[SDL_SCANCODE_J]) key = 'J';
	if(currentKeyStates[SDL_SCANCODE_K]) key = 'K';
	if(currentKeyStates[SDL_SCANCODE_L]) key = 'L';
	if(currentKeyStates[SDL_SCANCODE_M]) key = 'M';
	if(currentKeyStates[SDL_SCANCODE_N]) key = 'N';
	if(currentKeyStates[SDL_SCANCODE_O]) key = 'O';
	if(currentKeyStates[SDL_SCANCODE_P]) key = 'P';
	if(currentKeyStates[SDL_SCANCODE_Q]) key = 'Q';
	if(currentKeyStates[SDL_SCANCODE_R]) key = 'R';
	if(currentKeyStates[SDL_SCANCODE_S]) key = 'S';
	if(currentKeyStates[SDL_SCANCODE_T]) key = 'T';
	if(currentKeyStates[SDL_SCANCODE_U]) key = 'U';
	if(currentKeyStates[SDL_SCANCODE_V]) key = 'V';
	if(currentKeyStates[SDL_SCANCODE_W]) key = 'W';
	if(currentKeyStates[SDL_SCANCODE_X]) key = 'X';
	if(currentKeyStates[SDL_SCANCODE_Y]) key = 'Y';
	if(currentKeyStates[SDL_SCANCODE_Z]) key = 'Z';
	if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
	if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
	if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
	if(currentKeyStates[SDL_SCANCODE_4]) key = '4';
	if(currentKeyStates[SDL_SCANCODE_5]) key = '5';
	if(currentKeyStates[SDL_SCANCODE_6]) key = '6';
	if(currentKeyStates[SDL_SCANCODE_7]) key = '7';
	if(currentKeyStates[SDL_SCANCODE_8]) key = '8';
	if(currentKeyStates[SDL_SCANCODE_9]) key = '9';
	if(currentKeyStates[SDL_SCANCODE_0]) key = '0';
	if(currentKeyStates[SDL_SCANCODE_SPACE]) key = ' ';
	if(currentKeyStates[SDL_SCANCODE_DOWN])  key = DOWN_ARROW;
	if(currentKeyStates[SDL_SCANCODE_UP])    key = UP_ARROW;
	if(currentKeyStates[SDL_SCANCODE_LEFT])  key = LEFT_ARROW;
	if(currentKeyStates[SDL_SCANCODE_RIGHT]) key = RIGHT_ARROW;
	if(currentKeyStates[SDL_SCANCODE_RETURN]) key = SDL_SCANCODE_RETURN;
	if(currentKeyStates[SDL_SCANCODE_ESCAPE]) quit = true;

    	return key;
}

void SDL_Plotter::plotPixel(int x, int y, int r, int g, int b){
    	pixels[y * col + x] = RED_SHIFT*r + GREEN_SHIFT*g + BLUE_SHIFT*b;
}

void SDL_Plotter::clear(){
	     memset(pixels, WHITE, col * row * sizeof(Uint32));
}

int SDL_Plotter::getRow(){
    return row;
}

int SDL_Plotter::getCol(){
    return col;
}

void SDL_Plotter::initSound(string sound){
	//int  *threadReturnValue;

	if(!soundMap[sound].running){
			param* p = &soundMap[sound];
			p->name = sound;
			p->cond = SDL_CreateCond();
			p->mut = SDL_CreateMutex();

			p->threadID = SDL_CreateThread( Sound, sound.c_str(), (void*)p );
	}
}

void SDL_Plotter::setQuit(bool flag){
	this->quit = flag;
}

void SDL_Plotter::playSound(string sound){
	if(soundMap[sound].running){
		SDL_CondSignal(soundMap[sound].cond);
	}
}

void SDL_Plotter::quitSound(string sound){
	soundMap[sound].running = false;
	SDL_CondSignal(soundMap[sound].cond);
}

void SDL_Plotter::Sleep(int ms){
	SDL_Delay(ms);
}

bool SDL_Plotter::getMouseClick(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONUP ){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

bool SDL_Plotter::getMouseDown(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONDOWN){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

bool SDL_Plotter::getMouseUp(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONUP){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

bool SDL_Plotter::getMouseMotion(int& x, int& y){
		bool flag = false;
		x = y = 0;
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEMOTION){
				//Get mouse position
				flag = true;
				SDL_GetMouseState( &x, &y );
			}
			else{
				SDL_PushEvent(&event);
			}
		}
		return flag;
}

void SDL_Plotter::getMouseLocation(int& x, int& y){
    SDL_GetMouseState( &x, &y );
    cout << x << " " << y << endl;
}

