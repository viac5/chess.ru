#pragma once
#include "Figure.h" 

struct Move {
    int startX, startY;
    int endX, endY;
    Figure* movedPiece;
    Figure* capturedPiece;
    Color moveColor;
    int moveNumber;

    // Конструктор для удобства
    Move(int sX, int sY, int eX, int eY, Figure* moved, Figure* captured, Color color, int number)
        : startX(sX), startY(sY), endX(eX), endY(eY),movedPiece(moved), capturedPiece(captured), moveColor(color), moveNumber(number) {}
};
