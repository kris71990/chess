#include <array>
#include "../include/Rook.hpp"

bool Rook::validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo) {
  if ((xTo > 7 || xTo < 0) || (yTo > 7 || yTo < 0)) return false;

  // horizontal
  if (xTo == xFrom) {
    if (yFrom == yTo) return false;
    if (yFrom > yTo) {
      for (int i = yFrom - 1; i >= yTo; --i) {
        if (i == yTo && is_occupied) return true;
        if (board[xTo][i] != " ") return false;
      } 
    } else {
      for (int i = yFrom + 1; i <= yTo; ++i) {
        if (i == yTo && is_occupied) return true;
        if (board[xTo][i] != " ") return false;
      }
    }
    return true;
  // vertical
  } else if (yTo == yFrom) {
    if (xFrom == xTo) return false;
    if (xFrom > xTo) {
      for (int i = xFrom - 1; i >= xTo; --i) {
        if (i == xTo && is_occupied) return true;
        if (board[i][yTo] != " ") return false;
      } 
    } else {
      for (int i = xFrom + 1; i <= xTo; ++i) {
        if (i == xTo && is_occupied) return true;
        if (board[i][yTo] != " ") return false;
      }
    }
    return true;
  }
  return false;
}
