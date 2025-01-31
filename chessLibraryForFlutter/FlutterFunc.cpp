#include "FlutterFunc.h"

extern "C" Board * createBoard() {
    return new Board();
}

extern "C" void destroyBoard(Board * board) {
    if (board != nullptr) {
        delete board;  // Удаляем объект, если он не является nullptr
        board = nullptr;  // Обнуляем указатель после удаления
    }
}

extern "C" void undoMove(Board * board) {
    if (board != nullptr) {
        board->undoMove();
    }
}
extern "C" bool movePiece(Board * board, int startX, int startY, int endX, int endY) {
    return board->movePiece(startX, startY, endX, endY);
}

extern "C" int getBreak(Board * board) {
    return board->getBreak();
}

extern "C" void getEncodedBoard(Board * board, int* buffer) {

    auto encodedBoard = board->getEncodedBoard();
    int index = 0;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            buffer[index++] = encodedBoard[row][col];
        }
    }
}

extern "C" void setPawn(Board * board,int x,int y, int piece) {
    Figure* Piece = board->getfigure(x, y);
    if (piece == 1) board->setOnBishop(x, y, Piece->getColor());
    if (piece == 2) board->setOnKnight(x, y, Piece->getColor());
    if (piece == 3) board->setOnRook(x, y, Piece->getColor());
    if (piece == 4) board->setOnQueen(x, y, Piece->getColor());
}