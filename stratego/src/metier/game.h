#ifndef GAME_H
#define GAME_H
#include "action_result.h"
#include "model.h"
#include <memory>
namespace stratego {
/**
* @brief the class that will structure our project joining all the other classes together
*/
class Game : public Model {
    Board board_;
    Player currentPlayer_;
    Player opponentPlayer_;
    State state_;
    ActionResult currentResult_;
    std::shared_ptr<Square> selectedSquare_;
    std::vector<Position> possibleMoves_;
public:
    /**
    * @brief constructor of Game creates a new game with default setting
    */
    Game();

    /**
     * @brief getter of board
     * @return the board
     */
    Board board() override {return board_;}

    /**
     * @brief getter of currentPlayer
     * @return the currentPlayer
     */
    Player currentPlayer() const override {return currentPlayer_;}

    /**
     * @brief getter of currentResult
     * @return the currentResult
     */
    ActionResult currentResult() const override {return currentResult_;}

    /**
     * @briefgetter of opponentPlayer
     * @return the opponentPlayer
     */
    Player opponentPlayer() const override{return opponentPlayer_;}

    /**
     * @brief initilizeBoard fill the board
     */
    void initializeBoardFromFile() override;

    /**
    * @brief provides boolean that indicates if the game is over
    * @return true if the game is over, false otherwise
    */
    bool isOver() override;

    /**
    * @brief select the square that contains the piece you want to play with
    * @param position
    * @return true if we can play with that piece,false otherwise
    */
    void selectSquare(const Position& position) override;

    /**
      * @brief getter of selectedSquare_
      * @return the Square selected by the current player
      */
    Square selectedSquare() override;

    /**
     * @brief cheks if the piece that the player want to select is moveable
     * @param position the position of the piece
     * @return true if the piece is moveable, false otherwise
     */
    bool canSelect(const Position& position) const override;

    /**
     * @brief moves the selected Piece to the wanted position
     * @param position
     * @return true if the move is made with success, false otherwise
     */
    void move(Position position) override;


    /**
     * @brief provides all the possible position where the piece in the selected square can be put
     * @return a vector that contains all the allowed positions
     */
    std::vector<Position> possibleMoves() const  override{return possibleMoves_;}

    /**
     * @brief provides all the possible moves that can be done by piece in the selected square
     * a vector with all the possible moves
     */
    void updatePossibleMoves() override;

    /**
     * @brief initializeBoardFromLines Will initialize the board of the players with corresponding piece to the ranks in the line
     * @param line
     */
    void initializeLine(const std::string& line, int row) override;

    /**
     * @brief provides all possibles moves of a piece
     * @param position the Position of the piece
     * @return a vector that contains all the allowed positions for this piece
     */
    std::vector<Position> getPossibleMovesForPiece(const Position &position) const override;

private:

    /**
     * @brief put the given piece to the square at the given position
     * @param position a given position
     */
    bool putPiece(std::shared_ptr<CommonPiece>, const Position& position);

    void state(const State& state){ state_=state;}

    /**
     * @brief remove the piece of the player
     * @param player
     * @param position a given position
     */
    void removePieceFromPlayer(Player& player, const Position& position);

    /**
     * @brief provides all possibles moves of a piece in a certain Direction
     * @return a vector of all Position where the piece can go
     */
    std::vector<Position> findPossibleMovesInDirection(int, const Position&, Direction ,  std::vector<Position> &) const;

    /**
     * @brief swapPlayers Swaps the player so the opponent becomes current and viceversa.
     */
    void swapPlayers() {auto tmp = opponentPlayer_; opponentPlayer_=currentPlayer_; currentPlayer_=tmp;}

};

}
#endif // GAME_H
