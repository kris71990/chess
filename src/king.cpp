#include <array>
#include <string>

#include "../include/King.hpp"

bool King::validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo) 
{
  if ((xFrom - 1 == xTo && yFrom - 1 == yTo) ||
      (xFrom - 1 == xTo && yFrom == yTo) ||
      (xFrom - 1 == xTo && yFrom + 1 == yTo) ||
      (xFrom == xTo && yFrom - 1 == yTo) ||
      (xFrom == xTo && yFrom + 1 == yTo) ||
      (xFrom + 1 == xTo && yFrom - 1 == yTo) ||
      (xFrom + 1 == xTo && yFrom == yTo) ||
      (xFrom + 1 == xTo && yFrom + 1 == yTo)) {
        return true;
  }
  return false;
}
