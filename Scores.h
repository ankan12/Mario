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

/*
 * description: constructor for Score file
 * return: NA
 * precondition: instance of Score
 * postcondition: initialized the variables
 *
*/
    Score();

/*
 * description: sets the score
 * return: void
 * precondition: instance of Score and two variables are passed in
 * postcondition: score is set
 *
*/
    void setScore(int,int);

/*
 * description: sets the name
 * return: void
 * precondition: instance of Score
 * postcondition: sets the name variable
 *
*/
    void setName(string,int);


/*
 * description: gets the score
 * return: int
 * precondition: instance of Score and one int is passed in
 * postcondition: nothing is changed
 *
*/
    int getScore(int);

/*
 * description: gets the name
 * return: string
 * precondition: instance of Score and int passed in
 * postcondition: nothing is changed
 *
*/
    string getName(int);

/*
 * description: changes the scores
 * return: void
 * precondition: instance of Score
 * postcondition: name and score are set
 *
*/
    void changeScore(int, string);

/*
 * description: stores the scores
 * return: void
 * precondition: instance of Score
 * postcondition: scores are set into a file
 *
*/
    void storeScores();
};


#endif //GAMESCORETEST_SCORES_H
