//
// Created by Brandon Alcaraz on 11/10/2018.
//

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdlib>

#include "Scores.h"

Score::Score() {
    scoreFile.open("scores.txt");
    if(!scoreFile){
        cout << "File not found." << endl;
        exit(404);
    }

    scoreFile >> hscore1;
    scoreFile >> hscore2;
    scoreFile >> hscore3;
    scoreFile >> hscore4;
    scoreFile >> hscore5;

    scoreFile >> name1;
    scoreFile >> name2;
    scoreFile >> name3;
    scoreFile >> name4;
    scoreFile >> name5;

    scoreFile.close();
}


void Score::setScore(int s, int num) {
    switch (num){
        case 1:{
            this->hscore1 = s;
            break;
        }
        case 2:{
            this->hscore2 = s;
            break;
        }
        case 3:{
            this->hscore3 = s;
            break;
        }
        case 4:{
            this->hscore4 = s;
            break;
        }
        case 5: default:{
            this->hscore5 = s;
            break;
        }
    }
}

void Score::setName(string n, int num) {
    switch (num){
        case 1:{
            this->name1 = n;
            break;
        }
        case 2:{
            this->name2 = n;
            break;
        }
        case 3:{
            this->name3 = n;
            break;
        }
        case 4:{
            this->name4 = n;
            break;
        }
        case 5: default:{
            this->name5 = n;
            break;
        }
    }

}

int Score::getScore(int num){
    switch (num){
        case 1:{
            return this->hscore1;
        }
        case 2:{
            return this->hscore2;
        }
        case 3:{
            return this->hscore3;
        }
        case 4:{
            return this->hscore4;
        }
        case 5: default:{
            return this->hscore5;
        }
    }
}

string Score::getName(int num){
    switch (num){
        case 1:{
            return this->name1;
        }
        case 2:{
            return this->name2;
        }
        case 3:{
            return this->name3;
        }
        case 4:{
            return this->name4;
        }
        case 5: default:{
            return this->name5;
        }
    }
}

void Score::changeScore(int s, string n){
    if (s > hscore1){
        // Lower Scores
        setScore(hscore4,5);
        setName(name4,5);
        setScore(hscore3,4);
        setName(name3,4);
        setScore(hscore2,3);
        setName(name2,3);
        setScore(hscore1,2);
        setName(name1,2);
        // Add new Score
        setScore(s,1);
        setName(n,1);

        return;
    }
    else if (s > hscore2){
        // Lower Scores
        setScore(hscore4,5);
        setName(name4,5);
        setScore(hscore3,4);
        setName(name3,4);
        setScore(hscore2,3);
        setName(name2,3);
        // Add new score
        setScore(s,2);
        setName(n,2);

        return;
    }
    else if (s > hscore3){
        // Lower Scores
        setScore(hscore4,5);
        setName(name4,5);
        setScore(hscore3,4);
        setName(name3,4);
        // Add new score
        setScore(s,3);
        setName(n,3);

        return;

    }
    else if (s > hscore4){
        // Lower scores
        setScore(hscore4,5);
        setName(name4,5);
        // Add new score
        setScore(s,4);
        setName(n,4);

        return;
    }
    else if (s > hscore5){
        setScore(s,5);
        setName(n,5);
        return;
    }
}

void Score::storeScores() {
    scoreFile.open("scores.txt");
    if (!scoreFile){
        cout << "Error. File not Found." << endl;
        exit(404);
    }

    scoreFile << hscore1 << " ";
    scoreFile << hscore2 << " ";
    scoreFile << hscore3 << " ";
    scoreFile << hscore4 << " ";
    scoreFile << hscore5 << endl;

    scoreFile << name1 << " ";
    scoreFile << name2 << " ";
    scoreFile << name3 << " ";
    scoreFile << name4 << " ";
    scoreFile << name5 << endl;

    scoreFile.close();
}