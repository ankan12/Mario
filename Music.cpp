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
#include "Music.h" //include header file for music to make objects and methods
#include <string> //include string for name
#include <SDL.h> //include for INIT
#include <SDL_mixer.h> //include for chunk and music objects

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
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); //open audio

    Mix_Chunk *sound = Mix_LoadWAV(name.c_str()); //create a chunk of file

    Mix_VolumeChunk(sound, volume); //set volume to the variable

    Mix_PlayChannel(-1, sound, 0); //plays the sound
}

bgMusic::bgMusic() { //default constructor
    name = "mb_die.wav"; //set to die sound
    loops = 0; //set loops to default once
}

bgMusic::bgMusic(string localName) { //construct with string
    name = localName; //set name to parameter
    loops = 0; //set loops to default once
}

bgMusic::bgMusic(string localName, int localLoops) { //constructor with string and int
    name = localName; //set name to parameter
    loops = localLoops; //set volume to parameter
}

void bgMusic::playMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); //open audio

    Mix_Music *bgSound = Mix_LoadMUS(name.c_str()); //create a music file

    Mix_PlayMusic(bgSound, loops); //play the music with # of loops
}

