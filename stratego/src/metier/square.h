#ifndef SQUARE_H
#define SQUARE_H
#include "common_piece.h"
#include "position.h"
#include <memory>
#include <iostream>
namespace stratego {
/**
* @brief refers to a square of our 10x10 squares game board
*/
class Square{
private:
    bool isLand_;
    std::shared_ptr<CommonPiece> piece_;
    Position position_;
public:
    /**
    * @brief constructor used to create a square
    * @param the squareType
    */
    Square(bool isLand, Position position): isLand_ {isLand},piece_{nullptr}, position_{position}{}

    /**
     * @brief cheks if the piece that is in the Square is moveable
     * @return true if it is moveable, false otherwise
     */
    bool pieceMoves()const{return piece_->max_squares()>0;}


    /**
     * @brief add a piece in the square
     * @param a certain piece
     * @return true if the piece is put with success, false otherwise
     */
    inline bool putPiece(std::shared_ptr<CommonPiece>);

    /**
    * @brief remove the piece of the square
    * @param a certain piece
    */
    inline void removePiece();


    /**
     * @brief getter of piece
     * @return the piece
     */
    inline std::shared_ptr<CommonPiece> piece() const;

    /**
     * @brief getter of position
     * @return the position of the square
     */
    Position position() const{ return position_;}

    /**
    * @brief provides a boolean that is true if the square type is LAND, false otherwise
    * @return true if the square type is LAND, false otherwise.
    */
    bool isLand(){ return isLand_; }

    /**
     * @brief isFree provides a bool that shows us if the square is occupied by a piece
     * @return true if the square is empty, false otherwise
     */
    bool isFree() const { if(piece_ == nullptr) return true; else return false;}
};


std::shared_ptr<CommonPiece> Square::piece() const
{
    if(this->isFree())
        throw std::invalid_argument( "There is no piece here.");
    return piece_;
}

void Square::removePiece(){
    this->piece_.reset();
}

bool Square::putPiece(std::shared_ptr<CommonPiece> piece)
{
    this->piece_.reset();
    this->piece_ = piece;
    return true;
}


}
#endif // SQUARE_H
