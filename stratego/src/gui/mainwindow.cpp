#include "MainWindow.h"
#include "PieceButton.h"
#include "ui_MainWindow.h"
#include <QString>
#include <QSignalMapper>
#include <QDebug>
#include <QTime>
#include <QMessageBox>
using namespace stratego;

MainWindow::MainWindow(Model& game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model_{game},
    board_buttons_{}
{
    clicked_count_=0;
    game.addObserver(this);
    ui->setupUi(this);
    ui->boardUI->setVisible(false);
    ui->menu_right->setVisible(false);
    ui->boardSETUP->setVisible(false);
    ui->boardUI->setStyleSheet("QFrame {border-image: url(:/new/prefix1/images/boardbackground.jpg) 0 0 0 0 stretch stretch; }");
    ui->boardSETUP->setStyleSheet("QFrame {border-image: url(:/new/prefix1/images/boardbackground.jpg) 0 0 0 0 stretch stretch; }");
    signalMapper = new QSignalMapper();
    signalMapperSETUP = new QSignalMapper();
    connect (signalMapper, SIGNAL(mappedString(QString)), this, SLOT(pieceButtonHandler(QString)));
    connect (signalMapperSETUP, SIGNAL(mappedString(QString)), this, SLOT(pieceSetupButtonHandler(QString)));
    connect (ui->start_blue, SIGNAL(clicked()), this, SLOT(startBlueButtonHandler()));
    connect (ui->start_red, SIGNAL(clicked()), this, SLOT(startRedButtonHandler()));
    startGame();
    //ui->timer->setStyleSheet("border: 3px solid blue; border-radius: 10px;");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::startGame()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Using file"),
                                                  tr("Would you like to use the file for initializing your boards?")))
    {
        ui->boardUI->setVisible(true);
        ui->menu_right->setVisible(true);
        ui->start_blue->setVisible(false);
        ui->start_red->setVisible(false);
        model_.initializeBoardFromFile();
        createBoard();
    }
    else {
        ui->boardSETUP->setVisible(true);
        ui->menu_right->setVisible(true);
        setupBoardBlue();
    }
}

void MainWindow::createBoard()
{
    ui->turn_blue->setText("YOUR TURN");
    stratego::Board game_board = model_.board();
    ui->info_panel_blue->setText("The game starts now!");
    ui->info_panel_red->setText("The game starts now!");
    for(int row = 0; row<game_board.size();row++){
        std::vector<PieceButton *> row_buttons {};
        for(int column = 0; column<game_board.size();column++){
            PieceButton * btn = new PieceButton(row, column, model_, this);

            QString pos_string = QString::number(row);
            pos_string.append(QString::number(column));

            connect(btn, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
            signalMapper->setMapping(btn, pos_string);
            Position position = stratego::Position(row, column);
            if(!game_board.isFree(position))
            {
                int rank = game_board.piece(stratego::Position(row, column))->rank();
                auto btn_color = game_board.piece(position)->color();
                if(btn_color==PlayerColor::BLUE)
                    btn->makeBlue(rank);
                else btn->makeRed(rank);
                if(!game_board.matchesColor(position, model_.currentPlayer().color())){
                    btn->setText("");
                    btn->setEnabled(false);
                }
            }else{
                btn->makeInvisibleDisabled();
            }
            ui->board_layout->addWidget(btn, row, column);
            row_buttons.push_back(btn);
        }
        board_buttons_.push_back(row_buttons);
    }
}

void MainWindow::updateBoard()
{
    stratego::Board game_board = model_.board();

    //we have to show the board to the player that just made the move
    for(int row = 0; row<game_board.size();row++){
        for(int column = 0; column<game_board.size();column++){
            PieceButton * btn = board_buttons_[row][column];
            Position position = stratego::Position(row, column);
            if(!game_board.isFree(position))
            {
                int rank = game_board.piece(stratego::Position(row, column))->rank();
                if(game_board.piece(position)->color()==PlayerColor::BLUE)
                    btn->makeBlue(rank);
                else btn->makeRed(rank);
                if(game_board.matchesColor(position, model_.currentPlayer().color())){
                    btn->setText("");
                    btn->setEnabled(false);
                }
            }else{
                btn->makeInvisibleDisabled();
            }
        }
    }

    //we alert the player that made the move that is no longer his turn
    if(PlayerColor::BLUE==model_.opponentPlayer().color()){
        ui->turn_blue->setText("");
    } else ui->turn_red->setText("");
    setEnableToBoardButtons(false);
    startTimerAndUpdateSeconds(3);
    if(PlayerColor::BLUE==model_.currentPlayer().color()){
        ui->turn_blue->setText("YOUR TURN!");
    } else ui->turn_red->setText("YOUR TURN!");
    for(int row = 0; row<game_board.size();row++){
        for(int column = 0; column<game_board.size();column++){
            PieceButton * btn = board_buttons_[row][column];
            Position position = stratego::Position(row, column);
            if(!game_board.isFree(position))
            {
                int rank = game_board.piece(stratego::Position(row, column))->rank();
                if(game_board.piece(position)->color()==PlayerColor::BLUE)
                    btn->makeBlue(rank);
                else btn->makeRed(rank);
                if(!game_board.matchesColor(position, model_.currentPlayer().color())){
                    btn->setText("");
                    btn->setEnabled(false);
                }
            }else{
                btn->makeInvisibleDisabled();
            }
        }
    }
}


void MainWindow::setupBoardBlue()
{
    ui->turn_blue->setText("YOUR TURN!");
    ui->start_red->setEnabled(false);
    auto pieces = model_.currentPlayer().pieces();
    int row = 0;
    int column = 0;
    std::vector<PieceButton *> row_buttons {};
    for(const auto &piece : pieces){
        PieceButton * btn = new PieceButton(row, column, model_, this);

        QString pos_string = QString::number(row);
        pos_string.append(QString::number(column));
        connect(btn, SIGNAL(clicked(bool)), signalMapperSETUP, SLOT(map()));
        signalMapperSETUP->setMapping(btn, pos_string);

        int rank = piece.rank();
        btn->makeBlue(rank);
        btn->setEnabled(true);
        ui->board_SETUPGL->addWidget(btn, row, column);
        row_buttons.push_back(btn);

        if(column == model_.board().size()-1)
        {
            setup_buttons_.push_back(row_buttons);
            row_buttons.clear();
            row++;
            column=0;
        } else column++;
    }
    for(row = model_.board().size()/2-1; row < model_.board().size(); row++){
        std::vector<PieceButton *> row_buttons {};
        for(column = 0; column<model_.board().size();column++){
            PieceButton * btn = new PieceButton(row, column, model_, this);

            QString pos_string = QString::number(row);
            pos_string.append(QString::number(column));
            connect(btn, SIGNAL(clicked(bool)), signalMapperSETUP, SLOT(map()));
            signalMapperSETUP->setMapping(btn, pos_string);

            btn->makeInvisibleDisabled();
            row_buttons.push_back(btn);
            ui->board_SETUPGL->addWidget(btn, row, column);
        }
        setup_buttons_.push_back(row_buttons);
    }
}
void MainWindow::setupBoardRed()
{
    ui->turn_red->setText("YOUR TURN");
    ui->turn_blue->setText("");
    int row;
    int column;
    for(row = 0; row < model_.board().size()/2-1; row++){
        for(column = 0; column<model_.board().size();column++){
            setup_buttons_[row][column]->setText("");
            setup_buttons_[row][column]->setEnabled(false);
        }
    }
    row=model_.board().size()/2+1;
    column=0;
    auto pieces = model_.currentPlayer().pieces();
    for(const auto &piece : pieces){
        int rank = piece.rank();
        setup_buttons_[row][column]->makeRed(rank);
        setup_buttons_[row][column]->setEnabled(true);
        if(column == model_.board().size()-1)
        {
            row++;
            column=0;
        } else column++;
    }
}

std::string MainWindow::constructString(int row)
{
    QString result;
    for(int col = 0; col<model_.board().size();col++)
    {
        QString text = setup_buttons_[row][col]->text();
        if(text.length()>2) text=text.front();
        result += text + " ";
    }
    return result.toStdString();
}


void MainWindow::makeClickablePositions()
{
    auto positions = model_.possibleMoves();
    for(int row = 0; row<model_.board().size();row++){
        for(int column = 0; column<model_.board().size();column++){
            PieceButton * btn = board_buttons_[row][column];
            bool validPosition=false;
            for (auto & pos2 : positions)
            {
                if (pos2.row()==row&&pos2.column()==column)
                {
                    validPosition = true;
                    break;
                }
            }
            if(validPosition)
            {
                btn->makeAvailablePosition();
            }
        }
    }
}

void MainWindow::disableLastClickablePositions()
{
    auto positions = model_.possibleMoves();
    auto game_board = model_.board();
    for(int row = 0; row<game_board.size();row++){
        for(int column = 0; column<game_board.size();column++){
            PieceButton * btn = board_buttons_[row][column];
            bool validPosition=false;
            for (auto & pos2 : positions)
            {
                if (pos2.row()==row&&pos2.column()==column)
                {
                    validPosition = true;
                    break;
                }
            }
            if(validPosition)
            {
                Position position = stratego::Position(row, column);
                if(!game_board.isFree(position))
                {
                    int rank = game_board.piece(stratego::Position(row, column))->rank();
                    auto btn_color = game_board.piece(position)->color();
                    if(btn_color==PlayerColor::BLUE)
                        btn->makeBlue(rank);
                    else btn->makeRed(rank);
                    if(!game_board.matchesColor(position, model_.currentPlayer().color())){
                        btn->setText("");
                        btn->setEnabled(false);
                    }
                }else{
                    btn->makeInvisibleDisabled();
                }
            }
        }
    }
}

void MainWindow::wait1Second()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::startTimerAndUpdateSeconds(int secs)
{
    while(secs>=0){
        ui->timer->setText(QString::number(secs));
        wait1Second();
        secs--;
    }
}

void MainWindow::setEnableToBoardButtons(bool enable)
{
    auto game_board = model_.board();
    for(int row = 0; row<game_board.size();row++){
        for(int column = 0; column<game_board.size();column++){
            PieceButton * btn = board_buttons_[row][column];
            btn->setEnabled(enable);
        }
    }
}

void MainWindow::pieceButtonHandler(QString pos)
{
    bool ok;
    int num = pos.toInt(&ok);
    int row = num/10;
    int col = num%10;
    if(clicked_count_==0){
        model_.selectSquare(Position(row, col));
        model_.updatePossibleMoves();
        makeClickablePositions();
        clicked_count_++;
    }else{
        bool movePosition=false;
        for (auto & pos2 : model_.possibleMoves())
        {
            if (pos2.row()==row&&pos2.column()==col)
            {
                movePosition = true;
                break;
            }
        }
        if(movePosition)
        {
            model_.move(Position(row, col));
            clicked_count_++;
            model_.isOver();
        } else{
            disableLastClickablePositions();
            model_.selectSquare(Position(row, col));
            model_.updatePossibleMoves();
            makeClickablePositions();
        }
    }
    if(clicked_count_==2){
        clicked_count_= 0;
    }
}

void MainWindow::pieceSetupButtonHandler(QString pos)
{
    bool ok;
    int num = pos.toInt(&ok);
    int row = num/10;
    int col = num%10;
    if(clicked_count_==0){
        last_column_setup = col;
        last_row_setup = row;
        clicked_count_++;
    }else{
        QString text_this = setup_buttons_[row][col]->text();
        QString text_last = setup_buttons_[last_row_setup][last_column_setup]->text();
        setup_buttons_[row][col]->setText(text_last);
        setup_buttons_[last_row_setup][last_column_setup]->setText(text_this);
        clicked_count_++;
    }
    if(clicked_count_==2){
        clicked_count_= 0;
    }
}

void MainWindow::startBlueButtonHandler()
{
    for(int row = 0; row <=model_.board().size()/2-2; row++){
        model_.initializeLine(constructString(row), row);
    }
    clicked_count_=0;
    startTimerAndUpdateSeconds(3);
    ui->start_red->setEnabled(true);
    ui->start_blue->setEnabled(false);
    setupBoardRed();
}

void MainWindow::startRedButtonHandler()
{
    ui->turn_blue->setText("YOUR TURN");
    ui->turn_red->setText("");
    for(auto row = model_.board().size()/2+1; row < model_.board().size(); row++){
        model_.initializeLine(constructString(row), row);
    }
    ui->boardUI->setVisible(true);
    ui->boardSETUP->setVisible(false);
    ui->menu_right->setVisible(true);
    ui->start_blue->setVisible(false);
    ui->start_red->setVisible(false);
    createBoard();
    clicked_count_=0;
}


void MainWindow::update(const std::string &message) {
    if (message == model_.PROPERTY_BOARD) {
        updateBoard();
    }

    if (message == model_.PROPERTY_ENDGAME) {
        //clearButtons();
        setEnableToBoardButtons(false);
        ui->info_panel_blue->setText("Game over!");
        ui->info_panel_red->setText("Game over!");
        if(model_.opponentPlayer().color()==PlayerColor::BLUE){
            ui->turn_blue->setText("YOU WON!");
            ui->turn_red->setText("YOU LOST!");
        }else{
            ui->turn_red->setText("YOU WON!");
            ui->turn_blue->setText("YOU LOST!");
        }
    }

    if (message == model_.PROPERTY_NEWRESULT) {
        auto result = model_.currentResult();
        QString text;
        if(result == ActionResult::BOTH_LOST){
            text.append("Both of your pieces are the same rank! You both lost!");
        } else {
            QString color_current = (model_.currentPlayer().color() == PlayerColor::BLUE)?"BLUE":"RED";
            QString color_opponent = (model_.opponentPlayer().color() == PlayerColor::BLUE)?"BLUE":"RED";
            if(result == ActionResult::CURRENT_LOST){
                text.append(color_current+" player captured a piece from the "+color_opponent+" player.");
            } else if(result == ActionResult::OPPONENT_LOST){
                text.append(color_opponent+" player captured a piece from the "+color_current+" player.");
            } else if(result == ActionResult::NOBODY_LOST)
                text.append("Moved successfully.");
        }
        ui->info_panel_blue->setText(text);
        ui->info_panel_red->setText(text);
    }
}


