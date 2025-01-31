#pragma once
#include "Figure.h"
class Bishop : public Figure {
public:
    Bishop(Color color, int startX, int startY, Board* board): Figure(PieceType::Bishop, color, startX, startY, board) {}

    bool isValidMove(int startX, int startY, int endX, int endY) override;
};

