#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include "CollisionBox.h"

using namespace std;

struct Pipe{


    CollisionBox entrance;

    double exitX, exitY;

    double entranceX, entranceY;

    string direction;

/*
 * description: sets location of the pipe
 * return: void
 * precondition: instance of pipe exists
 * postcondition: location variables are set
 *
*/
    void assignToPipe(Pipe& pipe);

};



#endif // PIPE_H_INCLUDED
