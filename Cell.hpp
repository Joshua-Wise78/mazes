#pragma once

#include <string>

class Cell {

public:
  static const int TOP = 1;
  static const int RIGHT = 2;
  static const int BOTTOM = 4;
  static const int LEFT = 8;

  void addConnection(int wall) { boxState = boxState |= wall; }
  void removeConnection(int wall) { boxState = boxState & ~wall; }

  bool hasWall(int wall) { return (boxState & wall) == wall; }

  void setState(int state) { boxState = state; }

  std::string stateSwitch() const {
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

private:
  int boxState = 0;
};
