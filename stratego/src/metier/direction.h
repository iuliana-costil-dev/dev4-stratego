/*|
 * \file direction.h
 * \brief The direction a piece can move to
 */
#ifndef DIRECTION_H
#define DIRECTION_H


namespace stratego {
/**
* @brief The direction enum represents the direction of the movement.
*/

enum class Direction {
    UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT
};

}

#endif // DIRECTION_H
