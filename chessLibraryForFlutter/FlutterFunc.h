#pragma once
#include "Board.h"


extern "C" {
    __declspec(dllexport) Board* createBoard();

    __declspec(dllexport) void destroyBoard(Board* board);

    __declspec(dllexport) void undoMove(Board* board);

    __declspec(dllexport) bool movePiece(Board* board, int startX, int startY, int endX, int endY);

    __declspec(dllexport) int getBreak(Board* board);

    __declspec(dllexport) void getEncodedBoard(Board* board, int* buffer);

    __declspec(dllexport) void setPawn(Board* board, int x, int y, int piece);
}

// getType, getColor, getBreak,  set(4)
// getEncodedBoard
//0 : ������ ������,
//1 : �����,
//2 : ����,
//3 : �
//4 : �����,
//5 : �����,
//6 : ������.