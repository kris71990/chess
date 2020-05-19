#include <array>

#include "../include/Pawn.hpp"

bool Pawn::validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo) 
{
  if (turn % 2 == 0) {
    if (is_occupied) {
      if ((xFrom - 1 == xTo) && ((yFrom - 1 == yTo) || (yFrom + 1 == yTo))) return true;
      return false;
    } else {
      if (xFrom == 6) {
        if (((xFrom - 2 == xTo && yFrom == yTo) || (xFrom - 1 == xTo && yFrom == yTo))) return true;
      } else {
        if ((xFrom - 1 == xTo) && (yFrom = yTo)) return true;
      }
    }
  } else {
    if (is_occupied) {
      if ((xFrom + 1 == xTo) && ((yFrom - 1 == yTo) || (yFrom + 1 == yTo))) return true;
      return false;
    } else {
      if (xFrom == 1) {
        if (((xFrom + 2 == xTo && yFrom == yTo) || (xFrom + 1 == xTo && yFrom == yTo))) return true;
      } else {
        if ((xFrom + 1 == xTo) && (yFrom == yTo)) return true;
      }
    }
  }
  return false;
}