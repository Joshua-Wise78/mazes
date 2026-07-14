#pragma once

#include "Cell.hpp"
#include "MazeAlgorithms.hpp"
#include "MazeObserver.hpp"
#include <iostream>
#include <vector>

class Maze {
private:
  int rows;
  int columns;
  std::vector<std::vector<Cell>> grid;
  MazeObserver *observer = nullptr;

public:
  Maze(int row, int column) {
    rows = row;
    columns = column;
    grid.resize(row, std::vector<Cell>(column));
  }

  void setObserver(MazeObserver *obs) { observer = obs; }

  void notify(const MazeStep &step) {
    if (observer) {
      observer->onStep(*this, step);
    }
  }

  int getRows() const { return rows; }
  int getColumns() const { return columns; }

  void carvePassage(int r1, int c1, int r2, int c2) {
    if (r1 == r2 + 1) {
      grid[r1][c1].addConnection(Cell::TOP);
      grid[r2][c2].addConnection(Cell::BOTTOM);
    } else if (r1 == r2 - 1) {
      grid[r1][c1].addConnection(Cell::BOTTOM);
      grid[r2][c2].addConnection(Cell::TOP);
    } else if (c1 == c2 + 1) {
      grid[r1][c1].addConnection(Cell::LEFT);
      grid[r2][c2].addConnection(Cell::RIGHT);
    } else if (c1 == c2 - 1) {
      grid[r1][c1].addConnection(Cell::RIGHT);
      grid[r2][c2].addConnection(Cell::LEFT);
    }
    notify({MazeStep::Carve, r1, c1});
    notify({MazeStep::Carve, r2, c2});
  }

  bool isValid(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < columns;
  }

  void setBoxState(int r, int c, int state) {
    if (r >= 0 && r < rows && c >= 0 && c < columns) {
      grid[r][c].setState(state);
    }
  }

  void printMaze() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        std::cout << grid[i][j].stateSwitch();
      }
      std::cout << "\n";
    }
  }

  void generateMaze(MazeAlgorithms &algorithm) { algorithm.generate(*this); }
};
