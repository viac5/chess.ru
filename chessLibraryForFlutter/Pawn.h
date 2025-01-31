#pragma once
#include "Figure.h"

class Pawn : public Figure {
public:
	Pawn(Color color, int startX, int startY, Board* board) : Figure(PieceType::Pawn, color, startX, startY, board) {}
	bool isValidMove(int startX, int startY, int endX, int endY) override;
};