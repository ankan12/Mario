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
#include "WaveAnimation.h"
#include <cmath>

const double PI = 3.14159;

using namespace std;

/*
 * description: constructor for waveAnimation
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set
 *
*/
WaveAnimation::WaveAnimation(int platformNumber, int startX){

    a = 0.0;
    speed_1sthalf = 0.5;
    speed_2ndhalf = 0.5;
    w = 10/3.14159;
    distance = 30.0;
    height = 8.0;

    this->startX = startX;
    this->platformNumber = platformNumber;

}

/*
 * description: creates the wave behavior for right wave
 * return: double
 * precondition: wave exists, passed an int
 * postcondition: wave behavior is enacted on screen
 *
*/
double WaveAnimation::rightWave(int x){

    int c = a - height/2.0;

    if (x <= -w*PI + c || x >= w*PI + c){
        return 0;
    }

    return cos(((double)(floor(x) - c))/w) + 1.0;

}

/*
 * description: creates the wave behavior for left wave
 * return: double
 * precondition: wave exists, passed an int
 * postcondition: wave behavior is enacted on screen
 *
*/
double WaveAnimation::leftWave(int x){

    int c = a - height/2.0;

    if (x <= -w*PI - c || x >= w*PI - c){
        return 0;
    }

    return cos(((double)(floor(x) + c))/w) + 1.0;

}

/*
 * description: calculates the y value for the x
 * return: double
 * precondition: instance of class exists, is passed int
 * postcondition: returns a double thats the corresponding y for the x
 *
*/
double WaveAnimation::y(int x){

    if (a <= height/2.0){

        if (x <= -w * PI || x >= w * PI){
            return 0;
        }

        double f = -1 * pow(a/sqrt(height/2.0) - sqrt(height/2.0), 2)
        + height/2.0;

        double output = cos(floor(x)/w) + 1;
        output *= f;

        return output * -1;
    }
    else{

        int c = a - height/2.0;

        double f = -((height/4.0)/(distance - height/2.0)) * ((double)c) +
        height/4.0;

        int output = f * (rightWave(x) + leftWave(x));
        if (output > 0){
            return output * -1;
        }

        return 0;

    }

}

/*
 * description: sets up the next frame of the wave
 * return: bool
 * precondition: height and instances of class exist
 * postcondition: returns false when animation is done
 *
*/
bool WaveAnimation::setNextFrame(vector<int>& columnLocations){

    if (a >= distance){
        return false;
    }

    for (int i = 0; i < columnLocations.size(); i++){

        columnLocations[i] += y(i - startX);

    }

    if (a <= height/2.0){
        a += speed_1sthalf;
        return true;
    }

    a += speed_2ndhalf;
    return true;

}

/*
 * description: sets speed for half of the wave
 * return: void
 * precondition: wave exists
 * postcondition: wave speed is set
 *
*/
void WaveAnimation::setSpeed_1sthalf(double speed){

    speed_1sthalf = speed;

}

/*
 * description: sets speed for other half of the wave
 * return: void
 * precondition: wave exists
 * postcondition: wave speed is set
 *
*/
void WaveAnimation::setSpeed_2ndhalf(double speed){

    speed_2ndhalf = speed;

}

/*
 * description: tells program when the wave animation is done executing
 * return: bool
 * precondition: wave exists
 * postcondition: nothing is changed
 *
*/
bool WaveAnimation::finished(){

    if (a >= distance){
        return true;
    }

    return false;

}

/*
 * description: returns platform number
 * return: int
 * precondition: wave exists
 * postcondition: nothing is changed
 *
*/
int WaveAnimation::platformNum(){

    return platformNumber;

}

/*
 * description: sets the distance of the wave
 * return: void
 * precondition: wave exists, passed a double
 * postcondition: wave distance is set
 *
*/
void WaveAnimation::setDistance(double distance){

    this->distance = distance;

}

/*
 * description: sets the width of the wave
 * return: void
 * precondition: wave exists, passed a double
 * postcondition: wave width is set
 *
*/
void WaveAnimation::setWaveWidth(double w){

    this->w = w;

}

/*
 * description: sets the wave height
 * return: void
 * precondition: wave exists
 * postcondition: height is set
 *
*/
void WaveAnimation::setHeight(double height){

    this->height = height;

}
