#ifndef VIEW_H
#define VIEW_H

#include "board.h"
#include "player.h"
#include "utils/observer.h"
#include "game.h"
#include "utils/subject.h"

namespace stratego {

class View : public stratego::utils::Observer {

public:
    Model &model_;
    /**
     * @brief Constructor of view.
     * @param model of the game
     */
    inline View(Model &source) : model_{source} {
        source.addObserver(this);
    }

    /**
     * @brief Shows the game board.
     */
    void displayBoard(const Board &, const Player &);

    /**
     * @brief Asks the movement to the player.
     * @return the movement's player
     */
    int chooseMovement( const std::vector<Position> &);

    /**
     * @brief choosePiece
     * @param player
     * @return
     */
    Position choosePiece(const Model&);

    /**
     * @brief askModeFromFile Asks the player if he wants to use a file to fill the board.
     * @return true if he wishes, false otherwise
     */
    bool askModeFromFile();

    /**
     * @brief shows the end of the game.
     */
    void displayEnd(const Player &winner);

    /**
     * @brief update
     * @param message
     */
    void update(const std::string &message) override;

    void displayResult(const ActionResult& result, const Player& current, const Player& opponent);

    void showLineEnteringInstructions();

    std::string askLine(const Player&, int, unsigned long long);
};

}

#endif //VIEW_H
