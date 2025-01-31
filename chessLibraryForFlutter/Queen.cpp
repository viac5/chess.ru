#include "Queen.h"
#include "Board.h"
bool Queen::isValidMove(int startX, int startY, int endX, int endY) {
    // Проверка, что движение диагональное
    if (abs(endX - startX) != abs(endY - startY) && startX != endX && startY != endY) {
        return false; // Ферзь может ходить только прямо или по диагонали
    }
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false; // Вне границ доски
    }
    if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
        return false; // Фигура не может ходить, так как король окажется под шахом
    }
    if (abs(endX - startX) == abs(endY - startY) && startX != endX && startY != endY) {
        // Определяем направление движения
        int xDirection = (endX > startX) ? 1 : -1;
        int yDirection = (endY > startY) ? 1 : -1;

        // Проверяем все клетки по диагонали между стартом и целью
        for (int i = 1; i < abs(endX - startX); ++i) {
            int x = startX + i * xDirection;
            int y = startY + i * yDirection;

            // Используем указатель на доску (board) для проверки клеток
            if (board->getPiece(x, y) != nullptr) {
                return false; // На пути ферзя есть фигура
            }
        }

        // Проверяем, что конечная клетка либо пуста, либо там фигура противоположного цвета
        Figure* targetPiece = board->getPiece(endX, endY);
        if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
            return true; // Либо клетка пуста, либо можно взять фигуру противника
        }

        return false; // Невозможно завершить ход
    }
    if ((abs(endX - startX) != abs(endY - startY)) && (startX == endX || startY == endY)) {
        int deltaX = (endX > startX) ? 1 : (endX < startX) ? -1 : 0;
        int deltaY = (endY > startY) ? 1 : (endY < startY) ? -1 : 0;

        int x = startX + deltaX;
        int y = startY + deltaY;

        while (x != endX || y != endY) {
            if (board->getPiece(x, y) != nullptr) {
                return false;
            }
            x += deltaX;
            y += deltaY;
        }

        Figure* targetPiece = board->getPiece(endX, endY);
        if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
            return true;
        }
        return false;
    }
    return false;
}