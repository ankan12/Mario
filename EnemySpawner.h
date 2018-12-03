#ifndef ENEMYSPAWNER_H_INCLUDED
#define ENEMYSPAWNER_H_INCLUDED

#include "Enemy.h"
#include <vector>
#include <fstream>

class EnemySpawner{

private:

    vector<Enemy> listOfEnemies;
    int currentEnemy;
    int numOfPhases;

public:

    EnemySpawner();

    void readFile(char[], ifstream&);

    Enemy& getNextEnemy();

    int getNumOfPhases();

};


#endif // ENEMYSPAWNER_H_INCLUDED
