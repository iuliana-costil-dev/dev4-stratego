#include "board.h"
#include "constants.h"
#include "spy.h"
#include "miner.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Common_piece_factory.h"

using namespace stratego;

Board::Board() {
    board_.resize(size_, std::vector<Square>(size_, Square(false, Position(-1, -1))));
    for (int row=0; row<size_; row++)
    {
        for (int column=0; column<size_; column++)
            if(((row == size_ / 2 - 1) || (row == size_ / 2 ))
                    && (column == size_ / 5 || column == size_ / 5 + 1
                        || column == 3 * size_ / 5 || column == 3 * size_ / 5 +1 ))
                board_[row][column] = Square(false, Position(row, column));
            else{
                board_[row][column] = Square(true, Position(row, column));
            }
    }
}




void Board::assignPieceToPosition(Position& position, std::string& word){
    PlayerColor color;
    if(this->isRedSection(position))
        color=PlayerColor::RED;
    else color = PlayerColor::BLUE;
    try{
        int rank = stoi(word);
        switch(rank){
        case 1:{
            put(create_piece(rank, color, constants::spy_max_squares, "Spy"), position);
            break;}
        case 2: {
            put(create_piece(rank, color, constants::scout_max_squares, "CommonMoveablePiece"), position);
            break;}
        case 3:{
            put(create_piece(rank, color, constants::miner_max_squares, "Miner"), position);
            break;}
        default: {
            put(create_piece(rank, color, 1, "CommonMoveablePiece"), position);}
        }
    }
    catch(std::invalid_argument &) {
        if(word == "B"){
            put(create_piece(constants::bomb_rank, color, 0, "CommonPiece"), position);
        }
        else if(word == "x"){ }
        else if(word == "F"){
            put(create_piece(constants::flag_rank, color,0, "CommonPiece"), position);
        }
        else if(word=="Z"){
            put(create_piece(constants::spy_rank, color, constants::scout_max_squares, "ZebraSpy"), position);
        }
    }

}

bool Board::isInside(Position position) const {
    return position.row()>=0 && position.row() < size_ && position.column() >= 0 && position.column() <size_;
}

Square Board::square(Position position) const {
    if(!this->isInside(position))
        throw std::invalid_argument( "Position is outside of the board.("
                                     + std::to_string(position.row()) + " " + std::to_string(position.column()) + ") ");
    return board_[position.row()][position.column()];
}

bool Board::put(std::shared_ptr<CommonPiece> piece, const Position& position){
    if(!this->isInside(position))
        throw std::invalid_argument( "Position is outside of the board.("
                                     + std::to_string(position.row()) + " " + std::to_string(position.column()) + ") ");
    if(this->isFree(position))
    {
        board_[position.row()][position.column()].putPiece(piece);
        return true;
    } else {
        return false;
    }
}


bool Board::isFree(Position position) const{
    if(!this->isInside(position))
        throw std::invalid_argument( "Position is outside of the board.("
                                     + std::to_string(position.row()) + " " + std::to_string(position.column()) + ") ");
    return board_[position.row()][position.column()].isFree();
}

std::shared_ptr<CommonPiece> Board::piece(Position position) const{
    if(!this->isInside(position))
        throw std::invalid_argument( "Position is outside of the board.("
                                     + std::to_string(position.row()) + " " + std::to_string(position.column()) + ") ");
    return (board_[position.row()][position.column()].piece());
}

void Board::remove(Position position){
    if(!this->isInside(position))
        throw std::invalid_argument( "Position is outside of the board.("
                                     + std::to_string(position.row()) + " " + std::to_string(position.column()) + ") ");
    board_[position.row()][position.column()].removePiece();
}

void Board::move(Position from, Position to){
    if(!this->isInside(to))
        throw std::invalid_argument( "Source osition is outside of the board.("
                                     + std::to_string(from.row()) + " " + std::to_string(to.column()) + ") ");
    if(!this->isInside(to))
        throw std::invalid_argument( "Destination osition is outside of the board.("
                                     + std::to_string(from.row()) + " " + std::to_string(to.column()) + ") ");
    board_[to.row()][to.column()].putPiece(board_[from.row()][from.column()].piece());
    board_[from.row()][from.column()].removePiece();
}

bool Board::isRedSection(Position position) const{
    return (position.row()<= size_ && position.row() >= size_ / 2 + 1);
}

bool Board::isBlueSection(Position position)const {
    return (position.row()>= 0 && position.row() <= size_ / 2 - 2);
}
