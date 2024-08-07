#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game.h"
#include "view/view.h"

namespace stratego {

class Controller {
    Model &game_;
    View &view_;

public:
    /**
     * @brief Constructor of Controller.
     * @param game game
     * @param view view of the game
     */
    Controller(Model &game, View &view) :
        game_{game}, view_{view} {
    }

    /**
     * Starts the game.
     */
    void start();
};

}

#endif //CONTROLLER_H
