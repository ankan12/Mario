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
#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include "Enemy.h"
#include "Shellcreeper.h"
#include <vector>
#include "Pipe.h"
#include "CollisionBox.h"
#include "Sidestepper.h"
#include <fstream>
#include "Fighterfly.h"
#include "Slipice.h"
#include <fstream>

class Enemies{

private:

    Pipe pipe0, pipe1;

    vector<CollisionBox> enemyCBoxes;

    vector<CollisionBox> enemyHurtBoxes;

    vector<Shellcreeper> shellcreepers;

    vector<Sidestepper> sidesteppers;

    vector<Fighterfly> fighterflies;

    vector<Slipice> slipices;

    ifstream inFile;

public:

    Enemies(Pipe&, Pipe&);

    bool addEnemy(Enemy& enemy, ifstream& inFile);

    vector<CollisionBox>& getEnemyCBoxes();

    vector<CollisionBox>& getEnemyHurtBoxes();

    vector<Shellcreeper>& getShellcreepers();

    vector<Slipice>& getSlipices();

    void updateCollisionBoxes();

    void updateLocations();

    void solidCollisions(vector<CollisionBox>& solids);

    void draw(SDL_Plotter& p);

    void bumpEnemy(int ID);

    EnemyState stateOfEnemy(int ID);

    void kickEnemyIfBumped(int ID, double xVel);

    void clearEnemies();

};

#endif // ENEMIES_H_INCLUDED
