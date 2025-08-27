cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_executable(chess
    main.cpp
    Game.cpp
    Board.cpp
    Tile.cpp
    Piece.cpp
    Pawn.cpp
)

target_link_libraries(chess PRIVATE Qt6::Widgets)

set_target_properties(chess PROPERTIES
    WIN32_EXECUTABLE ON
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})