#ifndef WAVEANIMATION_H_INCLUDED
#define WAVEANIMATION_H_INCLUDED

#include <vector>
#include "Level.h"

using namespace std;

class WaveAnimation{

private:
    double a = 0.0;
    int startX;

    double speed_1sthalf = 0.1;
    double speed_2ndhalf = 0.1;

    double w = 10/3.14159;

    double distance = 30.0;

    double height = 8.0;

    int platformNumber;

public:
    WaveAnimation(int platformNumber, int startX);

    double y(int x);

    bool setNextFrame(vector<int>& columnLocations);
    //returns false when the animation has finished

    int getStartX();

    void setSpeed_1sthalf(double speed);
    void setSpeed_2ndhalf(double speed);
    void setWaveWidth(double w);

    void setDistance(double distance);

    double rightWave(int x);
    double leftWave(int x);

    bool finished();

    int platformNum();

    void setHeight(double height);

};


#endif // WAVEANIMATION_H_INCLUDED
