#include "Bishop.h"
#include "Board.h"
bool Bishop::isValidMove(int startX, int startY, int endX, int endY) {
    // ѕроверка, что движение диагональное
    if (abs(endX - startX) != abs(endY - startY)) {
        return false; // —лон может ходить только по диагонали
    }
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false; // ¬не границ доски
    }
    // ќпредел€ем направление движени€
    int xDirection = (endX > startX) ? 1 : -1;
    int yDirection = (endY > startY) ? 1 : -1;

    // ѕровер€ем все клетки по диагонали между стартом и целью
    for (int i = 1; i < abs(endX - startX); ++i) {
        int x = startX + i * xDirection;
        int y = startY + i * yDirection;

        // »спользуем указатель на доску (board) дл€ проверки клеток
        if (board->getPiece(x, y) != nullptr) {
            return false; // Ќа пути слона есть фигура
        }
    }

    // ѕровер€ем, что конечна€ клетка либо пуста, либо там фигура противоположного цвета
    Figure* targetPiece = board->getPiece(endX, endY);
    if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
        if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
            return false; // ‘игура не может ходить, так как король окажетс€ под шахом
        }
        else return true; // Ћибо клетка пуста, либо можно вз€ть фигуру противника
    }

    return false; // Ќевозможно завершить ход
}
