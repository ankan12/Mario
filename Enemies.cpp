#include "Enemies.h"
#include <iostream>
using namespace std;

Enemies::Enemies(Pipe& pipe0, Pipe& pipe1){

    this->pipe0.assignToPipe(pipe0);
    this->pipe1.assignToPipe(pipe1);

}

bool Enemies::addEnemy(Enemy& enemy, ifstream& inFile){

    switch(enemy.enemyType){

    case shellcreeper:{
        Shellcreeper e("turtle.txt",inFile,2,enemy.pipeNumber,pipe0,pipe1);
        e.getCBox().ID = enemyCBoxes.size();
        e.getHurtBox().ID = enemyHurtBoxes.size();
        shellcreepers.push_back(e);
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
        return false;
    }
    case sidestepper:{
        Sidestepper e("sidestepper.txt",inFile,2,enemy.pipeNumber,pipe0,pipe1);
        e.getCBox().ID = enemyCBoxes.size();
        e.getHurtBox().ID = enemyHurtBoxes.size();
        sidesteppers.push_back(e);
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
        return false;
    }

    case fighterfly:{
        Fighterfly e("fighterfly.txt",inFile,2,enemy.pipeNumber,pipe0,pipe1);
        e.getCBox().ID = enemyCBoxes.size();
        e.getHurtBox().ID = enemyHurtBoxes.size();
        fighterflies.push_back(e);
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
        return false;
    }
    case slipice:{
        Slipice e("slipice.txt",inFile,2,enemy.pipeNumber,pipe0,pipe1);
        e.getCBox().ID = enemyCBoxes.size();
        e.getHurtBox().ID = enemyHurtBoxes.size();
        slipices.push_back(e);
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
        return false;
    }

    default:
        return true;
    }

}

void Enemies::updateCollisionBoxes(){

    enemyCBoxes.clear();
    enemyHurtBoxes.clear();

    int ID = 0;

    for (int i = 0; i < shellcreepers.size(); i++, ID++){
        Shellcreeper& e = shellcreepers[i];
        e.getCBox().ID = ID;
        e.getHurtBox().ID = ID;
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
    }



    for (int i = 0; i < sidesteppers.size(); i++, ID++){
        Sidestepper& e = sidesteppers[i];
        e.getCBox().ID = ID;
        e.getHurtBox().ID = ID;
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
    }

    for (int i = 0; i < fighterflies.size(); i++, ID++){
        Fighterfly& e = fighterflies[i];
        e.getCBox().ID = ID;
        e.getHurtBox().ID = ID;
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
    }

    for (int i = 0; i < slipices.size(); i++, ID++){
        Slipice& e = slipices[i];
        e.getCBox().ID = ID;
        e.getHurtBox().ID = ID;
        enemyCBoxes.push_back(e.getCBox());
        enemyHurtBoxes.push_back(e.getHurtBox());
    }

}

void Enemies::updateLocations(){

    for (int i = 0; i < shellcreepers.size(); i++){

        Shellcreeper& e = shellcreepers[i];

        if (e.getState() == deadAndFalling && e.getY() > 400){
            e.setState(deadAndInvisible);
            shellcreepers.erase(shellcreepers.begin() + i);
        }
        e.updateLocation();
    }

    for (int i = 0; i < sidesteppers.size(); i++){

        Sidestepper& e = sidesteppers[i];

        if (e.getState() == deadAndFalling && e.getY() > 400){
            e.setState(deadAndInvisible);
            sidesteppers.erase(sidesteppers.begin() + i);
        }
        e.updateLocation();
    }

    for (int i = 0; i < fighterflies.size(); i++){

        Fighterfly& e = fighterflies[i];

        if (e.getState() == deadAndFalling && e.getY() > 400){
            e.setState(deadAndInvisible);
            fighterflies.erase(fighterflies.begin() + i);
        }
        e.updateLocation();
    }

    for (int i = 0; i < slipices.size(); i++){

        Slipice& e = slipices[i];

        if (e.getState() == deadAndInvisible){
            cout << "erase" << endl;
            slipices.erase(slipices.begin() + i);
        }
        e.updateLocation();
    }

}

void Enemies::solidCollisions(vector<CollisionBox>& solids){

    for (int i = 0; i < shellcreepers.size(); i++){
        shellcreepers[i].solidCollisions(solids);
    }

    for (int i = 0; i < sidesteppers.size(); i++){
        sidesteppers[i].solidCollisions(solids);
    }

    for (int i = 0; i < fighterflies.size(); i++){
        fighterflies[i].solidCollisions(solids);
    }

    for (int i = 0; i < slipices.size(); i++){
        slipices[i].solidCollisions(solids);
    }

}

void Enemies::draw(SDL_Plotter& p){

    for (int i = 0; i < shellcreepers.size(); i++){
        shellcreepers[i].draw(p);
    }

    for (int i = 0; i < sidesteppers.size(); i++){
        sidesteppers[i].draw(p);
    }

    for (int i = 0; i < fighterflies.size(); i++){
        fighterflies[i].draw(p);
    }

    for (int i = 0; i < slipices.size(); i++){
        slipices[i].draw(p);
    }

}

void Enemies::bumpEnemy(int ID){

    for (int i = 0; i < shellcreepers.size(); i++){

        Shellcreeper& e = shellcreepers[i];

        if (e.getCBox().ID != ID){
            continue;
        }

        if (e.getState() != grounded && e.getState() != bumpedAndGrounded && e.getState() != aliveAndFalling){
            continue;
        }

        e.setXVel(e.getXVel()*-1);
        e.setYVel(-2);
        e.getSprite().setCurrentFrame(8);
        e.setState(bumpedAndFalling);

    }

    for (int i = 0; i < sidesteppers.size(); i++){

        Sidestepper& e = sidesteppers[i];

        if (e.getCBox().ID != ID){
            continue;
        }

        if (e.getState() != grounded && e.getState() != bumpedAndGrounded && e.getState() != aliveAndFalling){
            continue;
        }

        if (e.getAngerCounter() == 0){

            cout << "angered" << endl;
            e.setYVel(-2);
            e.getSprite().setCurrentFrame(2);
            e.setState(aliveAndFalling);
            e.setAngerCounter(e.getAngerCounter()+1);
            e.setSpeedFactor(e.getSpeedFactor()+1);
            e.setXVel(e.getXVel() * e.getSpeedFactor());
            continue;
        }

        cout << "already angry" << endl;
        e.setXVel(e.getXVel()*-1);
        e.setYVel(-2);
        e.getSprite().setCurrentFrame(4);
        e.setState(bumpedAndFalling);

    }

    for (int i = 0; i < fighterflies.size(); i++){

        Fighterfly& e = fighterflies[i];

        if (e.getCBox().ID != ID){
            continue;
        }

        if (e.getState() != grounded && e.getState() != bumpedAndGrounded && e.getState() != aliveAndFalling){
            continue;
        }

        e.setXVel(e.getXVel()*-1);
        e.setYVel(-2);
        e.getSprite().setCurrentFrame(8);
        e.setState(bumpedAndFalling);

    }

    for (int i = 0; i < slipices.size(); i++){

        Slipice& e = slipices[i];

        if (e.getCBox().ID != ID){
            continue;
        }

        if (e.getState() != grounded && e.getState() != bumpedAndGrounded && e.getState() != aliveAndFalling && e.getState() != turningAround){
            continue;
        }

        e.setXVel(e.getXVel()*-1);
        e.setYVel(-2);
        e.getSprite().setCurrentFrame(6);
        e.setState(deadAndFalling);

    }

}

void Enemies::kickEnemyIfBumped(int ID, double xVel){

    for (int i = 0; i < shellcreepers.size(); i++){

        Shellcreeper& e = shellcreepers[i];

        if (e.getHurtBox().ID != ID){
            continue;
        }

        if (e.getState() == bumpedAndGrounded){
            e.setYVel(-2);
            e.setXVel(xVel);
            e.setYAccel(0.2);
            e.setState(deadAndFalling);

        }
    }

    for (int i = 0; i < sidesteppers.size(); i++){

        Sidestepper& e = sidesteppers[i];

        if (e.getHurtBox().ID != ID){
            continue;
        }

        if (e.getState() == bumpedAndGrounded){
            e.setYVel(-2);
            e.setXVel(xVel);
            e.setYAccel(0.2);
            e.setState(deadAndFalling);

        }
    }

    for (int i = 0; i < fighterflies.size(); i++){

        Fighterfly& e = fighterflies[i];

        if (e.getHurtBox().ID != ID){
            continue;
        }

        if (e.getState() == bumpedAndGrounded){
            e.setYVel(-2);
            e.setXVel(xVel);
            e.setYAccel(0.2);
            e.setState(deadAndFalling);

        }
    }

}

vector<CollisionBox>& Enemies::getEnemyCBoxes(){
    return enemyCBoxes;
}

vector<CollisionBox>& Enemies::getEnemyHurtBoxes(){
    return enemyHurtBoxes;
}

EnemyState Enemies::stateOfEnemy(int ID){

    for (int i = 0; i < shellcreepers.size(); i++){

        Shellcreeper& e = shellcreepers[i];

        if (e.getCBox().ID != ID){
            continue;
        }
        return e.getState();

    }

    for (int i = 0; i < sidesteppers.size(); i++){

        Sidestepper& e = sidesteppers[i];

        if (e.getCBox().ID != ID){
            continue;
        }
        return e.getState();

    }

    for (int i = 0; i < fighterflies.size(); i++){

        Fighterfly& e = fighterflies[i];

        if (e.getCBox().ID != ID){
            continue;
        }
        return e.getState();

    }

    for (int i = 0; i < slipices.size(); i++){

        Slipice& e = slipices[i];

        if (e.getCBox().ID != ID){
            continue;
        }
        return e.getState();

    }

    return grounded;
}

void Enemies::clearEnemies(){

    shellcreepers.clear();
    sidesteppers.clear();
    fighterflies.clear();
    slipices.clear();

}

vector<Slipice>& Enemies::getSlipices(){
    return slipices;
}
