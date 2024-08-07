#include "controller.h"
#include "action_result.h"
#include "spy.h"
#include "common_piece.h"

namespace stratego {

void Controller::start() {

    bool from_file = view_.askModeFromFile();
    if(from_file){
        game_.initializeBoardFromFile();
    }
    else {
        view_.showLineEnteringInstructions();
        for(auto row = 0; row <= game_.board().size()/2-2; row++){
            game_.initializeLine(view_.askLine(game_.currentPlayer(), row, game_.board().size()), row);
            view_.displayBoard(game_.board(), game_.currentPlayer());
        }
        for(auto row = game_.board().size()/2+1; row < game_.board().size(); row++){
            game_.initializeLine(view_.askLine(game_.currentPlayer(), row, game_.board().size()), row);
            view_.displayBoard(game_.board(), game_.currentPlayer());
        }
    }
   // ActionResult result;

    view_.displayBoard(game_.board(), game_.currentPlayer());

    while(!game_.isOver()){
        auto pos = view_.choosePiece(game_);
        game_.selectSquare(pos);
        game_.updatePossibleMoves();
        int movement = view_.chooseMovement(game_.possibleMoves());
        game_.move(game_.possibleMoves().at(movement));
    }

}
}
