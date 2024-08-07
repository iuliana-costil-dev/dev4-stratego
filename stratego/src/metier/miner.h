#ifndef MINER_H
#define MINER_H
#include "common_moveable_piece.h"
namespace stratego {
class Miner : public CommonMoveablePiece {
private:
    static const int maxSquares_=1;
public:

    /**
    * @brief constructor used to create a miner
    * @param color the PlayerColor of the piece
    */
    Miner(int rank, int max_squares, PlayerColor color): CommonMoveablePiece::CommonMoveablePiece(rank, color, max_squares){

    }

    /**
     * @brief provides a boolean that is true if the piece would win after the attacking the other piece
     * @param other
     * @return true if the piece would win, false otherwise
     */
    bool attackWon(const CommonPiece &other) const{
        if(other.rank()==11){ //bomb
            return true;
        }else{
            return this->rank() > other.rank();
        }
    }

};
}
#endif // MINER_H
