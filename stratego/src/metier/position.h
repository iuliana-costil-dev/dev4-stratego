#ifndef POSITION_H
#define POSITION_H

#include <string>
#include "direction.h"
#include <array>
namespace stratego {
/**
* @brief The position class represents a position in the game board.
*/
class Position {
private:
    int row_;
    int column_;

public:
    /**
    * @brief Constructor of Position.
    * @param row of the position
    * @param column of the position
    */
    Position(int row, int column) : row_ {row}, column_{column} {}

    /**
    * @brief Getter of row.
    * @return the position row
    */
    int row() const{ return row_; }

    /**
    * @brief Getter of column.
    * @return the position column
    */
    int column() const{ return column_; }
    /**
     * @brief operator == Defines the equality operator between two positions.
     * @param pos2 a given position
     * @return true if the two position are same, false otherwise.
     */
     bool operator==( const Position &pos2) {
        return this->row_== pos2.row() && this->column_ == pos2.column();
    }

    /**
     * @brief Gives the next Position according to direction.
     * @param posDelta the given position
     */
    inline Position next(Direction direction) const;


    /**
     * @brief operator <<
     * @param Str
     * @param v
     * @return
     */
    friend std::ostream & operator<<(std::ostream & out, Position const & pos) {
        std::array<std::string, 10> columns{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
        out << std::string("( ")
            <<std::to_string(pos.row_)<<std::string(", ")
            <<columns.at(pos.column_)<<std::string(" )");
        return out;
    }
};

/**
 * @brief Position::next provides the Position in the given Direction
 * @param direction
 * @return the next position
 */
Position Position::next(Direction direction) const{
    switch (direction){
        case Direction::DOWN : return  Position(this->row()+1, this->column());
        break;
        case Direction::UP : return  Position(this->row()-1, this->column());
        break;
        case Direction::LEFT : return  Position(this->row(), this->column()-1);
        break;
        case Direction::RIGHT : return  Position(this->row(), this->column()+1);
        break;
    case Direction::UPLEFT : return  Position(this->row()-1, this->column()-1);
    break;
    case Direction::UPRIGHT : return  Position(this->row()-1, this->column()+1);
    break;
    case Direction::DOWNLEFT : return  Position(this->row()+1, this->column()-1);
    break;
    case Direction::DOWNRIGHT : return  Position(this->row()+1, this->column()+1);
    break;
        default: return Position(-1, -1);
        break;
    }
}
}

#endif // POSITION_H
