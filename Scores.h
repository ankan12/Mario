//
// Created by Brandon Alcaraz on 11/10/2018.
//

#ifndef GAMESCORETEST_SCORES_H
#define GAMESCORETEST_SCORES_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

class Score {
protected:
        int hscore1,hscore2,hscore3,hscore4,hscore5;
        string name1,name2,name3,name4,name5;
        fstream scoreFile;
public:

    Score();

    void setScore(int,int);
    void setName(string,int);

    int getScore(int);
    string getName(int);

    void changeScore(int, string);
    void storeScores();
};


#endif //GAMESCORETEST_SCORES_H
