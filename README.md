<h1 align="center">
  <br>
  CheckCPP
  <br>
</h1>

<h4 align="center">A chess game with an intelligent AI opponent.</h4>

<p align="center">
  <a href="#key-features">Key Features</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#game-rules">Game Rules</a> •
  <a href="#installation">Installation</a> •
  <a href="#bot-difficulty">Bot Difficulty</a> •
  <a href="#license">License</a>
</p>

## Key Features

* Intelligent AI Opponent
  - Minimax algorithm with alpha-beta pruning for optimal move selection
  - Configurable search depth for different difficulty levels
  - Position evaluation system with piece values and board positioning
* Bot vs. Bot Mode
* Full Chess Implementation
* Modern GUI
* Cross Platform

## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com), [CMake 3.16+](https://cmake.org/), and [Qt6](https://www.qt.io/download) installed on your computer. From your command line:

```bash
# Clone this repository

# Go into the repository
$ cd check-cpp

# Create build directory
$ mkdir build && cd build

# Configure with CMake
$ cmake ..

# Build the application
$ make

# Run the application
$ ./chess
```

> **Note**
> Make sure Qt6 is properly installed and the Qt6 path is configured in CMakeLists.txt for your system.

## Game Rules

This chess implementation follows standard chess rules:

* **Movement** - Click on a piece to select it, then click on a destination square to move
* **Turn Order** - White (player) moves first, then black (bot) responds
* **Valid Moves** - Only legal moves are allowed, preventing moves that put your king in check
* **Special Moves**
  - Castling (kingside and queenside)
  - En passant captures
  - Pawn promotion (automatic for bot, manual selection for player)
* **Game End Conditions**
  - Checkmate - King is in check with no legal moves
  - Stalemate - No legal moves available but not in check
  - Draw conditions

## Bot Difficulty

The bot's strength can be adjusted by modifying the search depth in the code:

- **Depth 3-4**: Beginner level (fast moves, basic strategy)
- **Depth 5-6**: Intermediate level (balanced, good tactics)
- **Depth 7+**: Advanced level (slow but very strong)

Current default: **Depth 5** 

## Installation

### Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Qt6 (Widgets module)
- Git

### macOS Installation

```bash
# Install Qt6 via Homebrew
$ brew install qt@6

# Update CMAKE_PREFIX_PATH in CMakeLists.txt if needed
# Default: /opt/homebrew/lib/cmake/Qt6
```

### Windows Installation

Download and install Qt6 from the [official website](https://www.qt.io/download), then update the `CMAKE_PREFIX_PATH` in `CMakeLists.txt` to point to your Qt6 installation.

### Building from Source

```bash
mkdir build
cd build
cmake ..
make
```

## Project Structure

```
check-cpp/
├── src/
│   ├── main.cpp           # Application entry point
│   ├── gui/               # Qt GUI implementation
│   ├── board/             # Chess board and tile logic
│   ├── pieces/            # Chess piece implementations
│   ├── bot/               # AI bot with minimax algorithm
│   └── assets/            # Piece sprites (PNG images)
├── CMakeLists.txt         # Build configuration
└── README.md
```

## Credits

**Piece Sprites**: [Clipart Library](https://clipart-library.com/clipart/kTKopobEc.htm)

## Support

If you encounter any issues or have questions about the chess application, please open an issue on the GitHub repository.

## License

MIT

---

> Developed by Terrance Wong
