#pragma once
#include "Figure.h"
class Knight : public Figure {
public:
    Knight(Color color, int startX, int startY, Board* board) : Figure(PieceType::Knight, color, startX, startY, board) {}

    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
