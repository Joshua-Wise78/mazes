#pragma once
#include "Maze.hpp"
#include "MazeAlgorithms.hpp"
#include <random>
#include <stack>
#include <vector>

class DFSAlgorithm : public MazeAlgorithms {
public:
  struct Cord {
    int row;
    int col;
  };

  void generate(Maze &m) override {
    int rows = m.getRows();
    int cols = m.getColumns();
    std::vector<std::vector<bool>> visited(rows,
                                           std::vector<bool>(cols, false));
    std::stack<Cord> cellStack;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> rowDist(0, rows - 1);
    std::uniform_int_distribution<> colDist(0, cols - 1);

    int startRow = rowDist(gen);
    int startCol = colDist(gen);

    visited[startRow][startCol] = true;
    cellStack.push({startRow, startCol});
    m.notify({MazeStep::Visit, startRow, startCol});

    while (!cellStack.empty()) {
      Cord current_cell = cellStack.top();
      cellStack.pop();
      m.notify({MazeStep::Current, current_cell.row, current_cell.col});

      std::vector<Cord> unvistedNeighbors;

      // Checking north (row - 1)
      if (m.isValid(current_cell.row - 1, current_cell.col) &&
          !visited[current_cell.row - 1][current_cell.col]) {
        unvistedNeighbors.push_back({current_cell.row - 1, current_cell.col});
      }

      // Checking south (row + 1)
      if (m.isValid(current_cell.row + 1, current_cell.col) &&
          !visited[current_cell.row + 1][current_cell.col]) {
        unvistedNeighbors.push_back({current_cell.row + 1, current_cell.col});
      }

      // Checking West (col - 1)
      if (m.isValid(current_cell.row, current_cell.col - 1) &&
          !visited[current_cell.row][current_cell.col - 1]) {
        unvistedNeighbors.push_back({current_cell.row, current_cell.col - 1});
      }

      // Checking east (col + 1)
      if (m.isValid(current_cell.row, current_cell.col + 1) &&
          !visited[current_cell.row][current_cell.col + 1]) {
        unvistedNeighbors.push_back({current_cell.row, current_cell.col + 1});
      }

      if (!unvistedNeighbors.empty()) {
        cellStack.push(current_cell);

        std::uniform_int_distribution<> dist(0, unvistedNeighbors.size() - 1);
        Cord nextCell = unvistedNeighbors[dist(gen)];

        m.carvePassage(current_cell.row, current_cell.col, nextCell.row,
                       nextCell.col);

        visited[nextCell.row][nextCell.col] = true;
        m.notify({MazeStep::Visit, nextCell.row, nextCell.col});
        cellStack.push(nextCell);
      } else {
        m.notify({MazeStep::BackTrack, current_cell.row, current_cell.col});
      }
    }
  }
};
