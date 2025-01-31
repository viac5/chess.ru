import 'dart:ffi';
import 'package:flutter/material.dart';
import 'chess_ffi.dart';

void main() {
  runApp(const ChessApp());
}

class ChessApp extends StatelessWidget {
  const ChessApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Chess App',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const ChessBoardScreen(),
    );
  }
}

class ChessBoardScreen extends StatefulWidget {
  const ChessBoardScreen({super.key});

  @override
  // ignore: library_private_types_in_public_api
  _ChessBoardScreenState createState() => _ChessBoardScreenState();
}

class _ChessBoardScreenState extends State<ChessBoardScreen> {
  Pointer<Board>? board;
  List<int> encodedBoard = List.filled(64, 0); // Инициализация пустой доски
  bool isBoardFlipped = false; // Для хранения состояния переворота доски
  int moveNumber = 0; // Номер хода

  int? selectedRow;
  int? selectedCol;

  @override
  void initState() {
    super.initState();
    initializeBoard();
  }

  void initializeBoard() {
    board = createBoard();
    fetchBoardState();
  }

  void fetchBoardState() {
    setState(() {
      encodedBoard = fetchEncodedBoard(board!);
    });
  }

  void movePieceOnBoard(int startX, int startY, int endX, int endY) {
  try {
    bool validColor, moveSuccess;
    int piece = encodedBoard[startY * 8 + startX];
    if(moveNumber % 2 == 0 && piece<=16)validColor=true;
    else if(moveNumber % 2 != 0 && piece>16)validColor=true;
    else validColor=false;
    
    if(validColor)moveSuccess = movePiece(board!, startX, startY, endX, endY);
    else moveSuccess = false;
    
    //if(!validColor)moveSuccess=false;
    if (moveSuccess ) {
      setState(() {
        moveNumber++;
      });
      print("Move - $moveNumber successful from ($startX, $startY) to ($endX, $endY)");

      // Проверяем, является ли фигура пешкой и дошла ли она до конца доски
      int piece = encodedBoard[startY * 8 + startX];
      bool isWhitePawn = piece == 11 && endY == 7; // Белая пешка
      bool isBlackPawn = piece == 21 && endY == 0; // Чёрная пешка

      if (isWhitePawn || isBlackPawn) {
        int color = isWhitePawn ? 1 : 2; // 1 - Белая, 2 - Чёрная
        showPromotionDialog(context, endY, endX, color); // Показать окно преобразования
      }

      fetchBoardState(); // Обновляем состояние доски после хода

      // Проверка на мат или пат
      int gameState = getBreak(board!);

      if (gameState == 1) {
        String winner = piece <= 16 ? 'Белые' : 'Чёрные';
        showEndDialog(context, 'Мат', '$winner поставили мат! Игра окончена.');
      } else if (gameState == 2) {
        String currentPlayer = piece <= 16 ? 'Чёрные' : 'Белые';
        showEndDialog(context, 'Пат', 'Пат! $currentPlayer не могут продолжать игру.');
      }
    } else {
      print("Invalid move from ($startX, $startY) to ($endX, $endY)");
    }
  } catch (e) {
    print("Error during move: $e");
  }
}


  void showPromotionDialog(BuildContext context, int row, int col, int color) {
  showDialog(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        title: const Text('Выберите фигуру для преобразования'),
        content: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: [
            GestureDetector(
              onTap: () {
                setPawn(board!, col, row, 1); // 1 - Слон
                fetchBoardState();
                Navigator.of(context).pop();
              },
              child: Image.asset(
                color == 1 ? 'assets/images/WhiteBishop.png' : 'assets/images/BlackBishop.png',
                width: 57,
                height: 57,
              ),
            ),
            GestureDetector(
              onTap: () {
                setPawn(board!, col, row, 2); // 2 - Конь
                fetchBoardState();
                Navigator.of(context).pop();
              },
              child: Image.asset(
                color == 1 ? 'assets/images/WhiteKnight.png' : 'assets/images/BlackKnight.png',
                width: 57,
                height: 57,
              ),
            ),
            GestureDetector(
              onTap: () {
                setPawn(board!, col, row, 3); // 3 - Ладья
                fetchBoardState();
                Navigator.of(context).pop();
              },
              child: Image.asset(
                color == 1 ? 'assets/images/WhiteRook.png' : 'assets/images/BlackRook.png',
                width: 57,
                height: 57,
              ),
            ),
            GestureDetector(
              onTap: () {
                setPawn(board!, col, row, 4); // 4 - Ферзь
                fetchBoardState();
                Navigator.of(context).pop();
              },
              child: Image.asset(
                color == 1 ? 'assets/images/WhiteQueen.png' : 'assets/images/BlackQueen.png',
                width: 57,
                height: 57,
              ),
            ),
          ],
        ),
      );
    },
  );
}
void showEndDialog(BuildContext context, String title, String message) {
  showDialog(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        backgroundColor: Colors.white, // Цвет фона окна
        title: Text(
          title,
          style: TextStyle(
            fontSize: 24,
            fontWeight: FontWeight.bold,
            color: title == 'Мат' ? const Color.fromARGB(255, 56, 32, 32) : const Color.fromARGB(255, 36, 24, 8),
          ),
          textAlign: TextAlign.center,
        ),
        content: Padding(
          padding: const EdgeInsets.symmetric(vertical: 10.0),
          child: Text(
            message,
            style: const TextStyle(
              fontSize: 18,
              color: Colors.black87,
            ),
            textAlign: TextAlign.center,
          ),
        ),
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(15.0), // Закругленные углы
        ),
        actions: [
          TextButton(
            style: TextButton.styleFrom(
              backgroundColor: Colors.blueAccent, // Цвет кнопки
              foregroundColor: Colors.white, // Цвет текста на кнопке
              padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 10), // Отступы кнопки
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(10.0), // Закругленные углы кнопки
              ),
            ),
            onPressed: () {
              Navigator.of(context).pop();
              resetGame(); // Перезапуск игры
            },
            child: const Text('ОК'),
          ),
        ],
      );
    },
  );
}

void resetGame() {
  // Проверяем, что board не null перед удалением
  // if (board != null) {
  //   destroyBoard(board!); // Уничтожаем старую доску
  //   board = null; // Устанавливаем board в null после удаления
  // }

  // Создаем новую доску и обновляем состояние
  board = createBoard();
  fetchBoardState(); // Получаем состояние новой доски

  // Сбрасываем выделенные клетки
  setState(() {
    selectedRow = null;
    selectedCol = null;
  });
}

  void undoMoveOnBoard() {
    try {
      undoMove(board!);
      fetchBoardState();
      setState(() {
      if (moveNumber > 1) {
        moveNumber--;
      }
    });
    } catch (e) {
      print("Error during undo move: $e");
    }
  }

  void flipBoard() {
    setState(() {
      isBoardFlipped = !isBoardFlipped; // Изменяем состояние доски
    });
  }

  @override
  void dispose() {
    destroyBoard(board!);
    super.dispose();
  }

 @override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      title: const Text('chess.ru'),
      foregroundColor: const Color.fromARGB(255, 180, 171, 171), // Цвет текста на AppBar
      backgroundColor: const Color.fromARGB(221, 17, 16, 16), // Темный цвет для AppBar
      centerTitle: true,
    ),
    body: Container(
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: [ Colors.grey[800]!, const Color.fromARGB(255, 24, 24, 24), Colors.black], // Темный градиент
          begin: Alignment.topCenter,
          end: Alignment.bottomCenter,
        ),
      ),
      child: Column(
        children: [
          SizedBox(
            width: 500, // Фиксированная ширина
            height: 500, // Фиксированная высота
            child: GridView.builder(
              gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                crossAxisCount: 8,
                childAspectRatio: 1,
              ),
              itemCount: 64,
              itemBuilder: (context, index) {
                final actualIndex = isBoardFlipped ? 63 - index : index;
                final piece = encodedBoard[actualIndex];
                final row = actualIndex ~/ 8;
                final col = actualIndex % 8;
                final isWhiteSquare = (row + col) % 2 == 0;

                return GestureDetector(
                  onTap: () => onSquareTapped(row, col),
                  child: DragTarget<int>(
                    onAcceptWithDetails: (pieceCode) {
                      movePieceOnBoard(selectedCol!, selectedRow!, col, row);
                      setState(() {
                        selectedRow = null;
                        selectedCol = null;
                      });
                    },
                    builder: (context, candidateData, rejectedData) {
                      return Container(
                        decoration: BoxDecoration(
                          color: isWhiteSquare
                              ? const Color.fromARGB(255, 255, 254, 219) // Темный цвет для белых клеток
                              : const Color.fromARGB(255, 78, 78, 78), // Ещё более темный цвет для черных клеток
                          border: Border.all(
                            color: Colors.black54, // Легкая граница
                            width: 1,
                          ),
                          boxShadow: const [
                            BoxShadow(
                              color: Colors.black26,
                              blurRadius: 5,
                              spreadRadius: 0,
                              offset: Offset(0, 2), // Смещение тени
                            ),
                          ],
                        ),
                        child: Center(
                          child: piece != 0
                              ? Draggable<int>(
                                  data: piece,
                                  onDragStarted: () {
                                    setState(() {
                                      selectedRow = row;
                                      selectedCol = col;
                                    });
                                  },
                                  feedback: Container(
                                    decoration: const BoxDecoration(
                                      boxShadow: [
                                        BoxShadow(
                                          color: Colors.black54,
                                          blurRadius: 10,
                                          spreadRadius: 0,
                                          offset: Offset(0, 2),
                                        ),
                                      ],
                                    ),
                                    child: Image.asset(
                                      getPieceImagePath(piece),
                                      width: 57,
                                      height: 57,
                                    ),
                                  ),
                                  childWhenDragging: const SizedBox.shrink(),
                                  child: Image.asset(
                                    getPieceImagePath(piece),
                                    width: 57,
                                    height: 57,
                                  ),
                                )
                              : const SizedBox.shrink(),
                        ),
                      );
                    },
                  ),
                );
              },
            ),
          ),
          const SizedBox(height: 16), // Отступ между доской и кнопками
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              ElevatedButton(
                onPressed: undoMoveOnBoard,
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.blueGrey, // Темный цвет кнопки
                  padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                  elevation: 5, // Добавление тени
                ),
                child: const Text(
                  'Назад',
                  style: TextStyle(fontSize: 16, color: Colors.white),
                ),
              ),
              const SizedBox(width: 10),
              ElevatedButton(
                onPressed: flipBoard,
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.greenAccent, // Яркий цвет для кнопки
                  padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                  elevation: 5, // Добавление тени
                ),
                child: const Text(
                  'Перевернуть',
                  style: TextStyle(fontSize: 16, color: Colors.black),
                ),
              ),
            ],
          ),
        ],
      ),
    ),
  );
}


  void onSquareTapped(int row, int col) {
    // Для хода по клику добавляем проверку на повторное нажатие на ту же клетку
    if (selectedRow != null && selectedCol != null) {
      if (selectedRow == row && selectedCol == col) {
        setState(() {
          selectedRow = null;
          selectedCol = null;
        });
        return; // Нажали на ту же клетку, сбрасываем выбор
      }

      // Ход по клику
      movePieceOnBoard(selectedCol!, selectedRow!, col, row);
      setState(() {
        selectedRow = null;
        selectedCol = null;
      });
    } else {
      setState(() {
        selectedRow = row;
        selectedCol = col;
      });
    }
  }

  String getPieceImagePath(int pieceCode) {
    switch (pieceCode) {
      case 11:
        return 'assets/images/WhitePawn.png';
      case 12:
        return 'assets/images/WhiteKnight.png';
      case 13:
        return 'assets/images/WhiteBishop.png';
      case 14:
        return 'assets/images/WhiteRook.png';
      case 15:
        return 'assets/images/WhiteQueen.png';
      case 16:
        return 'assets/images/WhiteKing.png';
      case 21:
        return 'assets/images/BlackPawn.png';
      case 22:
        return 'assets/images/BlackKnight.png';
      case 23:
        return 'assets/images/BlackBishop.png';
      case 24:
        return 'assets/images/BlackRook.png';
      case 25:
        return 'assets/images/BlackQueen.png';
      case 26:
        return 'assets/images/BlackKing.png';
      default:
        return '';
    }
  }
}
