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
#ifndef MUSIC_H_INCLUDED //header guards for the file
#define MUSIC_H_INCLUDED

#include <string>

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

class bgMusic { //create bgMusic for a music file
private:
    string name; //has 2 variables
	int loops; //name of file and vol to play it at
public: //methods of bgMusic
    bgMusic(); //default constructor
    bgMusic(string localName); //constructor with name
    bgMusic(string localName, int numLoops); //constructor with name and loops
    void playMusic(); //method to play the music file
};

#endif // MUSIC_H_INCLUDED
