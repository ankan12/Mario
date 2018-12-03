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
#include "Pipe.h"

/*
 * description: sets location of the pipe
 * return: void
 * precondition: instance of pipe exists
 * postcondition: location variables are set
 *
*/
void Pipe::assignToPipe(Pipe& pipe){

    CollisionBox& e = pipe.entrance;
    entrance.resetAtLocation(e.get_x(), e.get_y());
    entrance.setWidth(e.getWidth());
    entrance.setHeight(e.getHeight());
    entranceX = pipe.entranceX;
    entranceY = pipe.entranceY;
    exitX = pipe.exitX;
    exitY = pipe.exitY;
    direction = pipe.direction;

}
