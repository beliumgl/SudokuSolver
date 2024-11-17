#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <vector>
#include <stdexcept>
#include <functional>

class Sudoku {
public:
  /**
   * @brief Solves the Sudoku table, modifying it in place.
   *
   * @param sudokuTable A 2D std::vector containing digits in a specified range and corresponding EMPTY_CELL.
   */
  void solve(std::vector<std::vector<char>>& sudokuTable);

private:
  constexpr static char EMPTY_CELL{ '.' };
  constexpr static unsigned int ROW_LENGTH{ 9 };
  constexpr static unsigned int COLUMN_LENGTH{ 9 };
  constexpr static unsigned int BLOCK_SIDE_LENGTH{ 3 };
  constexpr static unsigned int MIN_CELL_VALUE{ 1 };
  constexpr static unsigned int MAX_CELL_VALUE{ 9 };

  struct SudokuBlock {
    std::vector<std::vector<char>> block;
    SudokuBlock();
  };

  struct SudokuRow {
    std::vector<char> row;
    SudokuRow();
  };

  struct SudokuColumn {
    std::vector<char> column;
    SudokuColumn();
  };

  struct CellID {
    unsigned int row;
    unsigned int column;
    unsigned int block;

    CellID(unsigned int r, unsigned int c, unsigned int bID);
  };

  std::vector<SudokuBlock> blocks;
  std::vector<SudokuRow> rows;
  std::vector<SudokuColumn> columns;

  void ParseSudokuTable(const std::vector<std::vector<char>>& sudokuTable);

  [[nodiscard]]
  std::vector<CellID> FindEmptyCells() const;

  [[nodiscard]]
  bool IsValidValue(const unsigned int& row, const unsigned int& column, const char& value) const;
};

#endif // SUDOKUSOLVER_H