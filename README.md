# Stratego Game Implementation in C++

This project implements the classic board game **Stratego** in C++ with a graphical user interface (GUI). It was collaboratively developed by **Gracziela Sewodo** (52949) and **Iuliana Costil** (55994) for a C++ development course at **Haute Ecole Bruxelles Brabant**.

## Project Structure

The project directory structure is organized into several directories and files:

### `metier/`
Contains core game logic and data structures.

- **header/**
  - `utils/`
    - `observer.h`: Header for observer pattern.
    - `subject.h`: Header for subject pattern.
  - `game.h`: Header for game logic.
  - `board.h`: Header for board class.
  - `square.h`: Header for square class.
  - `position.h`: Header for position class.
  - `common_piece.h`: Header for common piece class.
  - `common_moveable_piece.h`: Header for common moveable piece class.
  - `Common_piece_factory.h`: Header for piece factory.
  - `spy.h`: Header for spy class.
  - `miner.h`: Header for miner class.
  - `direction.h`: Header for direction enum.
  - `player.h`: Header for player class.
  - `playerColor.h`: Header for player color enum.
  - `model.h`: Header for model class.
  - `state.h`: Header for state enum.
  - `action_result.h`: Header for action result enum.
  - `constants.h`: Header for project constants.

- **sources/**
  - `utils/`
    - `subject.cpp`: Implementation for subject pattern.
  - `game.cpp`: Implementation for game logic.
  - `board.cpp`: Implementation for board class.
  - `common_piece.cpp`: Implementation for common piece class.
  - `common_moveable_piece.cpp`: Implementation for common moveable piece class.
  - `player.cpp`: Implementation for player class.

### `console/`
Contains the console-based implementation of the game.

- **view/**
  - **header/**
    - `view.h`: Header for console view.
  - **sources/**
    - `view.cpp`: Implementation for console view.

- **controller/**
  - **header/**
    - `controller.h`: Header for console controller.
  - **sources/**
    - `controller.cpp`: Implementation for console controller.

- `main.cpp`: Entry point for the console application.

### `Gui/`
Contains the GUI implementation of the game using Qt.

- **images/**

- **headers/**
  - `mainwindow.h`: Header for main GUI window.
  - `PieceButton.h`: Header for custom piece button.

- **sources/**
  - `mainwindow.cpp`: Implementation for main GUI window.
  - `main.cpp`: Entry point for the GUI application.
  - `PieceButton.cpp`: Implementation for custom piece button.

### `tests/`
Contains unit tests for various aspects of the game.

- **sources/**
  - `main.cpp`: Entry point for the test application.
  - `tst_model.cpp`: Unit tests for game model and logic.

## Explanation of Classes and Enums

### Classes

- **Board**: Represents the 10x10 game board.
- **Square**: Represents a square on the game board.
- **CommonPiece**: Represents a non-moveable game piece.
- **CommonMoveablePiece**: Represents a moveable game piece, subclass of CommonPiece.
- **Miner**: Represents a specific moveable piece type that can defuse bombs.
- **Spy**: Represents a specific moveable piece type that can defeat a higher-ranked Marshal.
- **Position**: Represents a position on the game board.
- **Model**: Coordinates and manages the game's components and logic.

### Enums

- **ActionResult**: Represents the result of a game action (e.g., win, loss, draw).
- **State**: Represents the current state of the game (e.g., not started, in progress, ended).
- **PlayerColor**: Represents the color of players (e.g., blue, red).

## Changes Made Since Initial Submission

### Pieces

- Implemented two types of pieces:
  1. **CommonPiece**: Non-moveable piece with rank and color.
  2. **CommonMoveablePiece**: Moveable piece with rank, color, and maximum steps.

- Added subclasses of CommonMoveablePiece:
  - **Spy**: Can defeat a Marshal but is vulnerable to other pieces.
  - **Miner**: Can defuse bombs.

- Overridden operators (`==`, `>`, `<`) for CommonPiece to compare by rank.

- Introduced CommonPieceFactory for piece instantiation and polymorphism handling.

### Game

- Added method to swap players after each move, ensuring turns alternate between blue and red.

- Introduced selectedSquare to track currently selected game square.

- Implemented methods to determine valid moves for selected pieces based on movement rules.

### Square

- Enhanced Square class to include a position attribute.

- Replaced `std::optional<piece>` with `std::shared_ptr<CommonPiece>` for polymorphism support.

### General

- Implemented Observer/Observable pattern and MVC architecture.

- Detailed class diagram and additional information available in the accompanying PDF file.

### GUI (Version 3)

- Updated Game class in Model:
  - Added `currentResult_` to track game outcomes after each move.
  - Modified `move` method to return void and notify observers of game state changes.

- Detailed class diagram and further information available in the accompanying PDF file.

## How to Build and Run

To build and run the project:

1. **Console Application**: Compile `console.pro` using a C++ compiler with appropriate flags.
2. **GUI Application**: Use Qt Creator or qmake to build `gui.pro`. Ensure Qt libraries are installed.
3. **Testing**: Compile `tests.pro` to run unit tests.

## Dependencies

- **Qt Framework**: Required for GUI components (`Gui/`).
- **Catch2**: Header-only test framework for unit testing (`tests/sources/catch.hpp`).

## Contributors

- **Gracziela Sewodo**: Developer
- **Iuliana Costil**: Developer