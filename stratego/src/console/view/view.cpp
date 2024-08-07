#include "view.h"
#include "constants.h"
#include "libs/consoleColor.h"
#include <array>
#include <regex>
#include <iostream>
#include <iomanip>

using namespace std;
namespace stratego {

void View::showLineEnteringInstructions(){
    cout<<"Enter 10 pieces in a line. "<<endl;
    cout<<"You can use : F (flag), 1 (Marshall), 2 (Scout), 3 (Miner),..., B(bomb)"<<endl;
    cout<<"ex: 1 2 3 4 5 6 7 8 9 F"<<endl;
}

void View::displayResult(const ActionResult& result,const Player& current, const Player& opponent){
    if(result == ActionResult::BOTH_LOST){
        cout<<"Both of your pieces are the same rank! You both lost!"<<endl;
    } else {
        std::string color_current = (current.color() == PlayerColor::BLUE)?"BLUE":"RED";
        std::string color_opponent = (opponent.color() == PlayerColor::BLUE)?"BLUE":"RED";
        if(result == ActionResult::CURRENT_LOST){
            cout<<color_current<<" player captured a piece from the "<<color_opponent<<" player."<<endl;
        } else if(result == ActionResult::OPPONENT_LOST){
            cout<<color_opponent<<" player captured a piece from the "<<color_current<<" player."<<endl;
        }
    }
}

void View::displayBoard(const Board &board, const Player &player) {
    cout<<"Board of the " <<
          ((player.color()==PlayerColor::BLUE)?"blue":"red")
       <<" player"<<endl;
    std::array<string, 10> columns{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    cout <<" ";
    for (auto col = 0; col < board.size(); col++)
        cout <<setfill(' ') << std::setw(3)<<columns[col];
    cout<< endl;
    for (auto row = 0; row < board.size(); row++) {
        cout << row;
        for (auto col = 0; col < board.size(); col++) {
            auto pos = Position(row, col);
            if(!board.square(pos).isLand()){
                cout<<setfill(' ') << std::setw(3)<<"-"<<reset;
            }
            else{
                if(board.square(pos).isFree())
                {
                    cout<<"   ";
                } else
                {
                    string show="X";
                    if(board.piece(pos)->rank()==stratego::constants::flag_rank){
                        if(board.matchesColor(pos, player.color()))
                            show="F";
                        if(board.piece(pos)->color() == PlayerColor::BLUE)
                            cout<<blue<<setfill(' ') << std::setw(3)<<show<<reset;
                        else cout<<red<<setfill(' ') << std::setw(3)<<show<<reset;
                    }
                    else if(board.piece(pos)->rank()==stratego::constants::bomb_rank){
                        if(board.matchesColor(pos, player.color()))
                            show="B";
                        if(board.piece(pos)->color() == PlayerColor::BLUE)
                            cout<<blue<<setfill(' ') << std::setw(3)<<show<<reset;
                        else cout<<red<<setfill(' ') << std::setw(3)<<show<<reset;
                    } else {
                        if(board.matchesColor(pos, player.color()))
                            show=std::to_string(board.piece(pos)->rank());
                        if(board.piece(Position(row, col))->color() == PlayerColor::BLUE)
                            cout<<blue<<setfill(' ') << std::setw(3)<<show<<reset;
                        else cout<<red<<setfill(' ') << std::setw(3)<<show<<reset;
                    }
                }
            }
        }
        cout<<endl;
    }
}

int View::chooseMovement(const std::vector<Position> &possibleMoves) {
    size_t position;
    std::cout << "These are the available movements: "<<endl;
    for(size_t it = 0; it < possibleMoves.size();it++)
        cout<<it<<". " << possibleMoves.at(it)<<endl;

    do {
        cout<<"Type the number of the movement to chose."<<endl;
        cin >> position;
    } while (position>=possibleMoves.size());
    return position;
}

Position View::choosePiece(const Model &game) {
    std::vector<std::string> columns{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    size_t row;
    size_t column;
    string line;

    bool success_conversion = true;
    bool valid_piece = true;
    bool piece_has_moves = true;

    Position position(-1, -1);
    do {
        if(valid_piece == false)
            cerr<<"Invalid piece. "<<endl;
        if(piece_has_moves == false)
            cerr<<"There are no possible moves for this piece. "<<endl;

        success_conversion = true;
        valid_piece = true;
        piece_has_moves = true;

        if(game.currentPlayer().color()==PlayerColor::BLUE)
            cout<<blue<<"BLUE, please choose a piece (ex 1A): "<<reset;
        else cout<<red<<"RED, please choose a piece (ex 1A): "<<reset;
        cin >> line;
        try {
            //convert first char in line to int
            string s(1,line[0]);
            row = std::stoi(s);
        }
        catch (...) {
            //conversion failed
            success_conversion = false;
            cerr<<line[0]<<" is not a valid row. "<<endl;
        }
        //if the row is found, go ahead and find the col
        if(success_conversion){
            string s(1,line[1]);
            //is the letter eneter as a column inside available columns?
            vector<string>::iterator itr = find(columns.begin(), columns.end(), s);
            if(itr != end(columns)){
                //letter is inside, find at what index, that is the col
                column=distance(columns.begin(), itr);
            }else{
                //letter does not represent a column
                success_conversion= false;
                cerr<<line[1]<<" is not a valid column. "<<endl;
            }
            position=Position(row, column);
            if(success_conversion){
                valid_piece = game.canSelect(position);
                if(valid_piece)
                    piece_has_moves = game.getPossibleMovesForPiece(position).size()!=0;
            }
        }
    } while (!success_conversion || !valid_piece || !piece_has_moves);
    return position;
}

void View::displayEnd(const Player &winner) {
    cout<<"Good job player "
       <<((winner.color()==PlayerColor::BLUE)?"blue":"red")
      <<", you won!"<<endl;
}

bool View::askModeFromFile(){
    std::string decision;
    do {
        cout<<"Type yes/no if you want/don't want to fill your board from the file."<<endl;
        cin >> decision;
    } while (decision!="yes" && decision!="no");
    return decision == "yes";
}


std::string View::askLine(const Player& player, int row, unsigned long long required_number){
    std::string line;
    unsigned long long number;
    bool invalid_number = false;
    do {
        if(invalid_number) cerr<<"Required number of pieces: "<<required_number<<", you entered "<<number<<endl;
        if(player.color()==PlayerColor::BLUE)
            cout<<blue<<"BLUE, please enter pieces at row "<<row<<": "<<reset;
        else cout<<red<<"RED, please enter pieces at row : "<<row<<": "<<reset;
        std::getline(std::cin >> std::ws, line);
        std::stringstream stream(line);
        number = std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
        if(number != required_number) invalid_number = true;
    } while (number!=required_number);
    return line;
}

void View::update(const std::string &message) {
    if (message == model_.PROPERTY_BOARD) {
        displayBoard(model_.board(), model_.currentPlayer());
    }

    if (message == model_.PROPERTY_ENDGAME) {
        displayEnd(model_.opponentPlayer());
    }
    if (message == model_.PROPERTY_NEWRESULT) {
       displayResult(model_.currentResult(),model_.currentPlayer(),model_.opponentPlayer());
    }
}
}
