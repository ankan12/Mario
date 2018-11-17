#include "WaveAnimation.h"
#include <cmath>

const double PI = 3.14159;

using namespace std;

WaveAnimation::WaveAnimation(int platformNumber, int startX){

    this->startX = startX;
    this->platformNumber = platformNumber;

}

double WaveAnimation::rightWave(int x){

    int c = a - height/2.0;

    if (x <= -w*PI + c || x >= w*PI + c){
        return 0;
    }

    return cos(((double)(floor(x) - c))/w) + 1.0;

}

double WaveAnimation::leftWave(int x){

    int c = a - height/2.0;

    if (x <= -w*PI - c || x >= w*PI - c){
        return 0;
    }

    return cos(((double)(floor(x) + c))/w) + 1.0;

}

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

void WaveAnimation::setSpeed_1sthalf(double speed){

    speed_1sthalf = speed;

}

void WaveAnimation::setSpeed_2ndhalf(double speed){

    speed_2ndhalf = speed;

}

bool WaveAnimation::finished(){

    if (a >= distance){
        return true;
    }

    return false;

}

int WaveAnimation::platformNum(){

    return platformNumber;

}

void WaveAnimation::setDistance(double distance){

    this->distance = distance;

}

void WaveAnimation::setWaveWidth(double w){

    this->w = w;

}

void WaveAnimation::setHeight(double height){

    this->height = height;

}
