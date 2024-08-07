#include "common_moveable_piece.h"
using namespace stratego;


CommonMoveablePiece::CommonMoveablePiece(int rank, PlayerColor color, int max_squares)
    :CommonPiece::CommonPiece(rank, color),max_squares_{max_squares}{

}


bool CommonMoveablePiece::attackWon(const CommonPiece  &other) const {
   return *this > other;
}
