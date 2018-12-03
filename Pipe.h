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
