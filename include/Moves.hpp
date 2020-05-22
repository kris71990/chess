#include <vector>

#include "Board.hpp"

namespace Possible_Moves {
  // moves + capture
  std::vector<std::array<int, 2>> pawn_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};
    if (turn % 2 == 0) { // white move
      if (!board.is_on_board(x - 1, y)) return moves;

      // capture moves
      if (board.has_black_piece(x - 1, y - 1)) moves.push_back({ x - 1, y - 1});
      if (board.has_black_piece(x - 1, y + 1)) moves.push_back({ x - 1, y + 1});

      // if any piece is directly in front
      if (!board.is_unoccupied(x - 1, y)) return moves;
  
      // if on starting row, can move up two
      if (x == 6) {
        if (board.is_unoccupied(x - 2, y)) {
          moves.push_back({ x - 2, y });
          moves.push_back({ x - 1, y });
        } else {
          moves.push_back({ x - 1, y });
        }
      } else { // else, move up one
        moves.push_back({ x - 1, y });
      }
    } else { // black move
      if (!board.is_on_board(x + 1, y)) return moves;

      if (board.has_white_piece(x + 1, y - 1)) moves.push_back({ x + 1, y - 1});
      if (board.has_white_piece(x + 1, y + 1)) moves.push_back({ x + 1, y + 1});

      if (!board.is_unoccupied(x + 1, y)) return moves;

      if (x == 1) {
       if (board.is_unoccupied(x + 2, y)) {
          moves.push_back({ x + 2, y });
          moves.push_back({ x + 1, y });
        } else {
          moves.push_back({ x + 1, y });
        }
      } else {
        moves.push_back({ x + 1, y });
      }
    }
    return moves;
  }

  std::vector<std::array<int, 2>> king_moves(Board& board, int turn, int x, int y)
  {
    std::vector<std::array<int, 2>> moves {};
    int count { 0 }; 
    int count1 { 0 };
    int count2 { -1 };

    for (int i = 0; i < 8; ++i) {
      switch (i % 3) {
        case 0: { 
          if (board.is_on_board(x - 1, y - 1 + count) && board.is_unoccupied(x - 1, y - 1 + count)) {
            moves.push_back({ x - 1, y - 1 + count });
          }
          ++count;
          break;
        }
        case 1: {
          if (board.is_on_board(x + 1, y - 1 + count1) && board.is_unoccupied(x + 1, y - 1 + count1)) {
            moves.push_back({ x + 1, y - 1 + count1 });
          }
          ++count1;
          break;
        }
        default: {
          if (board.is_on_board(x, y + count2) && board.is_unoccupied(x, y + count2)) {
            moves.push_back({ x, y + count2 });
          }
          count2 = 1;
          break;
        }
      }
    }
    return moves;
  }

  std::vector<std::array<int, 2>> bishop_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};
    bool piece_disruption1 { false };
    bool piece_disruption2 { false };
    bool piece_disruption3 { false };
    bool piece_disruption4 { false };

    for (int i = 1; i < 8; ++i) {
      if (board.is_on_board(x + i, y + i) && !piece_disruption1) {
        // check if piece for capture
        if ((turn % 2 == 0 && board.has_black_piece(x + i, y + i)) || 
          (turn % 2 == 1 && board.has_white_piece(x + i, y + i))) moves.push_back({ x + i, y + i });

        // add unoccupied spaces diagonally if unimpeded
        if (!board.is_unoccupied(x + i, y + i)) piece_disruption1 = true;
        if (!piece_disruption1) moves.push_back({ x + i, y + i });
      }
      if (board.is_on_board(x - i, y - i) && !piece_disruption2) {
        if ((turn % 2 == 0 && board.has_black_piece(x - i, y - i)) || 
          (turn % 2 == 1 && board.has_white_piece(x - i, y - i))) moves.push_back({ x - i, y - i });

        if (!board.is_unoccupied(x - i, y - i)) piece_disruption2 = true;
        if (!piece_disruption2) moves.push_back({ x - i, y - i });
      }
      if (board.is_on_board(x - i, y + i) && !piece_disruption3) {
        if ((turn % 2 == 0 && board.has_black_piece(x - i, y + i)) || 
          (turn % 2 == 1 && board.has_white_piece(x - i, y + i))) moves.push_back({ x - i, y + i });

        if (!board.is_unoccupied(x - i, y + i)) piece_disruption3 = true;
        if (!piece_disruption3) moves.push_back({ x - i, y + i });
      }
      if (board.is_on_board(x + i, y - i) && !piece_disruption4) {
        if ((turn % 2 == 0 && board.has_black_piece(x + i, y - i)) || 
          (turn % 2 == 1 && board.has_white_piece(x + i, y - i))) moves.push_back({ x + i, y - i });

        if (!board.is_unoccupied(x + i, y - i)) piece_disruption4 = true;
        if (!piece_disruption4) moves.push_back({ x + i, y - i });
      }
    }
    return moves;
  }

  std::vector<std::array<int, 2>> rook_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};
    bool piece_disruption1 { false };
    bool piece_disruption2 { false };
    bool piece_disruption3 { false };
    bool piece_disruption4 { false };

    for (int i = 1; i < 8; ++i) {
      if (board.is_on_board(x + i, y) && !piece_disruption1) {
        // check if piece for capture
        if (((turn % 2 == 0 && board.has_black_piece(x + i, y)) || 
          (turn % 2 == 1 && board.has_white_piece(x + i, y)))) moves.push_back({ x + i, y });

        // add spaces vertically and horizontally if unimpeded
        if (!board.is_unoccupied( x + i, y)) piece_disruption1 = true;
        if (!piece_disruption1) moves.push_back({ x + i, y });
      }
      if (board.is_on_board(x - i, y) && !piece_disruption2) {
        if (!piece_disruption1 && ((turn % 2 == 0 && board.has_black_piece(x - i, y)) || 
          (turn % 2 == 1 && board.has_white_piece(x - i, y)))) moves.push_back({ x - i, y });

        if (!board.is_unoccupied(x - i, y)) piece_disruption2 = true;
        if (!piece_disruption2) moves.push_back({ x - i, y });
      }
      if (board.is_on_board(x, y + i) && !piece_disruption3) {
        if (!piece_disruption1 && ((turn % 2 == 0 && board.has_black_piece(x, y + i)) || 
          (turn % 2 == 1 && board.has_white_piece(x, y + i)))) moves.push_back({ i, y + i });

        if (!board.is_unoccupied( x, y + i)) piece_disruption3 = true;
        if (!piece_disruption3) moves.push_back({ x, y + i });
      }
      if (board.is_on_board(x, y - i) && !piece_disruption4) {
        if (!piece_disruption1 && ((turn % 2 == 0 && board.has_black_piece(x, y - i)) || 
          (turn % 2 == 1 && board.has_white_piece(x, y - i)))) moves.push_back({ x, y - i });

        if (!board.is_unoccupied(x, y - i)) piece_disruption4 = true;
        if (!piece_disruption4) moves.push_back({ x, y - i });
      }
    }
    return moves;
  }

  std::vector<std::array<int, 2>> queen_moves(Board& board, int turn, int x, int y) 
  {
    // same as both rook and bishop
    std::vector<std::array<int, 2>> rooks = rook_moves(board, turn, x, y);
    std::vector<std::array<int, 2>> bishops = bishop_moves(board, turn, x, y);

    std::vector<std::array<int, 2>> moves {};
    moves.reserve(rooks.size() + bishops.size());
    moves.insert(moves.end(), rooks.begin(), rooks.end());
    moves.insert(moves.end(), bishops.begin(), bishops.end());
    return moves;
  }

  std::vector<std::array<int, 2>> knight_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};

    if (board.is_on_board(x - 1, y - 2)) {
      if (turn == 2 && !board.has_white_piece(x - 1, y - 2)) moves.push_back({ x - 1, y - 2 });
    }
    if (board.is_on_board(x - 2, y - 1)) {
      if (turn == 2 && !board.has_white_piece(x - 2, y - 1)) moves.push_back({ x - 2, y - 1 });
    }
    if (board.is_on_board(x - 1, y + 2)) {
      if (turn == 2 && !board.has_white_piece(x - 1, y + 2)) moves.push_back({ x - 1, y + 2 });
    }
    if (board.is_on_board(x - 2, y + 1)) {
      if (turn == 2 && !board.has_white_piece(x - 2, y + 1)) moves.push_back({ x - 2, y + 1 });
    }
    if (board.is_on_board(x + 1, y - 2)) {
      if (turn == 2 && !board.has_white_piece(x + 1, y - 2)) moves.push_back({ x + 1, y - 2 });
    }
    if (board.is_on_board(x + 2, y - 1)) {
      if (turn == 2 && !board.has_white_piece(x + 2, y - 1)) moves.push_back({ x + 2, y - 1 });
    }
    if (board.is_on_board(x + 1, y + 2)) {
      if (turn == 2 && !board.has_white_piece(x + 1, y + 2)) moves.push_back({ x + 1, y + 2 });
    }
    if (board.is_on_board(x + 2, y + 1)) {
      if (turn == 2 && !board.has_white_piece(x + 2, y + 1)) moves.push_back({ x + 2, y + 1 });
    }
    return moves;
  }
}