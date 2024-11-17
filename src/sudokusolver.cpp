#include <sudokusolver.hpp>

Sudoku::SudokuBlock::SudokuBlock()
    : block(BLOCK_SIDE_LENGTH, std::vector<char>(BLOCK_SIDE_LENGTH, EMPTY_CELL)) {}

Sudoku::SudokuRow::SudokuRow()
    : row(ROW_LENGTH, EMPTY_CELL) {}

Sudoku::SudokuColumn::SudokuColumn()
    : column(COLUMN_LENGTH, EMPTY_CELL) {}

Sudoku::CellID::CellID(unsigned int r, unsigned int c, unsigned int bID)
    : row(r), column(c), block(bID) {}

void Sudoku::solve(std::vector<std::vector<char>>& sudokuTable) {
    ParseSudokuTable(sudokuTable);
    std::vector<CellID> emptyCellIDs{ FindEmptyCells() };

    std::function<bool(size_t)> SolveRecursively = [&](size_t emptyCellID) {
        if (emptyCellID >= emptyCellIDs.size())
            return true;

        CellID emptyCell{ emptyCellIDs[emptyCellID] };
        std::vector<char> possibleValues;

        for (char value{ MIN_CELL_VALUE + '0' }; value <= MAX_CELL_VALUE + '0'; ++value) {
            if (IsValidValue(emptyCell.row, emptyCell.column, value)) {
                possibleValues.push_back(value);
            }
        }

        if (possibleValues.empty()) {
            return false;
        }

        for (char value : possibleValues) {
            rows[emptyCell.row].row[emptyCell.column] = value;
            columns[emptyCell.column].column[emptyCell.row] = value;
            unsigned int blockIndex = emptyCell.block;
            blocks[blockIndex].block[emptyCell.row % BLOCK_SIDE_LENGTH][emptyCell.column % BLOCK_SIDE_LENGTH] = value;

            if (SolveRecursively(emptyCellID + 1)) {
                return true;
            }

            rows[emptyCell.row].row[emptyCell.column] = EMPTY_CELL;
            columns[emptyCell.column].column[emptyCell.row] = EMPTY_CELL;
            blocks[blockIndex].block[emptyCell.row % BLOCK_SIDE_LENGTH][emptyCell.column % BLOCK_SIDE_LENGTH] = EMPTY_CELL;
        }

        return false;
    };

    if (!SolveRecursively(0)) {
        throw std::invalid_argument("No possible solution found.");
    }

    for (unsigned int row{ 0 }; row < ROW_LENGTH; ++row) {
        for (unsigned int column{ 0 }; column < COLUMN_LENGTH; ++column) {
            sudokuTable[row][column] = rows[row].row[column];
        }
    }
}

void Sudoku::ParseSudokuTable(const std::vector<std::vector<char>>& sudokuTable) {
    for (unsigned int row{ 0 }; row < ROW_LENGTH; row++) {
        rows.emplace_back(SudokuRow());
        rows.back().row = sudokuTable[row];
    }

    for (unsigned int col{ 0 }; col < COLUMN_LENGTH; col++) {
        std::vector<char> column(ROW_LENGTH, EMPTY_CELL);
        for (unsigned int row{ 0 }; row < ROW_LENGTH; row++) {
            column[row] = sudokuTable[row][col];
        }
        columns.emplace_back(SudokuColumn());
        columns.back().column = column;
    }

    for (unsigned int blockRow{ 0 }; blockRow < BLOCK_SIDE_LENGTH; ++blockRow) {
        for (unsigned int blockColumn{ 0 }; blockColumn < BLOCK_SIDE_LENGTH; ++blockColumn) {
            SudokuBlock block;
            for (unsigned int i{ 0 }; i < BLOCK_SIDE_LENGTH; ++i) {
                for (unsigned int j{ 0 }; j < BLOCK_SIDE_LENGTH; ++j) {
                    block.block[i][j] = sudokuTable[blockRow * BLOCK_SIDE_LENGTH + i][blockColumn * BLOCK_SIDE_LENGTH + j];
                }
            }
            blocks.emplace_back(block);
        }
    }
}

std::vector<Sudoku::CellID> Sudoku::FindEmptyCells() const {
    std::vector<CellID> result;
    for (unsigned int row{ 0 }; row < ROW_LENGTH; ++row) {
        for (unsigned int column{ 0 }; column < COLUMN_LENGTH; ++column) {
            if (rows[row].row[column] == EMPTY_CELL) {
                unsigned int block { (row / BLOCK_SIDE_LENGTH) * BLOCK_SIDE_LENGTH + (column / BLOCK_SIDE_LENGTH) };
                result.emplace_back(row, column, block);
            }
        }
    }
    return result;
}

bool Sudoku::IsValidValue(const unsigned int& row, const unsigned int& column, const char& value) const {
    for (int c = 0; c < COLUMN_LENGTH; ++c) {
        if (rows[row].row[c] == value)
            return false;
    }

    for (int r = 0; r < ROW_LENGTH; ++r) {
        if (columns[column].column[r] == value)
            return false;
    }

    int blockRowStart = (row / BLOCK_SIDE_LENGTH) * BLOCK_SIDE_LENGTH;
    int blockColumnStart = (column / BLOCK_SIDE_LENGTH) * BLOCK_SIDE_LENGTH;

    for (int r = blockRowStart; r < blockRowStart + BLOCK_SIDE_LENGTH; ++r) {
        for (int c = blockColumnStart; c < blockColumnStart + BLOCK_SIDE_LENGTH; ++c) {
            if (blocks[(r / BLOCK_SIDE_LENGTH) * BLOCK_SIDE_LENGTH + (c / BLOCK_SIDE_LENGTH)].block[r % BLOCK_SIDE_LENGTH][c % BLOCK_SIDE_LENGTH] == value)
                return false;
        }
    }

    return true;
}
