#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include "CollisionBox.h"

using namespace std;

struct Pipe{

    CollisionBox entrance;

    double exitX, exitY;

    double entranceX, entranceY;

    string direction;

    void assignToPipe(Pipe& pipe);

};



#endif // PIPE_H_INCLUDED
