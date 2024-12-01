# Sudoku Solver

![Stars](https://img.shields.io/github/stars/beliumgl/sudokusolver?style=social)
![Forks](https://img.shields.io/github/forks/beliumgl/sudokusolver?style=social)

## Overview

This project provides a C++23 implementation of a Sudoku solver that can solve standard 9x9 Sudoku puzzles (can be modified) using backtracking algorithms. It is designed to be efficient, easy to use, and extendable for future enhancements.

## Features

- **Backtracking Algorithm**: Utilizes a recursive backtracking algorithm to find solutions.
- **Dynamic Input**: Accepts Sudoku puzzles as 2D vectors, allowing for easy integration and modification.
- **Error Handling**: Throws exceptions for unsolvable puzzles, ensuring robust performance.
- **Modular Design**: Organized into header and source files, making it easy to maintain and extend.

## Getting Started

### Prerequisites

To build and run this project, you will need:

- A C++ compiler that supports C++23 (e.g., clang++, g++)
- Git (optional, for cloning the repository)

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/beliumgl/sudokusolver.git
   cd sudokusolver
2. **Compiling to static library**:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .

### Sample Code

```cpp
#include <sudokusolver/sudokusolver.hpp>
#include <iostream>
#include <vector>

int main() {
    // Define a Sudoku puzzle (. represents empty cells)
    std::vector<std::vector<char>> sudokuTable = {
        {'.', '.', '.', '1', '2', '3', '.', '8', '.'},
        {'1', '.', '.', '.', '.', '.', '.', '3', '7'},
        {'.', '3', '8', '7', '4', '6', '9', '.', '2'},
        {'3', '4', '5', '8', '1', '7', '6', '2', '9'},
        {'7', '2', '6', '.', '.', '.', '.', '.', '8'},
        {'8', '9', '1', '.', '.', '.', '3', '.', '4'},
        {'.', '.', '7', '9', '5', '1', '2', '4', '3'},
        {'9', '.', '3', '4', '7', '2', '8', '6', '5'},
        {'.', '5', '.', '6', '.', '8', '.', '.', '1'}
    };

    // Create an instance of the Sudoku solver
    Sudoku solver;

    // Solve the Sudoku puzzle
    try {
        solver.solve(sudokuTable);
        
        // Print the solved Sudoku puzzle
        std::cout << "Solved Sudoku Puzzle:" << std::endl;
        for (const auto& row : sudokuTable) {
            for (char cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl; // Handle unsolvable puzzle case
    }

    return 0;
}
