#include "Knight.h"
#include "Board.h"

bool Knight::isValidMove(int startX, int startY, int endX, int endY) {
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false;
    }

    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
        return false;
    }

    Figure* targetPiece = board->getPiece(endX, endY);
    if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
        if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
            return false;
        }
        return true; 
    }

    return false; 
}
//bool Knight::isValidMove(int startX, int startY, int endX, int endY) {
//    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
//        return false; // ¬не границ доски
//    }
//    // ќпредел€ем направление движени€
//    int xDirection;
//    int yDirection;
//    if (endX - startX == 1)xDirection = 1;
//    if (endX - startX == -1)xDirection = -1;
//    if (endX - startX == 2)xDirection = 2;
//    if (endX - startX == -2)xDirection = -2;
//    // int xDirection = (endX - startX==1) ? 1 : (endX - startX == -1)? -1: (endX - startX == 2)? 2 : (endX - startX == -2) ? -2: ;
//    if (endY - startY == 1)yDirection = 1;
//    if (endY - startY == -1)yDirection = -1;
//    if (endY - startY == 2)yDirection = 2;
//    if (endY - startY == -2)yDirection = -2;
//    if ((endX - startX != 1 && endX - startX != -1 && endX - startX != 2 && endX - startX != -2) || (endY - startY != 1 && endY - startY != -1 && endY - startY != 2 && endY - startY != -2) || (std::abs(xDirection) + std::abs(yDirection) != 3))return false;
//
//    // ѕровер€ем, что конечна€ клетка либо пуста, либо там фигура противоположного цвета
//    Figure* targetPiece = board->getPiece(endX, endY);
//    if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
//        if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
//            return false; // ‘игура не может ходить, так как король окажетс€ под шахом
//        }
//        else return true; // Ћибо клетка пуста, либо можно вз€ть фигуру противника
//    }
//
//    return false; // Ќевозможно завершить ход
//}