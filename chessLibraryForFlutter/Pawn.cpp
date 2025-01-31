#include "Pawn.h"
#include "Board.h"

bool Pawn::isValidMove(int startX, int startY, int endX, int endY) {
    int direction = (color == White) ? 1 : -1; // Направление движения для пешки

    // Проверка границ доски
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false;
    }

    // Проверка, не ставит ли ход короля под шах
    if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
        return false;
    }

    Figure* targetPiece = board->getPiece(endX, endY);

    // Ход пешки вперёд
    if (startX == endX) {
        // Обычный ход на одну клетку вперёд
        if (endY == startY + direction && targetPiece == nullptr) {
            return true;
        }
        // Первый ход пешки на две клетки
        if (endY == startY + 2 * direction && targetPiece == nullptr &&
            ((startY == 1 && color == White) || (startY == 6 && color == Black)) &&
            board->getPiece(startX, startY + direction) == nullptr) {
            return true;
        }
    }

    // Взятие фигуры по диагонали
    if (abs(endX - startX) == 1 && endY == startY + direction && targetPiece != nullptr && targetPiece->getColor() != this->getColor()) {
        return true;
    }

    // Взятие на проходе
    Move lastMove = board->getLastMove();
    if (abs(endX - startX) == 1 && endY == startY + direction && lastMove.movedPiece != nullptr &&
        lastMove.movedPiece->getType() == PieceType::Pawn && lastMove.movedPiece->getColor() != this->getColor() &&
        lastMove.startY == startY + 2 * direction && lastMove.endX == endX && lastMove.endY == startY) {
        //board->setPiece(endX, startY, endX, startY + direction); 
        return true;
    }

    return false; // Ход недопустим
}