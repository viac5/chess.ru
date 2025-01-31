#include "Bishop.h"
#include "Board.h"
bool Bishop::isValidMove(int startX, int startY, int endX, int endY) {
    // ��������, ��� �������� ������������
    if (abs(endX - startX) != abs(endY - startY)) {
        return false; // ���� ����� ������ ������ �� ���������
    }
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false; // ��� ������ �����
    }
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
        if (board->isKingCheckAfterMove(startX, startY, endX, endY, (this->getColor() == White) ? Black : White)) {
            return false; // ������ �� ����� ������, ��� ��� ������ �������� ��� �����
        }
        else return true; // ���� ������ �����, ���� ����� ����� ������ ����������
    }

    return false; // ���������� ��������� ���
}
