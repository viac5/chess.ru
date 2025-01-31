#include "Rook.h"
#include "Board.h"

bool Rook::isValidMove(int startX, int startY, int endX, int endY) {
	if (startX != endX && startY != endY) {
		return false;
	}

	if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
		return false;
	}

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
		if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
			return false;
		}
		else {
			countMove = false;
			return true;
		}
	}
	return false;
}


//bool Rook::isValidMove(int startX, int startY, int endX, int endY) {
//    // ѕроверка, что движение пр€мое
//    if (startX!=endX && startY!=endY) {
//        return false; // ладь€ может ходить только пр€мо
//    }
//    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
//        return false; // ¬не границ доски
//    }
//    if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
//        return false; // ‘игура не может ходить, так как король окажетс€ под шахом
//    }
//
//    int dynamical, dynDirection,promX,promY,FOR;
//    bool XY;
//    if (startX == endX && startY != endY) {
//        dynamical = startY;
//        dynDirection= (endY > startY) ? 1 : -1;// ќпредел€ем направление движени€
//        XY = true;
//        FOR = abs(endY - startY);
//
//    }
//    if (startX != endX && startY == endY) {
//        dynamical = startX;
//        dynDirection= (endX > startX) ? 1 : -1;// ќпредел€ем направление движени€
//        XY = false;
//        FOR = abs(endX - startX);
//    }
//    // ѕровер€ем все клетки по пр€мой между стартом и целью
//    for (int i = 1; i < FOR; ++i) {
//        int way = dynamical+i* dynDirection;
//        if (XY==true)promX = startX, promY = way;
//        else promX = way, promY = startY;
//        // »спользуем указатель на доску (board) дл€ проверки клеток
//        if (board->getPiece(promX, promY) != nullptr) {
//            return false; // Ќа пути ладьи есть фигура
//        }
//    }
//
//    // ѕровер€ем, что конечна€ клетка либо пуста, либо там фигура противоположного цвета
//    Figure* targetPiece = board->getPiece(endX, endY);
//    if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
//        return true; // Ћибо клетка пуста, либо можно вз€ть фигуру противника
//    }
//
//    return false; // Ќевозможно завершить ход
//}