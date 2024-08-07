#ifndef PIECEBUTTON_H
#define PIECEBUTTON_H

#include "model.h"
#include <QPushButton>

class PieceButton : public QPushButton
{
private:
    stratego::Model& model_;
    const QString invisible_color_ = "rgba(200, 200, 0, 0)";
    const QString red_color_ = "rgba(208, 27, 27, 1)";
    const QString blue_color_ = "rgba(98, 186, 249, 1)";
    QString current_color_;
public:
    PieceButton(int row, int col,stratego::Model& model,QWidget *parent = nullptr);
    void makeInvisibleEnabled();
    void makeInvisibleDisabled();
    void makeRed(int rank);
    void makeBlue(int rank);
    void makeAvailablePosition();
protected:
    /*!
     * \brief row_ the row.
     */
    int row_;

    /*!
     * \brief col_ the column.
     */
    int col_;

};


#endif // PIECEBUTTON_H
