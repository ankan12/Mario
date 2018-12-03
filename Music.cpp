#include "Music.h" //include header file for music
#include <string> //include string for name
#include <SDL2/SDL.h> //include for INIT
#include <SDL2/SDL_mixer.h> //include for chunk

using namespace std;

Music::Music() { //default constructor
    name = "mb_die.wav"; //set to die sound
    volume = 100; //and standard vol 100
}

Music::Music(string localName) { //construct with string
    name = localName; //set name to parameter
    volume = 100; //default vol of 100
}

Music::Music(string localName, int localVolume) { //constructor with string and int
    name = localName; //set name to parameter
    volume = localVolume; //set volume to parameter
}

Music::setName(string localName) { //modifier for name
    name = localName; //set name to parameter
}

Music::setVolume(int localVolume) { //modifier for volume
    volume = localVolume; //set volume to parameter
}

void Music::playSound() { //function to play sound
    SDL_Init(SDL_INIT_EVERYTHING); //initialize SDL
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); //open audio

    Mix_Chunk *sound = Mix_LoadWAV(name.c_str()); //create a chunk of file

    Mix_VolumeChunk(sound, volume); //set volume to the variable

    Mix_PlayChannel(-1, sound, 0); //plays the sound
}
