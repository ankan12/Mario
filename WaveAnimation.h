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
