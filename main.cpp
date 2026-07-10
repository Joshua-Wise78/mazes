#include "DFSAlgorithm.hpp"
#include "Maze.hpp"

int main() {
  Maze m(20, 40);

  DFSAlgorithm dfsGen;

  m.generateMaze(dfsGen);
  m.printMaze();
}
