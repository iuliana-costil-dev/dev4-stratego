#ifndef COMMON_PIECE_H
#define COMMON_PIECE_H
#include "playerColor.h"
#include <iostream>
namespace stratego {
/**
* @brief class that represents a simple piece that is not moveable
*/
class CommonPiece{
private:
    int rank_;
    PlayerColor color_;
public:
  /**
  * @brief  simple constructor of CommonPiece
  * @param rank the rank of the piece
  * @param color the color of the piece
  */
    CommonPiece( int rank, PlayerColor color);

    /**
     * @brief default constructor
     */
    CommonPiece() = default;

    /**
    * @brief provides a boolean that shows if the pieces have the same color
    * @param square a certain piece
    *@return true if the pieces have the same color, false otherwise
    */
    bool sameColor(CommonPiece &other);

    /**
     * @brief provides a boolean that is true if the piece would win after the attacking th eother piece
     * @param other
     * @return true if the piece would win, false otherwise
     */
    virtual bool attackWon( const CommonPiece &other)const;

    /**
     * @brief max_square
     * @return the maximum steps
     */
    virtual int max_squares() const{return 0;}

    /**
     * @brief getter of color
     * @return the color of the piece
     */
    PlayerColor color() const{return color_;}

    /**
     * @brief provides a boolean that is true if the rank of the piece is equal to 0 , false otherwise
     * @param other
     * @return true if the rank of the piece is equal to 0, false otherwise
     */
    bool isFlag() const;

    /**
     * @brief rank
     * @return the rank of the piece
     */
    int rank() const;

    /**
     * @brief operator >
     * @param other
     * @return true if the other pieces rank is smaller than ours, false otherwise
     */
    bool operator> (const CommonPiece & other ) const;

    /**
     * @brief operator <
     * @param other
     * @return true if the other pieces rank is biger than ours, false otherwise
     */
    bool operator< (const CommonPiece & other ) const;

    /**
     * @brief operator == provides a boolean that shows if the pieces have the same rank
     * @param attacker a certain piece
     * @param defender a certain piece
     *  @return true if the pieces have the same rank, false otherwise
     */
    bool operator==(const CommonPiece &defender )const;
};

}
#endif // COMMON_PIECE_H
