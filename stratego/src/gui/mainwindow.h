#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PieceButton.h"
#include "game.h"
#include "qsignalmapper.h"
#include "utils/observer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public stratego::utils::Observer
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * Constructor of the MainView class will initialize class attributs and connect the two QSignalMapper to the corresponding slots
     * @param model
     * @param parent
     */
    explicit MainWindow(stratego::Model& model, QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief startGame
     * We will first ask the players if they would like to use the file to fill the board
     *  if yes: we set visible the board and the game can start
     *  if no: we set visible the SETUP board and let them fill the board one after another, the board will be created line by line from the setup board for
     * each player and the game can start
     */
    void startGame();
    /**
     * @brief createBoard
     * This method
     *  will create the buttons of the board,
     *  will set the QString for the map for each button (that will be created from the row and the column)
     *  will fill in the board_buttons_ attribute and the board_layout
     */
    void createBoard();
    /**
     * Updates the board of the game
     * We show the board for the player that just made a move, alert him that it is no longer his turn and then show the board for the other player
     * @brief updateBoard
     */
    void updateBoard();
    /**
     * @brief setupBoardBlue
     * This method will create all the setup buttons and set the QString for the map for each button (that will be created from the row and the column) and
     * add them to the setup_buttons_ and to the layout for the setup board
     * The red buttons will be invisible and not clickable at the start as well as the start button of the red player
     *
     */
    void setupBoardBlue();
    /**
     * @brief setupBoardRed
     * This method will update the red setup buttons with the available buttons, it will hide the content of the buttons of the blue player
     */
    void setupBoardRed();

    /**
     * @brief constructString
     * This method will construct a string in which each word is a rank, the ranks are ordered as they appear in the given row
     * @param row
     * @return
     */
    std::string constructString(int row);

    /**
     * @brief makeClickablePositions
     * This method will enable the valid positions so that the players can click on them
     */
    void makeClickablePositions();

    /**
     * @brief removeLastClickablePositions
     * This method will disable the last valid positions so that the players can no longer click on them
     */
    void disableLastClickablePositions();

    /**
     * @brief wait1Second
     * This method will help us make a pause of 1 second
     */
    void wait1Second();
    /**
     * @brief startTimerAndUpdateSeconds This method will and make a pause of sec seconds and also update the timer every second
     * @param sec
     */
    void startTimerAndUpdateSeconds(int sec);
    /**
     * @brief setEnableToBoardButtons This method will enable/disable all the board buttons baes on the bool given in the arguments
     */
    void setEnableToBoardButtons(bool);

private:
    Ui::MainWindow *ui;
    void update(const std::string &message) override;
    stratego::Model& model_;
    int clicked_count_;
    int last_row_setup;
    int last_column_setup;
    QSignalMapper *signalMapper;
    QSignalMapper *signalMapperSETUP;
    std::vector<std::vector<PieceButton *>> board_buttons_;
    std::vector<std::vector<PieceButton *>> setup_buttons_;

private slots:
    void pieceButtonHandler(QString);
    void pieceSetupButtonHandler(QString);
    void startBlueButtonHandler();
    void startRedButtonHandler();
};

#endif // MAINWINDOW_H
