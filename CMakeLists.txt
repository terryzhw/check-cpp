cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_executable(chess
    src/main.cpp
    src/gui/Game.cpp
    src/board/Board.cpp
    src/board/Tile.cpp
    src/pieces/Piece.cpp
    src/pieces/Pawn.cpp
    src/pieces/Bishop.cpp
    src/pieces/Knight.cpp
    src/pieces/Rook.cpp
    src/pieces/Queen.cpp
    src/pieces/King.cpp
)

target_link_libraries(chess PRIVATE Qt6::Widgets)

set_target_properties(chess PROPERTIES
    WIN32_EXECUTABLE ON
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})