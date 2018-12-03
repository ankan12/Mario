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
#include "Enemy.h"

EnemyType stringToEnemyType(string input){

    if (input == "shellcreeper"){
        return shellcreeper;
    }
    if (input == "sidestepper"){
        return sidestepper;
    }
    if (input == "fighterfly"){
        return fighterfly;
    }
    if (input == "slipice"){
        return slipice;
    }
    return endOfPhase;

}
