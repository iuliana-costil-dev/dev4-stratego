#ifndef BOARD_H
#define BOARD_H
#include "square.h"
#include "position.h"
#include "common_moveable_piece.h"
#include <vector>

namespace stratego {
/**
* @brief represents the board of the game, that will contain our pieces
*/
class Board{
private:
    int size_=10;
    std::vector<std::vector<Square>> board_;

public:
    /**
    * @brief constructor of Board
    */
    Board();

    /**
     * @brief getter if size
     * @return size_
     */
    int size() const {return size_;}

    /**
     * @brief initialize fill the board
     */
    void initializeBLUE(std::ifstream& infile_BLUE);

    /**
     * @brief initialize fill the board
     */
    void initializeRED(std::ifstream& infile_RED);

    /**
     * @brief assignPieceToPosition
     */
    void assignPieceToPosition(Position& position, std::string& word);

    /**
    * @brief provides a boolean that is true if the position isinside the Board , false otherwise
    * @return true if the position isinside the Board , false otherwise
    */
    bool isInside(Position position) const;

    /**
    * @brief provides the square of the given position
    * @param position a given position
    * @return the square of the given position
    */
    Square square(Position position) const;

    /**
    * @brief put the given piece to the square at the given position
    * @param position a given position
    */
    bool put(std::shared_ptr<CommonPiece>, const Position& position);

    /**
    * @brief provides a boolean that is true if the the square at the position is free , false otherwise
    * @param position a given position
    * @return true if the the square at the position is free , false otherwise
    */
    bool isFree(Position position) const;

    /**
    * @brief return the piece who is at the square at the given position
    * @param position a given position
    * @return the piece that is at the square at the given position
    */
    std::shared_ptr<CommonPiece> piece(Position position) const;

    /**
    * @brief remove Remove the piece of the square at the position given
    *  @param position a given position
    */
    void remove(Position position);

    void move(Position from, Position to);

    /**
     * @brief isRedSection will return true if the red player can place his pieces at the given position at the start of the game
     * @param position
     * @return
     */
    bool isRedSection(Position position)const;


    /**
     * @brief isBlueSection will return true if the blue player can place his pieces at the given position at the start of the game
     * @param position
     * @return
     */
    bool isBlueSection(Position position) const;

    /**
     * @brief cheks if the Piece at the Position is a certain color
     * @param position a position
     * @param color a color
     * @return true if its the same color
     */
    bool matchesColor(Position position, PlayerColor color) const {return piece(position)->color() == color;}
};
}

#endif // BOARD_H
