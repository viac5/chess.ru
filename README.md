# Desktop Chess Application

![Chess Game Screenshot](https://github.com/user-attachments/assets/557d6e05-f6e2-488a-b296-3046034ac007) <!-- Место для вставки скриншота работы программы -->

## О проекте

Этот проект представляет собой десктопные шахматы с движком на C++ и клиентом, написанным с использованием фреймворка Flutter. Игра предоставляет захватывающий опыт шахматной партии с интерактивным пользовательским интерфейсом.

## Архитектура проекта

### chessLibraryForFlutter

`chessLibraryForFlutter` — это библиотека на C++, которая собирается в динамическую библиотеку (.dll), обеспечивая связь между Dart и C++. Библиотека написана в соответствии с принципами ООП:

- **Figure**: базовый класс для всех фигур.
- **Наследуемые фигуры**: Bishop, Queen, Pawn, Knight, King, Rook, каждая со своими методами.
- **King**: содержит дополнительные методы для проверки матов, патов и сквозного удара (нельзя убрать фигуру, если после этого хода король будет атакован).
![Checkmate Screenshot](https://github.com/user-attachments/assets/a5ae195a-b736-4634-8e69-d4781a676148) <!-- Место для вставки скриншота интерфейса клиента -->


### Доска

Доска представлена в виде матрицы 8x8, где каждая клетка имеет тип `Figure`. Инициализация доски происходит с правильно расставленными фигурами. Также реализованы методы для переворота доски и возврата последнего хода.

### Клиентская часть

Клиентская часть, написанная на Flutter, создает объект доски и полностью работает на движке C++. Flutter был выбран из-за схожести синтаксиса языка Dart с C++, что сократило время изучения и разработки.

## Установка и запуск

1. Клонируйте репозиторий:
    ```bash
    git clone https://github.com/yourusername/desktop-chess-app.git
    ```
2. Перейдите в папку проекта:
    ```bash
    cd desktop-chess-app
    ```
3. Соберите библиотеку на C++ и свяжите её с клиентом на Flutter.

## Как играть

1. Запустите приложение.
2. Начните новую партию и наслаждайтесь игрой!


## Вклад

Принимаются вкладчики! Пожалуйста, создайте issue или pull request для улучшений.

## Лицензия

Этот проект лицензирован под MIT License.

