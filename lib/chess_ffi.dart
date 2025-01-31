import 'dart:ffi';
import 'dart:io';
import 'package:ffi/ffi.dart';

// Определяем библиотеку для загрузки нативного кода
final DynamicLibrary chessLib = Platform.isWindows
    ? DynamicLibrary.open("D:\\c-+++\\chessLibraryForFlutter\\x64\\Debug\\chessLibraryForFlutter.dll")
    : DynamicLibrary.process(); // Для других платформ (Linux/Mac)

// Структура Board для FFI
final class Board extends Struct {
  @Int32()
  external int dummyField; // Временное поле для корректной работы через FFI
}

// Определение функций из C++
typedef CreateBoardC = Pointer<Board> Function();
typedef CreateBoardDart = Pointer<Board> Function();

typedef DestroyBoardC = Void Function(Pointer<Board>);
typedef DestroyBoardDart = void Function(Pointer<Board>);

typedef UndoMoveC = Void Function(Pointer<Board>);
typedef UndoMoveDart = void Function(Pointer<Board>);

typedef MovePieceC = Uint8 Function(Pointer<Board>, Int32, Int32, Int32, Int32);
typedef MovePieceDart = int Function(Pointer<Board>, int, int, int, int);

typedef GetBreakC = Int32 Function(Pointer<Board>);
typedef GetBreakDart = int Function(Pointer<Board>);

typedef GetEncodedBoardC = Void Function(Pointer<Board>, Pointer<Int32>);
typedef GetEncodedBoardDart = void Function(Pointer<Board>, Pointer<Int32>);

typedef SetPawnC = Void Function(Pointer<Board>, Int32, Int32, Int32);
typedef SetPawnDart = void Function(Pointer<Board>, int, int, int);

// Функции для взаимодействия с C++
final CreateBoardDart createBoard = chessLib
    .lookup<NativeFunction<CreateBoardC>>('createBoard')
    .asFunction();

final DestroyBoardDart destroyBoard = chessLib
    .lookup<NativeFunction<DestroyBoardC>>('destroyBoard')
    .asFunction();

final UndoMoveDart undoMove = chessLib
    .lookup<NativeFunction<UndoMoveC>>('undoMove')
    .asFunction();

final MovePieceDart _movePiece = chessLib
    .lookup<NativeFunction<MovePieceC>>('movePiece')
    .asFunction();

// Изменяем возврат функции movePiece на bool
bool movePiece(Pointer<Board> board, int startX, int startY, int endX, int endY) {
  return _movePiece(board, startX, startY, endX, endY) != 0;
}

final GetBreakDart getBreak = chessLib
    .lookup<NativeFunction<GetBreakC>>('getBreak')
    .asFunction();

final GetEncodedBoardDart getEncodedBoard = chessLib
    .lookup<NativeFunction<GetEncodedBoardC>>('getEncodedBoard')
    .asFunction();

final SetPawnDart setPawn = chessLib
    .lookup<NativeFunction<SetPawnC>>('setPawn')
    .asFunction();


// Функция для получения закодированной доски
List<int> fetchEncodedBoard(Pointer<Board> board) {
  final Pointer<Int32> buffer = calloc<Int32>(64); // 8x8 доска
  getEncodedBoard(board, buffer);
  
  List<int> boardData = List.generate(64, (index) {
    int piece = buffer[index]; // Читаем значение как int
    return piece; // Возвращаем значение как есть (отрицательные числа будут обработаны правильно)
  });
  
  calloc.free(buffer);
  return boardData;
}
