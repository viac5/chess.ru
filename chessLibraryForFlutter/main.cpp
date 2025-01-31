#include <iostream>
#include "Board.h"
#include <io.h>     
#include <fcntl.h> 
#include <windows.h> 
// -----------------ШАХИ РЕНТГЕН РОКИРОВКА | back | ВЗЯТИЕ НА ПРОХОДЕ | ПЕШКА НА КОНЦЕ | МАТ | ПАТ (тесты)
int main() {
    //// Устанавливаем кодировку консоли на UTF-8
    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8);
    //_setmode(_fileno(stdout), _O_U8TEXT); // Устанавливаем вывод в Unicode
    //_setmode(_fileno(stdin), _O_U8TEXT);  // Устанавливаем ввод в Unicode

    //Board A;  // Инициализируем доску
    //std::wstring move, piece;
    //std::vector<wchar_t> chars = { L'a',L'b',L'c',L'd',L'e',L'f',L'g',L'h' }; // Вектор символов для колонок

    //A.printBoard(); // Печать начального состояния доски
    //std::wcout << L"\n\n\n\n\n";

    //// Основной цикл ввода ходов
    //while (true) {
    //    std::wcout << L"Напишите ваш ход (пример: e2-e4), 'back' для возврата хода или 'stop' для выхода: ";
    //    std::wcin >> move;

    //    if (move == L"stop") {
    //        break;  // Прерываем цикл, если введено "stop"
    //    }
    //    if (move == L"back") {
    //        A.undoMove();  // Выполняем возврат хода
    //        A.printBoard();
    //        std::wcout << L"\n\n\n\n\n";
    //        continue;
    //    }

    //    if (move.length() == 5 && move[2] == L'-') {  // Проверка формата строки
    //        int startX = -1, startY = -1, endX = -1, endY = -1;

    //        // Парсим начальную колонку (букву)
    //        for (int i = 0; i < 8; ++i) {
    //            if (move[0] == chars[i]) {
    //                startX = i;
    //                break;
    //            }
    //        }

    //        // Парсим начальную строку (цифру)
    //        startY = move[1] - L'1';  // Преобразуем символ '1'-'8' в числа 0-7

    //        // Парсим конечную колонку (букву)
    //        for (int i = 0; i < 8; ++i) {
    //            if (move[3] == chars[i]) {
    //                endX = i;
    //                break;
    //            }
    //        }

    //        // Парсим конечную строку (цифру)
    //        endY = move[4] - L'1';  // Преобразуем символ '1'-'8' в числа 0-7

    //        // Проверяем, что парсинг прошел успешно и координаты в пределах допустимого диапазона
    //        if (startX != -1 && startY >= 0 && startY < 8 && endX != -1 && endY >= 0 && endY < 8) {
    //            try {
    //                // Пытаемся выполнить ход
    //                A.movePiece(startX, startY, endX, endY);
    //                if (A.getfigure(endX, endY)->getType() == Pawn && ((endY == 7 && A.getfigure(endX, endY)->getColor() == White) || (endY == 0 && A.getfigure(endX, endY)->getColor() == Black))){
    //                    std::wcout << L"Напишите в кого хотите превратить пешку (R,K,B,Q):";
    //                    std::wcin >> piece;
    //                    if (piece[0] == 'R') A.setOnRook(endX, endY, A.getfigure(endX, endY)->getColor());
    //                    if (piece[0] == 'K') A.setOnKnight(endX, endY, A.getfigure(endX, endY)->getColor());
    //                    if (piece[0] == 'B') A.setOnBishop(endX, endY, A.getfigure(endX, endY)->getColor());
    //                    if (piece[0] == 'Q') A.setOnQueen(endX, endY, A.getfigure(endX, endY)->getColor());
    //                }
    //                // Печатаем доску после хода
    //                A.printBoard();
    //                if (A.getBreak() > 0)break;
    //                std::wcout << L"\n\n\n\n\n";
    //            }
    //            catch (const std::exception& e) {
    //                std::wcerr << L"Invalid move: " << e.what() << std::endl;
    //                //break;  // Завершаем программу при ошибке
    //            }
    //        }
    //        else {
    //            std::wcout << L"Invalid move format." << std::endl;
    //        }
    //    }
    //    else {
    //        std::wcout << L"Invalid move format." << std::endl;
    //    }
    //}

    //std::wcout << L"Game over." << std::endl;
    //return 0;
    Board A;
    std::vector<std::vector<int>> encodedBoard(8, std::vector<int>(8, 0));
    encodedBoard = A.getEncodedBoard();
    
    std::wcout << std::endl;
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col < 8; ++col) {
            if (encodedBoard[row][col] != 0) {
                std::wcout << encodedBoard[row][col]<< " ";
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

