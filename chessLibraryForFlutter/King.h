#pragma once
#include "Figure.h"
class King : public Figure {
private:
    bool countMove = true;
public:
    King(Color color, int startX, int startY, Board* board) : Figure(PieceType::King, color, startX, startY, board) {}

    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
