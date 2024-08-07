#ifndef SPY_H
#define SPY_H
#include "common_moveable_piece.h"
namespace stratego {
class Spy : public CommonMoveablePiece {

private:
    static const int maxSquares_=1;
public:
    /**
    * @brief constructor used to create a spy
    * @param color the PlayerColor of the piece
    */
    Spy(int rank, int max_squares,PlayerColor color): CommonMoveablePiece::CommonMoveablePiece(rank,color,max_squares){

    };

    /**
     * @brief provides a boolean that is true if the piece would win after the attacking th eother piece
     * @param other
     * @return true if the piece would win, false otherwise
     */
     bool attackWon(const CommonPiece &other) const{
           if(other.rank()==10){ //marshall
                       return true;}
                   else{
                       return this->rank()> other.rank();
                   }
       }

};
}
#endif // SPY_H
