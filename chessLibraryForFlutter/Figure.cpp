#include "Figure.h"
std::wstring Figure::getTypeString() {
    if (color == White) {
        return(type == Pawn) ? L"♙" : (type == Rook) ? L"♖" : (type == Knight) ? L"♘" : (type == Bishop) ? L"♗" : (type == Queen) ? L"♕" : (type == King) ? L"♔" : L". ";
        //return(type == Pawn) ? "P" : (type == Rook) ? "R" : (type == Knight) ? "Kn" : (type == Bishop) ? "B" : (type == Queen) ? "Q" : (type == King) ? "K" : ". ";
    }

    if (color == Black) {
        return (type == Pawn) ? L"♟" : (type == Rook) ? L"♜" : (type == Knight) ? L"♞" : (type == Bishop) ? L"♝" : (type == Queen) ? L"♛" : (type == King) ? L"♚" : L". ";
    }
    return L". ";
}