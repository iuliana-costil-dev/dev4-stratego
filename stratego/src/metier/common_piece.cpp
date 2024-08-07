#include "common_piece.h"
#include <iostream>
using namespace stratego;

CommonPiece::CommonPiece(int rank, PlayerColor color):  rank_{rank}, color_{color}{
}

bool CommonPiece::attackWon( const CommonPiece &other) const{
   throw std::invalid_argument( "A common piece cannot move and therefore cannot attack.");
    return *this>other;
}

bool CommonPiece::isFlag() const{
    return this->rank() == 0;
}

bool CommonPiece::sameColor(CommonPiece &other){return color_ == other.color_;}


int CommonPiece::rank() const { return rank_;}

bool CommonPiece::operator> (const CommonPiece & other ) const{
    return this->rank() > other.rank();
}

bool CommonPiece::operator< (const CommonPiece & other ) const{
    return this->rank() < other.rank();
}

bool CommonPiece::operator==(const CommonPiece &defender )const {
    return this->rank()== defender.rank();
}
