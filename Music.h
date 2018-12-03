#ifndef MUSIC_H_INCLUDED //header guards for the file
#define MUSIC_H_INCLUDED

using namespace std; //set standard name space

class Music //create a music class
{
private:
	string name; //has 2 variables
	int volume; //name of file and vol to play it at

public:
    Music(); //default constructor with no parameters
	Music(string localName); //constructor with name
	Music(string localName, int localVolume); //constructor with name and vol
	setName(string localName); //modifier to change name
    setVolume(int localVolume); //modifier to change volume
	void playSound(); //function to play the sound
};

#endif // MUSIC_H_INCLUDED
