cmake_minimum_required(VERSION 3.29)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 23)

add_library(sudokusolver STATIC src/sudokusolver.cpp)
target_include_directories(sudokusolver PUBLIC "${CMAKE_SOURCE_DIR}/include")