#include <catch.hpp>
#include "board.h"
#include "direction.h"
#include "position.h"
#include "constants.h"
#include "spy.h"
#include "common_moveable_piece.h"
#include "miner.h"
#include <iostream>
#include <memory>
#define private public
#include "game.h"
#undef private


TEST_CASE("test metier", "[metier]")
{
    using namespace stratego;
    //POSITION
    SECTION("PositionNext(UP)") {
        Position pos= Position(2,3);
        Position nextUp= pos.next(Direction::UP);
        Position excepted = Position(1,3);
        auto result = nextUp == excepted;  // Invokes my overloaded comparison operator
        REQUIRE(result);
    }
    SECTION("PositionNext(RIGHT)") {
        Position pos= Position(2,3);
        Position nextRight= pos.next(Direction::RIGHT);
        Position excepted = Position(2,4);
        auto result = nextRight == excepted;  // Invokes my overloaded comparison operator
        REQUIRE(result);
    }
    SECTION("PositionNext(LEFT)") {
        Position pos= Position(2,3);
        Position nextLeft= pos.next(Direction::LEFT);
        Position excepted = Position(2,2);
        auto result = nextLeft == excepted;  // Invokes my overloaded comparison operator
        REQUIRE(result);
    }
    SECTION("PositionNext(DOWN)") {
        Position pos= Position(2,3);
        Position nextDown= pos.next(Direction::DOWN);
        Position excepted = Position(3,3);
        auto result = nextDown == excepted;  // Invokes my overloaded comparison operator
        REQUIRE(result);
        REQUIRE(nextDown.row()== excepted.row() );
        REQUIRE(nextDown.column()==excepted.column());
    }

    SECTION("Position == operator false") {
        Position pos= Position(2,3);
        Position other = Position(3,3);
        auto result = pos == other;  // Invokes my overloaded comparison operator
        //REQUIRE(result==false);
        REQUIRE_FALSE( result );
    }
    SECTION("Position == operator true") {
        Position pos= Position(3,3);
        Position other = Position(3,3);
        auto result = pos == other;  // Invokes my overloaded comparison operator
        REQUIRE(result);
    }


    //SQUARE
    SECTION("Square piecesMove method true ") {
        Square square = Square(true, Position(0,0));
        square.putPiece(std::shared_ptr<CommonPiece>(new CommonMoveablePiece(3,  PlayerColor::BLUE,9)));//a scout
        bool pieceMoves= square.pieceMoves();

        REQUIRE(pieceMoves);

    }

    SECTION("Square piecesMove method false ") {
        Square square = Square(true, Position(0,0));
        square.putPiece(std::shared_ptr<CommonPiece>(new CommonPiece( constants::bomb_rank, PlayerColor::BLUE)));//a bomb
        bool pieceMoves= square.pieceMoves();

        REQUIRE_FALSE(pieceMoves);

    }


    SECTION("Square putPiece method ") {
        Square square = Square(true, Position(0,0));
        std::shared_ptr<CommonPiece>cm(new CommonPiece ( constants::bomb_rank, PlayerColor::BLUE));
        square.putPiece(cm);//a bomb
        REQUIRE(cm==square.piece());
    }

    SECTION("Square remove method ") {
        Square square = Square(true, Position(0,0));
        std::shared_ptr<CommonPiece>cm(new CommonPiece ( constants::bomb_rank, PlayerColor::BLUE));
        square.putPiece(cm);//a bomb
        square.removePiece();

        REQUIRE(square.isFree());
    }

    SECTION("Square isLand method true") {
        Square square = Square(true, Position(0,0));
        bool isLand= square.isLand();
        REQUIRE(isLand);
    }


    SECTION("Square isLand method false") {
        Square square = Square(false, Position(4,3));
        bool isLand= square.isLand();
        REQUIRE_FALSE(isLand);
    }

    SECTION("Square isFree method true") {
        Square square = Square(true, Position(0,0));
        std::shared_ptr<CommonPiece>cm(new CommonMoveablePiece(constants::scout_rank,  PlayerColor::BLUE,9));//a scout
        square.putPiece(cm);
        REQUIRE_FALSE(square.isFree());
    }
    SECTION("Square isFree method false") {
        Square square = Square(true, Position(2,5));
        REQUIRE(square.isFree());
    }

    // PIECE

    SECTION("isFlag false"){
        CommonMoveablePiece marshall =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        REQUIRE_FALSE(marshall.isFlag());
    }


    SECTION("isFlag true"){
        CommonPiece flag = CommonPiece(constants::flag_rank,  PlayerColor::BLUE);//a Flag
        REQUIRE(flag.isFlag());
    }

    SECTION("Common Piece == operator false") {
        Spy piece = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonMoveablePiece other =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        auto result = piece == other;  // Invokes my overloaded comparison operator
        REQUIRE_FALSE(result);
    }
    SECTION("Common Piece == operator true") {
        Spy piece = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        Spy other = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::BLUE);
        auto result = piece == other;  // Invokes my overloaded comparison operator
        REQUIRE(result);
    }
    SECTION("Common Piece > operator false") {
        Spy piece = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonMoveablePiece other =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        auto result = piece > other;  // Invokes my overloaded > operator
        REQUIRE_FALSE(result);
    }
    SECTION("Common Piece < operator true") {
        Spy piece = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonMoveablePiece other =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        auto result = piece < other;  // Invokes my overloaded < operator
        REQUIRE(result);
    }


    SECTION("Common Piece sameColor method false") {
        Spy piece = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonMoveablePiece other =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        REQUIRE_FALSE(piece.sameColor(other));
    }
    SECTION("Common Piece sameColor method true") {
        Spy piece = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonMoveablePiece other =CommonMoveablePiece(constants::marshall_rank, PlayerColor::RED, constants::marshall_max_squares);
        REQUIRE(piece.sameColor(other));
    }




    //ATTACKWON PIECES

    SECTION("Spy attackWon method spy attack marshall") {
        Spy spy = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonMoveablePiece marshall =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        REQUIRE(spy.attackWon(marshall));
    }


    SECTION("CommonMoveable attackWon method marshall attack spy ") {
        CommonMoveablePiece marshall =CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares);
        Spy spy = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        REQUIRE(marshall.attackWon(spy));
    }


    SECTION("Miner attackWon miner attack bomb ") {
        Miner miner =Miner(constants::miner_rank, constants::miner_max_squares,PlayerColor::BLUE);
        CommonPiece bomb = CommonPiece(constants::bomb_rank,  PlayerColor::RED);//a bomb
        REQUIRE(miner.attackWon(bomb));
    }


    SECTION("CommonMoveable piece attackWon not a Miner attack bomb ") {
        CommonMoveablePiece lieutenant =  CommonMoveablePiece(constants::lieutenant_rank,PlayerColor::RED, constants::lieutenant_max_squares);
        CommonPiece bomb = CommonPiece(constants::bomb_rank,  PlayerColor::BLUE);//a bomb
        REQUIRE_FALSE(lieutenant.attackWon(bomb));
    }

    SECTION("Spy piece attackWon spy attack bomb ") {
        Spy spy = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        CommonPiece bomb = CommonPiece(constants::bomb_rank,  PlayerColor::BLUE);//a bomb
        REQUIRE_FALSE(spy.attackWon(bomb));
    }

    SECTION("CommonMoveable attackWon attack same rank") {
        CommonMoveablePiece scout = CommonMoveablePiece(constants::scout_rank,  PlayerColor::BLUE,constants::scout_max_squares);
        CommonMoveablePiece scout2 = CommonMoveablePiece(constants::scout_rank,  PlayerColor::BLUE,constants::scout_max_squares);
        REQUIRE_FALSE(scout.attackWon(scout2));
    }

    SECTION("Spy attackWon Spy attack Spy (same rank) ") {
        Spy spy = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        Spy spy2 = Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED);
        REQUIRE_FALSE(spy.attackWon(spy2));
    }

    SECTION("Miner attackWon Miner attack Miner") {
        Miner miner = Miner(constants::miner_rank, constants::miner_max_squares, PlayerColor::RED);
        Miner miner2 = Miner(constants::miner_rank, constants::miner_max_squares, PlayerColor::RED);
        REQUIRE_FALSE(miner.attackWon(miner2));
    }

    //BOARD


    SECTION("BOARD IsInside method true") {
        Board board;
        bool isInside=board.isInside(Position(0,0));
        REQUIRE(isInside);
    }
    SECTION("BOARD IsInside method false") {
        Board board;
        bool isInside=board.isInside(Position(10,3));
        REQUIRE_FALSE(isInside);
    }
    SECTION("BOARD isFree method false") {
        Board board;
        Position pos(0,0);
        std::string word = "1";
        board.assignPieceToPosition(pos,word);//a spy
        bool isFree= board.isFree(pos);
        REQUIRE_FALSE(isFree);
    }
    SECTION("BOARD isFree method true") {
        Board board;
        Position pos(0,0);
        bool isFree= board.isFree(pos);
        REQUIRE(isFree);
    }

    SECTION("BOARD assignPieceToPosition method ") {
        Board board;
        Position pos(0,0);
        std::string word = "1";
        board.assignPieceToPosition(pos,word);//a spy
        bool isFree= board.isFree(pos);
        REQUIRE_FALSE(isFree);
        REQUIRE(board.piece(pos)->rank()==constants::spy_rank);
    }

    SECTION("BOARD isRedSection method true ") {
        Board board;
        Position pos(9,0);
        bool isRedSection= board.isRedSection(pos);
        REQUIRE(isRedSection);
    }
    SECTION("BOARD isRedSection method false ") {
        Board board;
        Position pos(0,0);
        bool isRedSection= board.isRedSection(pos);
        REQUIRE_FALSE(isRedSection);
    }


    SECTION("BOARD isBlueSection method true ") {
        Board board;
        Position pos(0,0);
        bool isBlueSection= board.isBlueSection(pos);
        REQUIRE(isBlueSection);
    }
    SECTION("BOARD isBlueSection method false ") {
        Board board;
        Position pos(9,0);
        bool isBlueSection= board.isBlueSection(pos);
        REQUIRE_FALSE(isBlueSection);
    }

    SECTION("BOARD matchesColor method false ") {
        Board board;
        Position pos(9,0);
        std::string word = "3";
        board.assignPieceToPosition(pos,word);
        bool matchesColor= board.matchesColor(Position(9,0),PlayerColor::BLUE);
        REQUIRE_FALSE(matchesColor);

    }
    SECTION("BOARD matchesColor method true ") {
        Board board;
        Position pos(9,0);
        std::string word = "3";
        board.assignPieceToPosition(pos,word);
        bool matchesColor= board.matchesColor(Position(9,0),PlayerColor::RED);
        REQUIRE(matchesColor);

    }
    SECTION("BOARD move method") {
        Board board;
        Position start(9,0);
        Position end(9,1);
        std::string word = "3";
        board.assignPieceToPosition(start,word);
        board.move(start,end);
        bool baseFree=board.square(start).isFree();
        bool endOccupied= board.square(end).piece()->rank()==3;
        REQUIRE(baseFree);
        REQUIRE(endOccupied);
    }

    SECTION("BOARD isInside method false") {
        Board board;
        Position pos(-5,-6);
        bool isInside= board.isInside(pos);
        REQUIRE_FALSE(isInside);
    }

    SECTION("BOARD isInside method true") {
        Board board;
        Position pos(5,8);
        bool isInside= board.isInside(pos);
        REQUIRE(isInside);
    }



    //GAME all moves works but security not allow us to add a piece when game already started ,
    //we can only put piece at the begining. Red piece in the redScetion and Blue piece in the bluesection.
    //so we comment all tests because it's impossible to put piece RED and Blue in the same colorsection


    SECTION("Game isOver Method only bomb left true") {
        Game game{};

        Position start(0, 0);
        game.putPiece(std::shared_ptr<CommonPiece>(new Spy(1, 1, PlayerColor::BLUE)),start);//a spy
        Position end(0, 1);
        game.putPiece(std::shared_ptr<CommonPiece>(new CommonPiece(constants::bomb_rank, PlayerColor::RED)),end);//a Bomb

        game.state(State::IN_PROGRESS);
        game.selectSquare(start);
        game.updatePossibleMoves();
        game.move(end);
        bool isOver= game.isOver();
        REQUIRE(isOver);
    }
    SECTION("Game isOver Method a scout left false") {
        Game game{};
        Position end(0, 1);
        game.putPiece(std::shared_ptr<CommonPiece>(new CommonMoveablePiece(constants::scout_rank, PlayerColor::BLUE,constants::scout_max_squares)),end);//a a scout
        game.state(State::IN_PROGRESS);
        bool isOver= game.isOver();
        REQUIRE_FALSE(isOver);
    }

    SECTION("test of move SPY attack Marshall") {

        Game game{};
        Position start(0, 0);
        game.putPiece(std::shared_ptr<CommonPiece>(new Spy(1, 1, PlayerColor::BLUE)),start);//a spy

        Position end(0, 1);
        game.putPiece( std::shared_ptr<CommonPiece>(new CommonMoveablePiece(10,  PlayerColor::RED,1)),end);//a marshall
        game.state(State::IN_PROGRESS);
        game.selectSquare(start);
        game.updatePossibleMoves();

        game.move(end);
        bool resultBase = game.board().square(start).isFree();
        bool resultArrived = game.board().square(end).piece().get()->rank()==1;

        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }

    SECTION("test of move Marshall attack SPY") {
        Game game = Game{};

        std::shared_ptr<CommonPiece> pieceToMove (new CommonMoveablePiece(constants::marshall_rank, PlayerColor::BLUE, constants::marshall_max_squares));
        game.putPiece(pieceToMove, Position(1,2));
        std::shared_ptr<CommonPiece> pieceToAttack (new Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED));


        game.putPiece(pieceToAttack, Position(1,3));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(1,2));
        game.updatePossibleMoves();
        game.move(Position(1,3));

        bool resultBase = game.board().square(Position(1,2)).isFree();
        bool resultArrived = game.board().square(Position(1,3)).piece()->rank()==constants::marshall_rank;
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }


    SECTION("test of move miner attack Bomb") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new Miner(constants::miner_rank, constants::miner_max_squares,PlayerColor::BLUE));
        game.putPiece(pieceToMove,Position(7,5));
        std::shared_ptr<CommonPiece> pieceToAttack (new  CommonPiece(constants::bomb_rank,  PlayerColor::RED));//a bomb
        game.putPiece(pieceToAttack,Position(8,5));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(7,5));
        game.updatePossibleMoves();
        game.move(Position(8,5));
        bool resultBase = game.board().square(Position(7,5)).isFree();
        bool resultArrived = game.board().square(Position(8,5)).piece()->rank()==constants::miner_rank;
        REQUIRE(resultBase);
        REQUIRE(resultArrived);
    }

    SECTION("test of move piece that is not miner(lieutenant) attack Bomb") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new CommonMoveablePiece(constants::lieutenant_rank,PlayerColor::BLUE, constants::lieutenant_max_squares));
        game.putPiece(pieceToMove,Position(9,2));
        std::shared_ptr<CommonPiece> pieceToAttack (new CommonPiece(constants::bomb_rank, PlayerColor::RED));//a bomb
        game.putPiece(pieceToAttack,Position(9,3));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(9,2));
        game.updatePossibleMoves();
        game.move(Position(9,3));
        bool resultBase = game.board().square(Position(9,2)).isFree();
        bool resultArrived = game.board().square(Position(9,3)).piece()->rank()==constants::bomb_rank;
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }
    SECTION("test of move piece that have the same rank that the opponent piece") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new CommonMoveablePiece(constants::captain_rank,  PlayerColor::BLUE,constants::captain_max_squares));
        game.putPiece(pieceToMove,Position(4,4));
        std::shared_ptr<CommonPiece> pieceToAttack(new  CommonMoveablePiece(constants::captain_rank,  PlayerColor::RED,constants::captain_max_squares));
        game.putPiece(pieceToAttack,Position(5,4));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(4,4));
        game.updatePossibleMoves();
        game.move(Position(5,4));
        bool resultBase = game.board().square(Position(4,4)).isFree();
        bool resultArrived = game.board().square(Position(5,4)).isFree();
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }

    SECTION("test of move piece that have the same rank that the opponent piece 2") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new  CommonMoveablePiece(constants::sergeant_rank,  PlayerColor::BLUE,constants::sergeant_max_squares));
        game.putPiece(pieceToMove,Position(4,4));
        std::shared_ptr<CommonPiece> pieceToAttack (new CommonMoveablePiece(constants::sergeant_rank,  PlayerColor::RED,constants::sergeant_max_squares));
        game.putPiece(pieceToAttack,Position(5,4));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(4,4));
        game.updatePossibleMoves();
        game.move(Position(5,4));
        bool resultBase = game.board().square(Position(4,4)).isFree();
        bool resultArrived = game.board().square(Position(5,4)).isFree();
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }
    SECTION("test of move piece that have the same rank that the opponent piece 3") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::BLUE));
        game.putPiece(pieceToMove,Position(0,0));
        std::shared_ptr<CommonPiece> pieceToAttack (new  Spy(constants::spy_rank, constants::spy_max_squares, PlayerColor::RED));
        game.putPiece(pieceToAttack,Position(0,1));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(0,0));
        game.updatePossibleMoves();
        game.move(Position(0,1));
        bool resultBase = game.board().square(Position(0,0)).isFree();
        bool resultArrived = game.board().square(Position(0,1)).isFree();
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }



    SECTION("test of move of Scout ") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new CommonMoveablePiece(constants::scout_rank,  PlayerColor::BLUE,constants::scout_max_squares));
        game.putPiece(pieceToMove,Position(0,0));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(0,0));
        game.updatePossibleMoves();
        game.move(Position(0,9));
        bool resultBase = game.board().square(Position(0,0)).isFree();
        bool resultArrived = game.board().square(Position(0,9)).piece()->rank()==constants::scout_rank;
        REQUIRE(resultBase);
        REQUIRE(resultArrived);
    }



    SECTION("test of move attack bigger rank") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new  CommonMoveablePiece(constants::lieutenant_rank,  PlayerColor::BLUE,constants::lieutenant_max_squares));
        game.putPiece(pieceToMove,Position(9,2));
        std::shared_ptr<CommonPiece> pieceToAttack (new  CommonMoveablePiece(constants::marshall_rank,  PlayerColor::RED,constants::marshall_max_squares));
        game.putPiece(pieceToAttack,Position(9,3));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(9,2));
        game.updatePossibleMoves();
        game.move(Position(9,3));
        bool resultBase = game.board().square(Position(9,2)).isFree();
        bool resultArrived = game.board().square(Position(9,3)).piece()->rank()==constants::marshall_rank;
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }



    SECTION("test of move attack lower rank") {
        Game game = Game{};
        std::shared_ptr<CommonPiece> pieceToMove (new  CommonMoveablePiece(constants::marshall_rank,  PlayerColor::BLUE,constants::marshall_max_squares));
        game.putPiece(pieceToMove,Position(9,2));
        std::shared_ptr<CommonPiece> pieceToAttack (new CommonMoveablePiece(constants::lieutenant_rank,  PlayerColor::RED,constants::lieutenant_max_squares));
        game.putPiece(pieceToAttack,Position(9,3));
        game.state(State::IN_PROGRESS);
        game.selectSquare(Position(9,2));
        game.updatePossibleMoves();
        game.move(Position(9,3));
        bool resultBase = game.board().square(Position(9,2)).isFree();
        bool resultArrived = game.board().square(Position(9,3)).piece()->rank()==constants::marshall_rank;
        REQUIRE(resultBase);
        REQUIRE(resultArrived);

    }

}
