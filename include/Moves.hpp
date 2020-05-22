#include <vector>

#ifndef MOVES_H
#define MOVES_H

#include "Board.hpp"

namespace Possible_Moves {
  std::vector<std::array<int, 2>> pawn_moves(Board& board, int turn, int x, int y);
  std::vector<std::array<int, 2>> king_moves(Board& board, int turn, int x, int y);
  std::vector<std::array<int, 2>> bishop_moves(Board& board, int turn, int x, int y);
  std::vector<std::array<int, 2>> rook_moves(Board& board, int turn, int x, int y);
  std::vector<std::array<int, 2>> queen_moves(Board& board, int turn, int x, int y);
  std::vector<std::array<int, 2>> knight_moves(Board& board, int turn, int x, int y);
}

#endif