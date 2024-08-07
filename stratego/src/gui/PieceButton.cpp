#include "PieceButton.h"
using namespace stratego;
PieceButton::PieceButton(int row, int col,stratego::Model& game, QWidget *parent)
    : QPushButton(parent),
      model_{game},
      row_{row},
      col_{col}
{
}

void PieceButton::makeInvisibleEnabled()
{
    setText("");
    setStyleSheet("QPushButton { background-color: "+invisible_color_+" }");
    current_color_=invisible_color_;
    setEnabled(true);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void PieceButton::makeInvisibleDisabled()
{
    setText("");
    setStyleSheet("QPushButton { background-color: "+invisible_color_+" }");
    current_color_=invisible_color_;
    setEnabled(false);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void PieceButton::makeRed(int rank)
{
    if(rank == 11) {
        setText("Bomb");
        setEnabled(false);
    }
    else if(rank == 0) {
        setText("Flag");
        setEnabled(false);
    }
    else {
        setText(QString::number(rank));
        setEnabled(true);
    }
    setAutoFillBackground(true);
    setStyleSheet("QPushButton {background-color: "+red_color_+"}");
    current_color_=red_color_;
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void PieceButton::makeBlue(int rank)
{
    if(rank == 11) {
        setText("Bomb");
        setEnabled(false);
    }
    else if(rank == 0) {
        setText("Flag");
        setEnabled(false);
    }
    else {
        setText(QString::number(rank));
        setEnabled(true);
    }
    setAutoFillBackground(true);
    setStyleSheet("QPushButton {background-color: "+blue_color_+"}");
    current_color_=blue_color_;
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void PieceButton::makeAvailablePosition()
{
    if(current_color_==red_color_){
        setStyleSheet("QPushButton { background-color: rgba(248, 67, 67, 1)}");
    }else if(current_color_==blue_color_)
        setStyleSheet("QPushButton { background-color: rgba(128, 226, 255, 1)}");
    else setStyleSheet("QPushButton { background-color: rgba(200, 200, 0, 0.3)}");
    setEnabled(true);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

