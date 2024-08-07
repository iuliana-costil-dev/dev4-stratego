#ifndef COMMON_MOVEABLE_PIECE_H
#define COMMON_MOVEABLE_PIECE_H
#include "playerColor.h"
#include "square.h"
#include "common_piece.h"
namespace stratego {
/**
* @brief class that represents a simple piece
*/
class CommonMoveablePiece: public CommonPiece{
private:
    int max_squares_;
public:

  /**
  * @brief CommonMoveablePiece::CommonMoveablePiece simple constructor of commonMoveable
  * @param rank the rank of the piece
  * @param color the color of the piece
  * @param max_squares maximum steps of the piece
  */
    CommonMoveablePiece( int rank, PlayerColor color, int max_squares);

    /**
     * @brief provides a boolean that is true if the piece would win after the attacking the other piece
     * @param other
     * @return true if the piece would win, false otherwise
     */
    virtual bool attackWon( const CommonPiece &other) const  ;

    /**
     * @brief getter of max_square
     * @return max_Squares_
     */
    virtual int max_squares() const{return max_squares_;}

};

}
#endif // COMMON_MOVEABLE_PIECE_H
