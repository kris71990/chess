#include <vector>
#include <map>

#ifndef MOVES_H
#define MOVES_H

#include "Board.hpp"

namespace Possible_Moves {
  std::map<int, Position> pawn_moves(const Board& board, int x, int y);
  std::map<int, Position> bishop_moves(const Board& board, int x, int y);
  std::map<int, Position> rook_moves(const Board& board, int x, int y);
  std::map<int, Position> queen_moves(const Board& board, int x, int y);
  std::map<int, Position> knight_moves(const Board& board, int x, int y);
  std::map<int, Position> king_moves(const Board& board, int x, int y);
}

#endif