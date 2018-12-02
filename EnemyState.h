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
