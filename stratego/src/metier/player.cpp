#include "player.h"
#include "spy.h"
#include "miner.h"
#include "constants.h"
#include "zebra_spy.h"
using namespace stratego;

void Player::removePiece(int rank){
    auto position = std::find_if(pieces_.begin(), pieces_.end(),[rank] (const CommonPiece& p) { return p.rank() == rank; });
    pieces_.erase(position);
}

Player::Player(PlayerColor color) : color_{color}{
    for(int count = 0; count < constants::nb_flags; count ++){
        pieces_.push_back(CommonPiece(constants::flag_rank, color_));
    }
    for(int count = 0; count < constants::nb_spies; count ++){
        pieces_.push_back(Spy(constants::spy_rank, constants::spy_max_squares, color_));
    }
    for(int count = 0; count < constants::nb_marshalls; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::marshall_rank,
                                              color_,
                                              constants::marshall_max_squares));
    }
    for(int count = 0; count < constants::nb_generals; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::general_rank,
                                              color_,
                                              constants::general_max_squares));
    }
    for(int count = 0; count < constants::nb_colonels; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::colonel_rank,
                                              color_,
                                              constants::colonel_max_squares));
    }
    for(int count = 0; count < constants::nb_majors; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::major_rank,
                                              color_,
                                              constants::major_max_squares));
    }
    for(int count = 0; count < constants::nb_captains; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::captain_rank,
                                              color_,
                                              constants::captain_max_squares));
    }
    for(int count = 0; count < constants::nb_lieutenants; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::lieutenant_rank,
                                              color_,
                                              constants::lieutenant_max_squares));
    }
    for(int count = 0; count < constants::nb_sergeants; count ++){
        pieces_.push_back(CommonMoveablePiece(constants::sergeant_rank,
                                              color_,
                                              constants::sergeant_max_squares));
    }
    for(int count = 0; count < constants::nb_miners; count ++){
        pieces_.push_back(Miner(constants::miner_rank,
                                constants::miner_max_squares,
                                color_));
    }
    for(int count = 0; count < constants::nb_scouts; count ++){
        pieces_.push_back(ZebraSpy(constants::spy_rank,
                                        constants::scout_max_squares,
                                        color_));
    }
    for(int count = 0; count < constants::nb_bombs; count ++){
        pieces_.push_back(CommonPiece(constants::bomb_rank, color_));
    }
}
