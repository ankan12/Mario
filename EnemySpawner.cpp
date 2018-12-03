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
#include "EnemySpawner.h"
#include <iostream>
using namespace std;

EnemySpawner::EnemySpawner(){
    currentEnemy = 0;
}

void EnemySpawner::readFile(char filename[], ifstream& inFile){

    listOfEnemies.clear();

    inFile.open(filename);

    inFile >> numOfPhases;

    Enemy enemy;

    string enemyType;
    int pipeNumber;

    while(inFile >> enemyType >> pipeNumber){
        enemy.enemyType = stringToEnemyType(enemyType);
        enemy.pipeNumber = pipeNumber;
        listOfEnemies.push_back(enemy);
    }

    currentEnemy = 0;

    inFile.close();

}

Enemy& EnemySpawner::getNextEnemy(){
    int i = currentEnemy;
    currentEnemy++;
    return listOfEnemies[i];
}

int EnemySpawner::getNumOfPhases(){
    return numOfPhases;
}
