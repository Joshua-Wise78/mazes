#pragma once

class Maze;

class MazeAlgorithms {
public:
  virtual ~MazeAlgorithms() = default;

  virtual void generate(Maze &m) = 0;
};
