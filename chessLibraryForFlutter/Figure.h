#pragma once
#include <string>
#include <vector>


enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King, None };
enum Color { White, Black, NoColor };

class Board;

class Figure {
protected:
    PieceType type;
    Color color;
    int x, y;
    Board* board;

public:
    Figure(PieceType type, Color color, int x, int y, Board* board): type(type), color(color), x(x), y(y), board(board) {}

    virtual bool isValidMove(int startX, int startY, int endX, int endY) = 0; // виртуальная функция
    
    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }
    PieceType getType() const { return type; }

    std::wstring getTypeString();

    Color getColor() const { return color; }

    std::string getColorString() const {
        return (color == White) ? "White" : (color == Black) ? "Black" : "None";
    }
    Board* getBoard() const { return board; }
};

