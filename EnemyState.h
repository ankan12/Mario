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
#ifndef ENEMYSTATE_H_INCLUDED
#define ENEMYSTATE_H_INCLUDED


/*
 * description: function that determines the enemy state
 * return: enum
 * precondition: various states passed in
 * postcondition: variables are set to input
 *
*/
enum EnemyState {grounded, aliveAndFalling, enteringPipe, exitingPipe, deadAndFalling,
bumpedAndFalling, bumpedAndGrounded, deadAndInvisible, turningAround};

#endif // ENEMYSTATE_H_INCLUDED
