#ifndef ACTIONRESULT_H
#define ACTIONRESULT_H

namespace stratego {
/**
* @brief The ActionResult enum represents the result of the movement made.
*/

enum class ActionResult {
    BOTH_LOST, CURRENT_LOST, OPPONENT_LOST, NOBODY_LOST
};

}

#endif // ACTIONRESULT_H
