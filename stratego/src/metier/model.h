#ifndef MODEL_H
#define MODEL_H

#include "action_result.h"
#include "board.h"
#include "player.h"
#include "state.h"
#include "position.h"
#include "utils/subject.h"

namespace stratego {
/**
* @brief the class that will structure our project joining all the other classes together
*/
class Model : public stratego::utils::Subject {
public:
    inline static const std::string PROPERTY_BOARD{"Board"};
    inline static const std::string PROPERTY_ENDGAME{"End"};
    inline static const std::string PROPERTY_NEWRESULT{"result"};

    /**
     * @brief board
     * @return the board
     */
    virtual Board board()= 0;

    /**
     * @brief currentPlayer
     * @return the currentPlayer
     */
    virtual Player currentPlayer() const= 0;

    /**
     * @brief opponentPlayer
     * @return the opponentPlayer
     */
    virtual Player opponentPlayer() const = 0;


    /**
     * @brief currentResult
     * @return the currentResult
     */
    virtual ActionResult currentResult() const = 0;

    /**
     * @brief initilizeBoard fill the board
     */
    virtual void initializeBoardFromFile()= 0;

    /**
    * @brief provides boolean that indicates if the game is over
    * @return true if the game is over, false otherwise
    */
    virtual bool isOver()= 0;

    /**
     * @brief cheks if the piece that the player want to select is moveable
     * @param position the position of the piece
     * @return true if the piece is moveable, false otherwise
     */
    virtual bool canSelect(const Position& position) const =0;

    /**
    * @brief select the square that contains the piece you want to play with
    * @param position
    * @return true if we can play with that piece,false otherwise
    */
    virtual void selectSquare(const Position& position) = 0;

    /**
      * @brief provides the Square selected by the current player
      * @return the Square selected by the current player
      */
    virtual Square selectedSquare()= 0;

    /**
     * @brief moves the selected Piece to the wanted position
     * @param position
     * @return true if the move is made with success, false otherwise
     */
    virtual void move(Position position)= 0;

    /**
     * @brief provides all the possible position where the piece in the selected square can be put
     * @return a vector that contains all the allowed positions
     */
    virtual std::vector<Position> possibleMoves() const = 0;

    /**
     * @brief initializeLine Initializez the specified row of the board with the pieces that are in the line
     * @param line
     * @param row
     */
    virtual void initializeLine(const std::string& line, int row) =0;

    /**
     * @brief provides all the possible moves that can be done by piece in the selected square
     * a vector with all the possible moves
     */
    virtual void updatePossibleMoves()= 0;

    virtual std::vector<Position> getPossibleMovesForPiece(const Position &) const =0;

};

}

#endif // MODEL_H
