#include "Music.h"
#include "SDL_mixer.h"

using namespace std;


Music::Music(void) {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	vMusic.loadMusic("md_die");
	vMusic.loadMusic("md_coin");
	vMusic.loadMusic("md_jump");
	vMusic.loadMusic("md_new");
	vMusic.loadMusic("md_sc");
	vMusic.loadMusic("md_touch");


	setVolume(100);
	this->currentMusic = mNOTHING;
}

Music::~Music(void) {
	for(int i = 0; i < vMusic.size(); i++) {
		Mix_FreeMusic(vMusic[i]);
	}

	vMusic.clear();

	for(int j = 0; j < vChunk.size(); j++) {
		Mix_FreeChunk(vChunk[j]);
	}

	vChunk.clear();
}


	if(currentMusic != eNew || forceChange) {
		StopMusic();
		currentMusic = eNew;
		PlayMusic();
	}
}

void Music::PlayMusic() {
	if(currentMusic != mNOTHING) {
		Mix_PlayMusic(vMusic[currentMusic - 1], -1);
		musicStopped = false;
	} else {
		StopMusic();
	}
}

void Music::PlayMusic(eMusic musicID) {
	if(musicID != mNOTHING) {
		Mix_PlayMusic(vMusic[musicID - 1], -1);
		musicStopped = false;
		currentMusic = musicID;
	} else {
		StopMusic();
		currentMusic = mNOTHING;
	}
}

void Music::StopMusic() {
	if(!musicStopped) {
		Mix_HaltMusic();
		musicStopped = true;
	}
}

void Music::PauseMusic() {
	if(Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
		musicStopped = false;
	} else {
		Mix_PauseMusic();
		musicStopped = true;
	}
}


void Music::PlayChunk(eChunk chunkID) {
	Mix_VolumeChunk(vChunk[chunkID], iVolume);
	Mix_PlayChannel(-1, vChunk[chunkID], 0);
}


Mix_Music* Music::loadMusic(string fileName) {
	fileName = "files/sounds/" + fileName + ".wav";
	return Mix_LoadMUS(fileName.c_str());
}

Mix_Chunk* Music::loadChunk(string fileName) {
	fileName = "files/sounds/" + fileName + ".wav";
	return Mix_LoadWAV(fileName.c_str());
}

int Music::getVolume() {
	return iVolume;
}

void Music::setVolume(int iVolume) {
	this->iVolume = iVolume;
	Mix_VolumeMusic(iVolume);
}
