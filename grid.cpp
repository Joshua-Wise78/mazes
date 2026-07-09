#include <algorithm>
#include <iostream>
#include <random>
#include <stack>
#include <string>
#include <vector>

class box {
public:
  static const int TOP = 1;
  static const int RIGHT = 2;
  static const int BOTTOM = 4;
  static const int LEFT = 8;
  int boxState = 0;

  void addConnection(int wall) { boxState = boxState |= wall; }

  void removeConnection(int wall) { boxState = boxState & ~wall; }

  bool hasWall(int wall) { return (boxState & wall) == wall; }

  void setState(int state) { boxState = state; }

  std::string stateSwitch() {
    switch (boxState) {
    case 0:
      return " ";
    case 1:
      return "\u2575"; // Top
    case 2:
      return "\u2576"; // Right
    case 3:
      return "\u2514"; // Top + Right
    case 4:
      return "\u2577"; // Bottom
    case 5:
      return "\u2502"; // Top + Bottom
    case 6:
      return "\u250C"; // Right + Bottom
    case 7:
      return "\u251C"; // Top + Right + Bottom
    case 8:
      return "\u2574"; // Left
    case 9:
      return "\u2518"; // Top + Left
    case 10:
      return "\u2500"; // Right + Left
    case 11:
      return "\u2534"; // Top + Right + Left
    case 12:
      return "\u2510"; // Bottom + Left
    case 13:
      return "\u2524"; // Top + Bottom + Left
    case 14:
      return "\u252C"; // Right + Bottom + Left
    case 15:
      return "\u253C"; // Top + Right + Bottom + Left
    default:
      return "?";
    }
  }
};

class maze {
private:
  int rows;
  int columns;
  std::vector<std::vector<box>> grid;

  struct Cell {
    int r, c;
  };

public:
  maze(int row, int column) {
    rows = row;
    columns = column;
    grid.resize(row, std::vector<box>(column));
  }

  void setBoxState(int r, int c, int state) {
    if (r >= 0 && r < rows && c >= 0 && c < columns) {
      grid[r][c].setState(state);
    }
  }

  void generateMaze() {
    // Track which cells we have visited
    std::vector<std::vector<bool>> visited(rows,
                                           std::vector<bool>(columns, false));
    std::stack<Cell> cellStack;

    // Setup randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    // Start at top-left corner (0,0)
    int currR = 0;
    int currC = 0;
    visited[currR][currC] = true;
    cellStack.push({currR, currC});

    // Loop until backtracked all the way to the start
    while (!cellStack.empty()) {
      currR = cellStack.top().r;
      currC = cellStack.top().c;
      cellStack.pop();

      // Find all unvisited neighbors
      std::vector<int> neighbors; // 0=Top, 1=Right, 2=Bottom, 3=Left

      if (currR > 0 && !visited[currR - 1][currC])
        neighbors.push_back(0); // Top
      if (currC < columns - 1 && !visited[currR][currC + 1])
        neighbors.push_back(1); // Right
      if (currR < rows - 1 && !visited[currR + 1][currC])
        neighbors.push_back(2); // Bottom
      if (currC > 0 && !visited[currR][currC - 1])
        neighbors.push_back(3); // Left

      // If we have unvisited neighbors
      if (!neighbors.empty()) {
        // Push current cell back onto the stack to backtrack to later
        cellStack.push({currR, currC});

        // Pick a random neighbor
        std::uniform_int_distribution<> dist(0, neighbors.size() - 1);
        int choice = neighbors[dist(gen)];

        // Next row and column
        int nextR = currR;
        int nextC = currC;

        // Move top
        if (choice == 0) {
          nextR = currR - 1;
          grid[currR][currC].addConnection(box::TOP);
          grid[nextR][nextC].addConnection(box::BOTTOM);
          // Move right
        } else if (choice == 1) {
          nextC = currC + 1;
          grid[currR][currC].addConnection(box::RIGHT);
          grid[nextR][nextC].addConnection(box::LEFT);
          // Move bottom
        } else if (choice == 2) {
          nextR = currR + 1;
          grid[currR][currC].addConnection(box::BOTTOM);
          grid[nextR][nextC].addConnection(box::TOP);

          // Move left
        } else if (choice == 3) {
          nextC = currC - 1;
          grid[currR][currC].addConnection(box::LEFT);
          grid[nextR][nextC].addConnection(box::RIGHT);
        }

        // Mark neighbor as visited and push to stack
        visited[nextR][nextC] = true;
        cellStack.push({nextR, nextC});
      }
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
};

int main() {

  maze maze(20, 40);

  maze.generateMaze();
  maze.printMaze();

  return 0;
}
