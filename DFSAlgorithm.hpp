#pragma once
#include "Maze.hpp"
#include "MazeAlgorithms.hpp"
#include <vector>

class DFSAlgorithm : public MazeAlgorithms {
public:
  void generate(Maze &m) override {
    int rows = m.getRows();
    int cols = m.getColumns();
    std::vector<std::vector<bool>> visited(rows,
                                           std::vector<bool>(cols, false));
  }
};
