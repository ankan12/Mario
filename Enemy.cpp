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
