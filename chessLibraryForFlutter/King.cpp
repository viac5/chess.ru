#include "King.h"
#include "Board.h"

bool King::isValidMove(int startX, int startY, int endX, int endY) {
    if (abs(endX - startX) > 2 || abs(endY - startY) > 1) {
        return false;
    }
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false;
    }
    if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
        return false;
    }
    
    if (abs(endX - startX) == 2 && startY==endY) {//���������
        if (!countMove)return false;

        int xDirection = (endX > startX) ? 1 : -1;
        int rookX = (endX > startX) ? 7 : 0;

        Figure* RookPiece = board->getPiece(rookX, endY);
        if (RookPiece->getType() != Rook)return false;

        class::Rook* rookPiece = dynamic_cast<class::Rook*>(RookPiece); // ���������� � ������ Rook

        if (!rookPiece->countMoves())return false;

        for (int x = startX + xDirection; x != rookX; x += xDirection) {
            if (board->getPiece(x, startY) != nullptr) return false;
        }
        for (int x = startX; x != endX + xDirection; x += xDirection) {
            if (board->isSquareAttacked(x, startY, (this->getColor() == White) ? Black : White)) return false;
        }
        board->setPiece(rookX, startY, startX + xDirection, startY);
    }
    else {
        if (abs(endX - startX) == 2)return false;
        Figure* targetPiece = board->getPiece(endX, endY);
        if (targetPiece != nullptr && targetPiece->getColor() == this->getColor()) {
            return false;
        }

        // ���������, �� �������� �� ������ ��� ������ ����� ����
        if (board->isSquareAttacked(endX, endY, (this->getColor() == White) ? Black : White)) {
            return false;
        }
    }
    countMove = false;
    return true;  
}
//
//bool King::isValidMove(int startX, int startY, int endX, int endY) {
//    // ��������, ��� �������� �� ���� ������ � ����� �����������
//    if (abs(endX - startX) > 1 || abs(endY - startY) > 1) {
//        return false;
//    }
//
//    // �������� ������ �� ������� �����
//    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
//        return false; // ��� ������ �����
//    }
//
//    // ���������, ��� �������� ������ ���� �����, ���� ��� ������ ���������������� �����
//    Figure* targetPiece = board->getPiece(endX, endY);
//    if (targetPiece != nullptr && targetPiece->getColor() == this->getColor()) {
//        return false; // ������ ������ �� ������, ��� ����� ������ ���� �� �����
//    }
//
//    // ���������, �� �������� �� ������ ��� ������ ����� ����
//    if (board->isSquareAttacked(endX, endY, (this->getColor() == White) ? Black : White)) {
//        return false;
//    }
//
//    return true;
//}