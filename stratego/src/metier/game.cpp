#include "game.h"
#include "position.h"
#include "constants.h"
#include "direction.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <streambuf>


using namespace stratego;

void Game::removePieceFromPlayer(Player& player, const Position& position){
    player.removePiece(board_.square(position).piece()->rank());
    board_.remove(position);
}


void Game::move(Position position){
    if(state_ != State::IN_PROGRESS) throw std::invalid_argument("You can only do while the game is in progress.");
    bool validPosition = false;
    for (auto & pos2 : possibleMoves_)
    {
        if (pos2 == position)
        {
            validPosition = true;
            break;
        }
    }
    if(!validPosition) throw std::invalid_argument("Position not allowed");

    if(!selectedSquare_->pieceMoves())
        throw std::invalid_argument("Piece does not move");

    if(board_.isFree(position)){
        board_.move(selectedSquare_->position(), position);
        //notify(PROPERTY_BOARD);
         currentResult_=ActionResult::NOBODY_LOST;
         notify(PROPERTY_NEWRESULT);
        swapPlayers();
        notify(PROPERTY_BOARD);
    }else{
        if(*selectedSquare_->piece()==*board_.square(position).piece()){
            removePieceFromPlayer(currentPlayer_, selectedSquare_->position());
            removePieceFromPlayer(opponentPlayer_, position);
            //notify(PROPERTY_BOARD);
            currentResult_=ActionResult::BOTH_LOST;
            notify(PROPERTY_NEWRESULT);
            swapPlayers();
            notify(PROPERTY_BOARD);

        }else{
            if(selectedSquare_->piece()->attackWon(*(board_.square(position).piece()))){
                if(board_.square(position).piece()->isFlag()){
                    removePieceFromPlayer(opponentPlayer_, position);
                    board_.move(selectedSquare_->position(),position);
                    //notify(PROPERTY_BOARD);
                    this->state_=State::END;
                    currentResult_=ActionResult::CURRENT_LOST;
                    notify(PROPERTY_NEWRESULT);
                    swapPlayers();
                    notify(PROPERTY_BOARD);

                }else{
                    removePieceFromPlayer(opponentPlayer_, position);
                    board_.move(selectedSquare_->position(),position);
                    //notify(PROPERTY_BOARD);
                    currentResult_=ActionResult::CURRENT_LOST;
                    notify(PROPERTY_NEWRESULT);
                    swapPlayers();
                    notify(PROPERTY_BOARD);          
                }
            }else{
                removePieceFromPlayer(currentPlayer_, selectedSquare_->position());
                //notify(PROPERTY_BOARD);
                currentResult_=ActionResult::OPPONENT_LOST;
                notify(PROPERTY_NEWRESULT);
                swapPlayers();
                notify(PROPERTY_BOARD);
            }
        }
    }
}

Game::Game() :
    currentPlayer_(PlayerColor::BLUE),
    opponentPlayer_(PlayerColor::RED),
    state_(State::NOT_STARTED)
{ }


void Game::initializeBoardFromFile(){
    if(state_ != State::NOT_STARTED) throw std::invalid_argument("You can only do this before the game starts.");
    std::ifstream file_blue;
    file_blue.open("../../../stratego/src/console/placement_blue.txt");
    std::string str_blue((std::istreambuf_iterator<char>(file_blue)),
                         std::istreambuf_iterator<char>());
    std::ifstream file_red;
    file_red.open("../../../stratego/src/console/placement_red.txt");
    std::string str_red((std::istreambuf_iterator<char>(file_red)),
                        std::istreambuf_iterator<char>());
    file_blue.close();
    file_red.close();

    int row = 0;
    int column=0;
    std::string word;
    for ( std::istringstream is( str_blue ); is >> word; )
    {
        Position position(row, column);
        board_.assignPieceToPosition(position, word);
        column++;
        if(column == board_.size() )
        {
            row++;
            column=0;
        }
    }
    row = board_.size() - 1;
    column=0;
    for ( std::istringstream is( str_red ); is >> word; )
    {
        Position position(row, column);
        board_.assignPieceToPosition(position, word);
        column++;
        if(column == board_.size())
        {
            row--;
            column=0;
        }
    }
    state_ = State::IN_PROGRESS;
}

void Game::initializeLine(const std::string& line, int row){
    if(state_ != State::NOT_STARTED) throw std::invalid_argument("You can only do this before the game starts.");
    int column=0;
    std::string word;
    for ( std::istringstream is( line ); is >> word; )
    {
        Position position(row, column);
        board_.assignPieceToPosition(position, word);
        column++;
        if(column == board_.size() )
            column=0;
    }

    if(row == board_.size()-1){
        state_ = State::IN_PROGRESS;
        swapPlayers();
    }
    if(row == board_.size()/2-2)
        swapPlayers();
}


bool Game::isOver(){
    //the game ended previously by capturing a flag
    if(state_==State::END)
    {
        notify(PROPERTY_ENDGAME);
        return true;
    }
    //the player doesn't have any moves
    for(int i =0; i< board_.size();i++){
        for(int j=0;j<board_.size();j++){
            Position pos = Position(i,j);
            if(board_.isInside(pos)&&!board_.isFree(pos)
                    &&board_.matchesColor(pos,currentPlayer_.color())
                    &&board_.square(pos).pieceMoves()){
                if((getPossibleMovesForPiece(pos)).size()>0){
                    return false;
                }
            }
        }
    }
    state_ = State::END;
    notify(PROPERTY_ENDGAME);
    return true;
}

void Game::selectSquare(const Position& position){
    if(state_ != State::IN_PROGRESS) throw std::invalid_argument("Game is not in progress.");
    if(canSelect(position)){
        selectedSquare_.reset();
        selectedSquare_ = std::make_unique<Square>(board_.square(position));
    }
}
bool Game::canSelect(const Position& position) const {
    return board_.isInside(position)
            && board_.square(position).isLand()
            && !board_.isFree(position)
            && board_.matchesColor(position, currentPlayer_.color())
            && board_.square(position).pieceMoves();
}

Square Game::selectedSquare(){
    return *selectedSquare_;
}
std::vector<Position> Game::getPossibleMovesForPiece(const Position &position) const{
    std::vector<Position> possibleMoves;
    possibleMoves=findPossibleMovesInDirection(board_.piece(position)->max_squares(), position.next(Direction::UP), Direction::UP, possibleMoves);
    possibleMoves=findPossibleMovesInDirection(board_.piece(position)->max_squares(), position.next(Direction::DOWN), Direction::DOWN, possibleMoves);
    possibleMoves=findPossibleMovesInDirection(board_.piece(position)->max_squares(), position.next(Direction::LEFT), Direction::LEFT, possibleMoves);
    possibleMoves=findPossibleMovesInDirection(board_.piece(position)->max_squares(), position.next(Direction::RIGHT), Direction::RIGHT, possibleMoves);
    return possibleMoves;

}
void Game::updatePossibleMoves(){
    if(state_ != State::IN_PROGRESS) throw std::invalid_argument("Game is not in progress.");
    possibleMoves_= getPossibleMovesForPiece(selectedSquare_->position());
}

std::vector<Position> Game::findPossibleMovesInDirection(int max_squares, const Position& pos, Direction dir,  std::vector<Position> &possibleMoves) const{
    if(max_squares != 0){
        if(board_.isInside(pos)&&board_.square(pos).isLand()){
            if(!board_.square(pos).isFree()&&board_.matchesColor(pos,opponentPlayer_.color()))
                possibleMoves.push_back(pos);
            else if(board_.square(pos).isFree()){
                possibleMoves.push_back(pos);
                findPossibleMovesInDirection(max_squares-1, pos.next(dir), dir, possibleMoves);
            }
        }
    }
    return possibleMoves;
}

bool Game::putPiece(std::shared_ptr<CommonPiece> piece, const Position& position){
    if(state_ != State::NOT_STARTED) throw std::invalid_argument("You can only do this before the game starts.");
    if(!board_.isInside(position))
        throw std::invalid_argument( "Position is outside of the board.("
                                     + std::to_string(position.row()) + " " + std::to_string(position.column()) + ") ");
    if(board_.isFree(position))
    {
        board_.put(piece, position);
        return true;
    } else {
        return false;
    }
}
