#ifndef PLAYER_H
#define PLAYER_H
#include "playerColor.h"
#include <vector>
#include "common_moveable_piece.h"
#include <algorithm>
namespace stratego  {
/**
* @brief The Player class represents the players of the game.
* The player is characterized by his color,
* and the pieces he owns.
*/
class Player {
    PlayerColor color_;
    std::vector<CommonPiece> pieces_;

public:
    /**
    * @brief constructor used to create a player
    * @param color of the player
    */
    Player(PlayerColor color);

    /**
    * @brief add a piece to the player’s pieces
    * @param piece a given piece
    */
    void addPiece(const CommonPiece &piece){ pieces_.push_back(piece);}
    /**
    * @brief remove the piece given to the player’s pieces
    * @param piece a given piece
    */
    void removePiece(int rank);

    /**
     * @brief getter of pieces_
     * @return all the pieces of the Player
     */
    std::vector<CommonPiece> pieces() const{return pieces_;}

    /**
     * @brief getter of color_
     * @return the color of the player
     */
    PlayerColor color() const{ return color_;}

};

}

#endif // PLAYER_H
