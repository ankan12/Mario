#ifndef WAVEANIMATION_H_INCLUDED
#define WAVEANIMATION_H_INCLUDED

#include <vector>

using namespace std;

class WaveAnimation{

private:
    double a;
    int startX;

    double speed_1sthalf;
    double speed_2ndhalf;

    double w;

    double distance;

    double height;

    int platformNumber;

public:

/*
 * description: constructor for waveAnimation
 * return: NA
 * precondition: class instance exists
 * postcondition: private variables are set
 *
*/
    WaveAnimation(int platformNumber, int startX);

/*
 * description: calculates the y value for the x
 * return: double
 * precondition: instance of class exists, is passed int
 * postcondition: returns a double thats the corresponding y for the x
 *
*/

    double y(int x);


/*
 * description: sets up the next frame of the wave
 * return: bool
 * precondition: height and instances of class exist
 * postcondition: returns false when animation is done
 *
*/
    bool setNextFrame(vector<int>& columnLocations);


/*
 * description: returns the start x
 * return: int
 * precondition: instance of class exists
 * postcondition: nothing is changed
 *
*/
    int getStartX(); //this function isn't defined, do we need it?

/*
 * description: sets speed for half of the wave
 * return: void
 * precondition: wave exists
 * postcondition: wave speed is set
 *
*/
    void setSpeed_1sthalf(double speed);

/*
 * description: sets speed for other half of the wave
 * return: void
 * precondition: wave exists
 * postcondition: wave speed is set
 *
*/
    void setSpeed_2ndhalf(double speed);

/*
 * description: sets the width of the wave
 * return: void
 * precondition: wave exists, passed a double
 * postcondition: wave width is set
 *
*/
    void setWaveWidth(double w);


/*
 * description: sets the distance of the wave
 * return: void
 * precondition: wave exists, passed a double
 * postcondition: wave distance is set
 *
*/
    void setDistance(double distance);

/*
 * description: creates the wave behavior for right wave
 * return: double
 * precondition: wave exists, passed an int
 * postcondition: wave behavior is enacted on screen
 *
*/
    double rightWave(int x);

/*
 * description: creates the wave behavior for left wave
 * return: double
 * precondition: wave exists, passed an int
 * postcondition: wave behavior is enacted on screen
 *
*/
    double leftWave(int x);

/*
 * description: tells program when the wave animation is done executing
 * return: bool
 * precondition: wave exists
 * postcondition: nothing is changed
 *
*/
    bool finished();

/*
 * description: returns platform number
 * return: int
 * precondition: wave exists
 * postcondition: nothing is changed
 *
*/
    int platformNum();

/*
 * description: sets the wave height
 * return: void
 * precondition: wave exists
 * postcondition: height is set
 *
*/
    void setHeight(double height);

};


#endif // WAVEANIMATION_H_INCLUDED
