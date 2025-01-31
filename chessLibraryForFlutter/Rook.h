#pragma once
#include "Figure.h"
class Rook : public Figure {
private:
    bool countMove = true;
public:
    Rook(Color color, int startX, int startY, Board* board) : Figure(PieceType::Rook, color, startX, startY, board) {}

    bool isValidMove(int startX, int startY, int endX, int endY) override;
    bool countMoves() {
        return countMove;
    }
};

