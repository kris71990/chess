#include <vector>

#include "Board.hpp"

namespace Possible_Moves {
  // moves + capture
  std::vector<std::array<int, 2>> pawn_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};
    if (turn % 2 == 0) {
      if (!board.is_on_board(x - 1, y)) return moves;
      std::map<Board::Position, Piece*>::iterator it_black_two;
      std::map<Board::Position, Piece*>::iterator it_black_one;
      std::map<Board::Position, Piece*>::iterator it_black_left;
      std::map<Board::Position, Piece*>::iterator it_black_right;

      it_black_left = board.black_pieces.find(Board::Position(x - 1, y - 1));
      it_black_right = board.black_pieces.find(Board::Position(x - 1, y + 1));
      if (it_black_left != board.black_pieces.end()) moves.push_back({ x - 1, y - 1});
      if (it_black_right != board.black_pieces.end()) moves.push_back({ x - 1, y + 1});
  
      if (x == 6) {
        it_black_two = board.black_pieces.find(Board::Position(x - 2, y));
        it_black_one = board.black_pieces.find(Board::Position(x - 1, y));
        if (it_black_one != board.black_pieces.end()) return moves;

        if (it_black_two != board.black_pieces.end()) {
          moves.push_back({ x - 1, y });
        } else {
          moves.push_back({ x - 2, y });
          moves.push_back({ x - 1, y });
        }
      } else {
        it_black_one = board.black_pieces.find(Board::Position(x - 1, y));
        if (it_black_one == board.black_pieces.end()) moves.push_back({ x - 1, y });
      }
    } else {
      if (!board.is_on_board(x + 1, y)) return moves;
      std::map<Board::Position, Piece*>::iterator it_white_two;
      std::map<Board::Position, Piece*>::iterator it_white_one;
      std::map<Board::Position, Piece*>::iterator it_white_left;
      std::map<Board::Position, Piece*>::iterator it_white_right;

      it_white_left = board.white_pieces.find(Board::Position(x + 1, y - 1));
      it_white_right = board.white_pieces.find(Board::Position(x + 1, y + 1));
      if (it_white_left != board.white_pieces.end()) moves.push_back({ x + 1, y - 1});
      if (it_white_right != board.white_pieces.end()) moves.push_back({ x + 1, y + 1});

      if (x == 1) {
        it_white_two = board.white_pieces.find(Board::Position(x + 2, y));
        it_white_one = board.white_pieces.find(Board::Position(x + 1, y));
        if (it_white_one != board.white_pieces.end()) return moves;

        if (it_white_two != board.white_pieces.end()) {
          moves.push_back({ x + 1, y });
        } else {
          moves.push_back({ x + 1, y });
          moves.push_back({ x + 2, y });
        }
      } else {
        it_white_one = board.white_pieces.find(Board::Position(x + 1, y));
        if (it_white_one == board.white_pieces.end()) moves.push_back({ x + 1, y });
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
        if (!board.is_unoccupied(x + i, y + i)) piece_disruption1 = true;
        if (!piece_disruption1) moves.push_back({ x + i, y + i });
      }
      if (board.is_on_board(x - i, y - i)) {
        if (!board.is_unoccupied(x - i, y - i)) piece_disruption2 = true;
        if (!piece_disruption2) moves.push_back({ x - i, y - i });
      }
      if (board.is_on_board(x - i, y + i)) {
        if (!board.is_unoccupied(x - i, y + i)) piece_disruption3 = true;
        if (!piece_disruption3) moves.push_back({ x - i, y + i });
      }
      if (board.is_on_board(x + i, y - i)) {
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
        if (!board.is_unoccupied( x + i, y)) piece_disruption1 = true;
        if (!piece_disruption1) moves.push_back({ x + i, y });
      }
      if (board.is_on_board(x - i, y)) {
        if (!board.is_unoccupied(x - i, y)) piece_disruption2 = true;
        if (!piece_disruption2) moves.push_back({ x - i, y });
      }
      if (board.is_on_board(x, y + i)) {
        if (!board.is_unoccupied( x, y + i)) piece_disruption3 = true;
        if (!piece_disruption3) moves.push_back({ x, y + i });
      }
      if (board.is_on_board(x, y - i)) {
        if (!board.is_unoccupied(x, y - i)) piece_disruption4 = true;
        if (!piece_disruption4) moves.push_back({ x, y - i });
      }
    }
    return moves;
  }

  std::vector<std::array<int, 2>> queen_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};

    bool piece_disruption1 { false };
    bool piece_disruption2 { false };
    bool piece_disruption3 { false };
    bool piece_disruption4 { false };
    bool piece_disruption5 { false };
    bool piece_disruption6 { false };
    bool piece_disruption7 { false };
    bool piece_disruption8 { false };

    for (int i = 1; i < 8; ++i) {
      if (board.is_on_board(x + i, y) && !piece_disruption1) {
        if (!board.is_unoccupied(x + i, y)) piece_disruption1 = true;
        if (!piece_disruption1) moves.push_back({ x + i, y });
      }
      if (board.is_on_board(x - i, y)) {
        if (!board.is_unoccupied(x - i, y)) piece_disruption2 = true;
        if (!piece_disruption2) moves.push_back({ x - i, y });
      }
      if (board.is_on_board(x, y + i)) {
        if (!board.is_unoccupied(x, y + i)) piece_disruption3 = true;
        if (!piece_disruption3) moves.push_back({ x, y + i });
      }
      if (board.is_on_board(x, y - i)) {
        if (!board.is_unoccupied(x, y - i)) piece_disruption4 = true;
        if (!piece_disruption4) moves.push_back({ x, y - i });
      }
    }

    for (int i = 1; i < 8; ++i) {
      if (board.is_on_board(x + i, y + i) && !piece_disruption1) {
        if (!board.is_unoccupied(x + i, y + i)) piece_disruption5 = true;
        if (!piece_disruption5) moves.push_back({ x + i, y + i });
      }
      if (board.is_on_board(x - i, y - i)) {
        if (!board.is_unoccupied(x - i, y - i)) piece_disruption6 = true;
        if (!piece_disruption6) moves.push_back({ x - i, y - i });
      }
      if (board.is_on_board(x - i, y + i)) {
        if (!board.is_unoccupied(x - i, y + i)) piece_disruption7 = true;
        if (!piece_disruption7) moves.push_back({ x - i, y + i });
      }
      if (board.is_on_board(x + i, y - i)) {
        if (!board.is_unoccupied(x + i, y - i)) piece_disruption8 = true;
        if (!piece_disruption8) moves.push_back({ x + i, y - i });
      }
    }
    return moves;
  }

  std::vector<std::array<int, 2>> knight_moves(Board& board, int turn, int x, int y) 
  {
    std::vector<std::array<int, 2>> moves {};

    if (board.is_on_board(x - 1, y - 2)) moves.push_back({ x - 1, y - 2 });
    if (board.is_on_board(x - 2, y - 1)) moves.push_back({ x - 2, y - 1 });
    if (board.is_on_board(x - 1, y + 2)) moves.push_back({ x - 1, y + 2 });
    if (board.is_on_board(x - 2, y + 1)) moves.push_back({ x - 2, y + 1 });
    if (board.is_on_board(x + 1, y - 2)) moves.push_back({ x + 1, y - 2 });
    if (board.is_on_board(x + 2, y - 1)) moves.push_back({ x + 2, y - 1 });
    if (board.is_on_board(x + 1, y + 2)) moves.push_back({ x + 1, y + 2 });
    if (board.is_on_board(x + 2, y + 1)) moves.push_back({ x + 2, y + 1 });

    return moves;
  }
}