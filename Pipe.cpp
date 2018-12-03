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
