#pragma once
#include "Figure.h"
class Queen : public Figure {
public:
    Queen(Color color, int startX, int startY, Board* board) : Figure(PieceType::Queen, color, startX, startY, board) {}

    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
