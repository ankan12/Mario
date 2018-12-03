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
