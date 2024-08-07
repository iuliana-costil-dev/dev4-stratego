#ifndef COMMON_PIECE_FACTORY_H
#define COMMON_PIECE_FACTORY_H

#include <string>
#include <memory>
#include "common_moveable_piece.h"
#include "common_piece.h"
#include "miner.h"
#include "spy.h"
#include "zebra_spy.h"

namespace stratego {
/**
 * @brief create_piece Create the pointer to the specified CommonPiece type* If the type
 * is unrecognized, throws std::invalid_argument The Piece is allocated with new, so some
 *  other component is resposible for deleting it.
 * @param rank rank of the piece
 * @param color color of the piece
 * @param max_squares maximum step of the piece
 * @param type the type of the piece
 * @return  return the pointer to the specified CommonPiece type
 */
std::shared_ptr<CommonPiece> create_piece(const int rank, const stratego::PlayerColor color, const int max_squares, const std::string &type){
    if (type == "CommonPiece")
    {
       return std::shared_ptr<CommonPiece>(new CommonPiece(rank, color));
    }
    else if (type == "CommonMoveablePiece")
    {
       return std::shared_ptr<CommonPiece>(new CommonMoveablePiece(rank, color, max_squares));
    }
    else if(type=="Spy")
    {
        return std::shared_ptr<CommonPiece>(new Spy(rank, max_squares, color));
    }
    else if(type=="Miner")
    {
        return std::shared_ptr<CommonPiece>(new Miner(rank, max_squares, color));
    }
    else if(type=="ZebraSpy")
    {
        return std::shared_ptr<CommonPiece>(new ZebraSpy(rank, max_squares, color));
    }
    throw std::invalid_argument("Trying to create piece of unknown type!");
}
}
#endif // COMMON_PIECE_FACTORY_H
