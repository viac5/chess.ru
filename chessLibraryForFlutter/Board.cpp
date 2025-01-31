#include "Board.h"
#include <io.h>     
#include <fcntl.h> 
bool Board::movePiece(int startX, int startY, int endX, int endY) {
	Figure* figure = squares[startY][startX];
	Figure* capturedPiece;
	if (!figure) {
		return false;
	}
	if (figure->isValidMove(startX, startY, endX, endY)) {
		if (figure->getType() == Pawn && squares[endY][endX] == nullptr && std::abs(endX - startX) == 1) {
			capturedPiece = squares[startY][endX];
			squares[startY][endX] = nullptr;
		}
		else {
			capturedPiece = squares[endY][endX];
		}
		moveHistory.push(Move(startX, startY, endX, endY, figure, capturedPiece, figure->getColor(), currentMoveNumber));

		squares[endY][endX] = figure; 

		squares[startY][startX] = nullptr; 

		figure->setPosition(endX, endY);

		currentMoveNumber++;

		Color opponentColor = (figure->getColor() == White) ? Black : White;

		if (isCheckmate(opponentColor)) {
			std::wcout << (opponentColor == White ? L"White" : L"Black") << " is checkmated!" << std::endl;
			isBreakGame = 1;
			return true;
		}

		if (isStalemate(opponentColor)) {
			std::wcout << L"It's a stalemate!" << std::endl;
			isBreakGame = 2;
			return true;
		}
		return true;
	}
	else {
		return false;
	}
}

void Board::printBoard() {
	std::wcout << std::endl;
	for (int row = 7; row >= 0; --row) {
		for (int col = 0; col < 8; ++col) {
			if (squares[row][col] != nullptr) {
				std::wcout << squares[row][col]->getTypeString() << " ";
			}
			else {
				std::wcout << L". ";
			}

			if (col == 7) std::wcout << L"  " + std::to_wstring(row + 1);
		}
		std::wcout << std::endl;
	}
	std::wcout << std::endl << L"a b c d e f g h ";
}

void Board::undoMove() {
	if (!moveHistory.empty()) {
		Move lastMove = moveHistory.top();
		moveHistory.pop();

		int startX = lastMove.startX;
		int startY = lastMove.startY;
		int endX = lastMove.endX;
		int endY = lastMove.endY;
		Figure* capturedPiece = lastMove.capturedPiece;
		Figure* movedPiece = lastMove.movedPiece;
		squares[startY][startX] = squares[endY][endX];
		squares[startY][startX]->setPosition(startX, startY);

		if (capturedPiece) { 
			if (capturedPiece->getType() == Pawn && endY != capturedPiece->getY()) {
				// Это взятие на проходе
				squares[endY][endX] = nullptr; 
				squares[capturedPiece->getY()][capturedPiece->getX()] = capturedPiece;
			}
			else {
				squares[endY][endX] = capturedPiece;
			}
		}
		else if (movedPiece->getType() == King && std::abs(endX - startX) == 2) {//рокировка
			int xDirection = (endX > startX) ? 1 : -1;
			int rookX = (endX > startX) ? 7 : 0;
			if (squares[endY][endX - xDirection]->getType() == Rook) {
				squares[endY][endX - xDirection] = nullptr;
				setOnRook(rookX, endY, movedPiece->getColor());
				squares[endY][endX] = nullptr;
			}
		}
		else {
			squares[endY][endX] = nullptr;
		}
		currentMoveNumber--;
	}
	else {
		throw std::invalid_argument("moveHistory is empty");
	}
}

bool Board::isSquareAttacked(int x, int y, Color attackerColor) {
	// Проверка, атакует ли какая-либо фигура указанной стороны клетку (x, y)
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Figure* piece = getPiece(col, row);
			if (piece != nullptr && piece->getColor() == attackerColor) {
				// Используем новую функцию для проверки атаки, а не полноценный ход
				if (piece->getType() == Pawn) {
					if (((piece->getColor()==Black && y-row==-1)||(piece->getColor() == White && y - row == 1)) && std::abs(x - col) == 1)return true; ///// подумать!!!!!
					else continue;
				}
				if (piece->isValidMove(col, row, x, y)) {
					return true; // Фигура может атаковать клетку
				}
			}
		}
	}
	return false;
}

bool Board::isKingCheckAfterMove(int startX, int startY, int endX, int endY, Color attackerColor) {
	// Находим координаты короля текущего игрока
	int kingX = -1, kingY = -1;
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Figure* piece = getPiece(col, row);
			if (piece != nullptr && piece->getType() == King && piece->getColor() != attackerColor) {
				kingX = col;
				kingY = row;
				break;
			}
		}
		if (kingX != -1) break; // Прерываем поиск, если нашли короля
	}

	// Если король сам перемещается, нужно обновить его позицию на конечную клетку
	Figure* movingPiece = getPiece(startX, startY);
	if (movingPiece != nullptr && movingPiece->getType() == King) {
		kingX = endX;
		kingY = endY;
	}

	// Сохраняем целевую клетку
	Figure* targetPiece = getPiece(endX, endY);

	// Совершаем временный ход
	squares[endY][endX] = movingPiece;
	squares[startY][startX] = nullptr;

	// Проверяем, окажется ли король под шахом после хода
	bool kingInCheck = isSquareAttacked(kingX, kingY, attackerColor);

	// Откатываем ход
	squares[startY][startX] = movingPiece;
	squares[endY][endX] = targetPiece;

	return kingInCheck;
}

bool Board::isCheckmate(Color playerColor) {
	// Находим координаты короля
	int kingX = -1, kingY = -1;
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Figure* piece = getPiece(col, row);
			if (piece != nullptr && piece->getType() == King && piece->getColor() == playerColor) {
				kingX = col;
				kingY = row;
				break;
			}
		}
	}
	if (kingX == -1)return true;
	// Если король под шахом
	if (isSquareAttacked(kingX, kingY, (playerColor == White) ? Black : White)) {
		// Перебираем все фигуры игрока и проверяем возможные ходы
		for (int startY = 0; startY < 8; ++startY) {
			for (int startX = 0; startX < 8; ++startX) {
				Figure* piece = getPiece(startX, startY);
				if (piece != nullptr && piece->getColor() == playerColor) {
					for (int endY = 0; endY < 8; ++endY) {
						for (int endX = 0; endX < 8; ++endX) {
							if (piece->isValidMove(startX, startY, endX, endY)) {
								// Если после хода король не будет под шахом, то это не мат
								if (!isKingCheckAfterMove(startX, startY, endX, endY, (playerColor == White) ? Black : White)) {
									return false; // Нет мата
								}
							}
						}
					}
				}
			}
		}
		return true; // Все возможные ходы проверены, мата избежать нельзя
	}
	return false; // Король не под шахом, мата нет
}

bool Board::isStalemate(Color playerColor) {
	// Находим координаты короля
	int kingX = -1, kingY = -1;
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Figure* piece = getPiece(col, row);
			if (piece != nullptr && piece->getType() == King && piece->getColor() == playerColor) {
				kingX = col;
				kingY = row;
				break;
			}
		}
	}

	// Если король не под шахом
	if (!isSquareAttacked(kingX, kingY, (playerColor == White) ? Black : White)) {
		// Перебираем все фигуры игрока и проверяем возможные ходы
		for (int startY = 0; startY < 8; ++startY) {
			for (int startX = 0; startX < 8; ++startX) {
				Figure* piece = getPiece(startX, startY);
				if (piece != nullptr && piece->getColor() == playerColor) {
					for (int endY = 0; endY < 8; ++endY) {
						for (int endX = 0; endX < 8; ++endX) {
							if (piece->isValidMove(startX, startY, endX, endY)) {
								// Если есть хотя бы один легальный ход, пата нет
								return false;
							}
						}
					}
				}
			}
		}
		return true; // Ни одного легального хода — пат
	}
	return false; // Король под шахом, значит пата нет
}


std::vector<std::vector<int>> Board::getEncodedBoard() {
	std::vector<std::vector<int>> encodedBoard(8, std::vector<int>(8, 0)); // Инициализируем 8x8 доску с 0

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Figure* figure = squares[row][col];

			// Проверяем, есть ли фигура на клетке
			if (figure == nullptr) {
				encodedBoard[row][col] = 0;
				continue; // Переходим к следующей клетке
			}

			// Определяем цвет
			int colorOffset = (figure->getColor() == White) ? 10 : 20;

			// Присваиваем значение в зависимости от типа фигуры
			if (dynamic_cast<class::Pawn*>(figure)) {
				encodedBoard[row][col] = 1 + colorOffset;
			}
			else if (dynamic_cast<class::Knight*>(figure)) {
				encodedBoard[row][col] = 2 + colorOffset;
			}
			else if (dynamic_cast<class::Bishop*>(figure)) {
				encodedBoard[row][col] = 3 + colorOffset;
			}
			else if (dynamic_cast<class::Rook*>(figure)) {
				encodedBoard[row][col] = 4 + colorOffset;
			}
			else if (dynamic_cast<class::Queen*>(figure)) {
				encodedBoard[row][col] = 5 + colorOffset;
			}
			else if (dynamic_cast<class::King*>(figure)) {
				encodedBoard[row][col] = 6 + colorOffset;
			}
		}
	}

	return encodedBoard;
}

