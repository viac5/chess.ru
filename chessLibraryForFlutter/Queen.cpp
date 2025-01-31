#include "Queen.h"
#include "Board.h"
bool Queen::isValidMove(int startX, int startY, int endX, int endY) {
    // ��������, ��� �������� ������������
    if (abs(endX - startX) != abs(endY - startY) && startX != endX && startY != endY) {
        return false; // ����� ����� ������ ������ ����� ��� �� ���������
    }
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false; // ��� ������ �����
    }
    if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
        return false; // ������ �� ����� ������, ��� ��� ������ �������� ��� �����
    }
    if (abs(endX - startX) == abs(endY - startY) && startX != endX && startY != endY) {
        // ���������� ����������� ��������
        int xDirection = (endX > startX) ? 1 : -1;
        int yDirection = (endY > startY) ? 1 : -1;

        // ��������� ��� ������ �� ��������� ����� ������� � �����
        for (int i = 1; i < abs(endX - startX); ++i) {
            int x = startX + i * xDirection;
            int y = startY + i * yDirection;

            // ���������� ��������� �� ����� (board) ��� �������� ������
            if (board->getPiece(x, y) != nullptr) {
                return false; // �� ���� ����� ���� ������
            }
        }

        // ���������, ��� �������� ������ ���� �����, ���� ��� ������ ���������������� �����
        Figure* targetPiece = board->getPiece(endX, endY);
        if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
            return true; // ���� ������ �����, ���� ����� ����� ������ ����������
        }

        return false; // ���������� ��������� ���
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