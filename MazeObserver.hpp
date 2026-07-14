#pragma once

class Maze;

struct MazeStep {
  enum Kind {
    Visit,
    Carve,
    BackTrack,
    Current,
  } kind;
  int r;
  int c;
};

class MazeObserver {
public:
  virtual ~MazeObserver() = default;

  virtual void onStep(const Maze &m, const MazeStep &step) = 0;
};
