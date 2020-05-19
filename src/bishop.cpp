#include <array>
#include "../include/Bishop.hpp"

bool Bishop::validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo) {
  if ((xTo > 7 || xTo < 0) || (yTo > 7 || yTo < 0)) return false;
  if ((yFrom == yTo) || (xFrom == xTo)) return false;

  if ((xFrom > xTo) && (yFrom > yTo)) { // up, left
    if (xFrom - xTo != yFrom - yTo) return false;

    int yRunner = yFrom;
    for (int i = xFrom - 1; i >= xTo; --i) {
      --yRunner;
      if (i == xTo && is_occupied) return true;
      if (board[i][yRunner] != " ") return false;
    } 
  } else if ((xFrom < xTo) && (yFrom < yTo)) { // down, right
    if (xTo - xFrom != yTo - yFrom) return false;

    int yRunner = yFrom;
    for (int i = xFrom + 1; i <= xTo; ++i) {
      ++yRunner;
      if (i == xTo && is_occupied) return true;
      if (board[i][yRunner] != " ") return false;
    }
  } else if ((xFrom > xTo) && (yFrom < yTo)) { // up, right
    if (xFrom - xTo != yTo - yFrom) return false;

    int yRunner = yFrom;
    for (int i = xFrom - 1; i >= xTo; --i) {
      ++yRunner;
      if (i == xTo && is_occupied) return true;
      if (board[i][yRunner] != " ") return false;
    }
  } else if ((xFrom < xTo) && (yFrom > yTo)) { // down, left
    if (xTo - xFrom != yFrom - yTo) return false;

    int yRunner = yFrom;
    for (int i = xFrom + 1; i <= xTo; ++i) {
      --yRunner;
      if (i == xTo && is_occupied) return true;
      if (board[i][yRunner] != " ") return false;
    }
  }
  return true;
}
