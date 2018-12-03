#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <string>

using namespace std;

enum EnemyType {shellcreeper, sidestepper, fighterfly, slipice, endOfPhase};

struct Enemy{

    EnemyType enemyType;
    int pipeNumber;

};

EnemyType stringToEnemyType(string input);


#endif // ENEMY_H_INCLUDED
