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
