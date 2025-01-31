#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Move.h"
class Board {
private:
	std::vector<std::vector<Figure*>> squares; // 8x8 ��������� �����
	std::stack<Move> moveHistory; // ���� ��� �������� ������� �����
	int currentMoveNumber = 1; // ����� �������� ����
	int isBreakGame = 0;// 0 ���� ������������ , 1 ��� , 2 ���

public:
	Board() {
		// �������������� ����� 8x8 ������� �������� (nullptr)
		squares.resize(8, std::vector<Figure*>(8, nullptr));

		// ����������� �����
		for (int i = 0; i < 8; ++i)
		{

			squares[1][i] = new class::Pawn(Color::White, i, 1, this); // ����� ����� �� ������ �����
			squares[6][i] = new class::Pawn(Color::Black, i, 6, this); // ������ ����� �� ������� ����

		}

		//�����
		squares[0][2] = new class::Bishop(Color::White, 2, 0, this);
		squares[0][5] = new class::Bishop(Color::White, 2, 0, this);
		squares[7][2] = new class::Bishop(Color::Black, 2, 7, this);
		squares[7][5] = new class::Bishop(Color::Black, 2, 7, this);
		//�����
		squares[0][0] = new class::Rook(Color::White, 0, 0, this);
		squares[0][7] = new class::Rook(Color::White, 7, 0, this);
		squares[7][7] = new class::Rook(Color::Black, 7, 7, this);
		squares[7][0] = new class::Rook(Color::Black, 0, 7, this);
		//����
		squares[0][1] = new class::Knight(Color::White, 1, 0, this);
		squares[0][6] = new class::Knight(Color::White, 6, 0, this);
		squares[7][6] = new class::Knight(Color::Black, 6, 7, this);
		squares[7][1] = new class::Knight(Color::Black, 1, 7, this);
		//�����
		squares[0][4] = new class::Queen(Color::White, 4, 0, this);
		squares[7][4] = new class::Queen(Color::Black, 4, 7, this);
		//������
		squares[0][3] = new class::King(Color::White, 3, 0, this);
		squares[7][3] = new class::King(Color::Black, 3, 7, this);
	}

	~Board() {
		// ����������� ������ ��� ���� �����
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (squares[row][col] != nullptr) {
					delete squares[row][col]; // ������� ������, ���� ��������� �� �������
				}
			}
		}
		while (!moveHistory.empty()) {
			Move lastMove = moveHistory.top();
			moveHistory.pop();

			// ���� ������ ���� ���������, ������� ������
			if (lastMove.movedPiece) {
				delete lastMove.movedPiece; // �������, ���� ��������� �� �������
			}
			if (lastMove.capturedPiece) {
				delete lastMove.capturedPiece; // �������, ���� ��������� �� �������
			}
		}
	}

	// ����� ��� ����������� ������ � ����� ������ �� ������
	bool movePiece(int startX, int startY, int endX, int endY);

	// ����� ��� ��������� ������ � ������������ ������
	Figure* getPiece(int x, int y) {
		return squares[y][x];
	}
	Move getLastMove() {
		if (!moveHistory.empty()) {
			return moveHistory.top();
		}
		else return Move(-1, -1, -1, -1,nullptr, nullptr, NoColor, 0);
	}
	int getBreak() {
		return isBreakGame;
	}
	void setPiece(int startX, int startY, int endX, int endY) {
		if (squares[startY][startX] != nullptr && squares[endY][endX] == nullptr) {
			squares[endY][endX] = squares[startY][startX];
			squares[startY][startX] = nullptr;
		}
	}
	bool isSquareAttacked(int x, int y, Color attackerColor);// �������� �� ����
	bool isKingCheckAfterMove(int startX, int startY, int endX, int endY, Color attackerColor);
	bool isCheckmate(Color playerColor);
	bool isStalemate(Color playerColor);

	void printBoard();
	void undoMove();
	Figure* getfigure(int x,int y) {
		return squares[y][x];
	}
	void setOnBishop(int x, int y, Color color){
		delete squares[y][x];
		squares[y][x] = new class::Bishop(color, x, y, this);
	}
	void setOnKnight(int x, int y, Color color) {
		delete squares[y][x];
		squares[y][x] = new class::Knight(color, x, y, this);
	}
	void setOnRook(int x, int y, Color color) {
		delete squares[y][x];
		squares[y][x] = new class::Rook(color, x, y, this);
	}
	void setOnQueen(int x, int y, Color color) {
		delete squares[y][x];
		squares[y][x] = new class::Queen(color, x, y, this);
	}
	std::vector<std::vector<int>> getEncodedBoard();

};
