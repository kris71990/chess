#include <vector>
#include <map>

#ifndef MOVES_H
#define MOVES_H

#include "Board.hpp"

namespace Possible_Moves {
  std::map<int, std::pair<int, int>> pawn_moves(Board& board, int turn, int x, int y);
  std::map<int, std::pair<int, int>> bishop_moves(Board& board, int turn, int x, int y);
  std::map<int, std::pair<int, int>> rook_moves(Board& board, int turn, int x, int y);
  std::map<int, std::pair<int, int>> queen_moves(Board& board, int turn, int x, int y);
  std::map<int, std::pair<int, int>> knight_moves(Board& board, int turn, int x, int y);
  std::map<int, std::pair<int, int>> king_moves(Board& board, int turn, int x, int y, std::map<int, std::pair<int, int>> opponent_next_move);
}

#endif