#include "../include/Moves.hpp"

std::map<int, std::pair<int, int>> Possible_Moves::pawn_moves(Board& board, int x, int y) 
{
  std::map<int, std::pair<int, int>> moves {};
  if (board.turn % 2 == 0) { // white move
    if (!board.is_on_board(x - 1, y)) return moves;

    // capture moves
    if (board.has_black_piece(x - 1, y - 1)) moves.insert({ 1, { x - 1, y - 1 } });
    if (board.has_black_piece(x - 1, y + 1)) moves.insert({ 2, { x - 1, y + 1 } });

    // if any piece is directly in front
    if (!board.is_unoccupied(x - 1, y)) return moves;

    // if on starting row, can move up two
    if (x == 6) {
      if (board.is_unoccupied(x - 2, y)) {
        moves.insert({ 3, { x - 2, y } });
        moves.insert({ 4, { x - 1, y } });
      } else {
        moves.insert({ 5, { x - 1, y } });
      }
    } else { // else, move up one
      moves.insert({ 6, { x - 1, y } });
    }
  } else { // black move
    if (!board.is_on_board(x + 1, y)) return moves;

    if (board.has_white_piece(x + 1, y - 1)) moves.insert({ 1, { x + 1, y - 1 } });
    if (board.has_white_piece(x + 1, y + 1)) moves.insert({ 2, { x + 1, y + 1 } });

    if (!board.is_unoccupied(x + 1, y)) return moves;

    if (x == 1) {
      if (board.is_unoccupied(x + 2, y)) {
        moves.insert({ 3, { x + 2, y } });
        moves.insert({ 4, { x + 1, y } });
      } else {
        moves.insert({ 5, { x + 1, y } });
      }
    } else {
      moves.insert({ 6, { x + 1, y } });
    }
  }
  return moves;
}

std::map<int, std::pair<int, int>> Possible_Moves::king_moves(Board& board, int x, int y)
{
  std::map<int, std::pair<int, int>> moves {};
  std::map<int, std::pair<int, int>>::iterator it;
  std::map<int, std::pair<int, int>> last_piece_possible_moves = board.get_last_piece_possible_moves();

  if (board.is_on_board(x - 1, y - 1) && (board.is_unoccupied(x - 1, y - 1))) {
    moves.insert({ 0, { x - 1, y - 1} });
  }
  if (board.is_on_board(x - 1, y) && (board.is_unoccupied(x - 1, y))) {
    moves.insert({ 1, { x - 1, y } });
  }
  if (board.is_on_board(x - 1, y + 1) && (board.is_unoccupied(x - 1, y + 1))) {
    moves.insert({ 2, { x - 1, y + 1 } });
  }

  if (board.is_on_board(x + 1, y - 1) && board.is_unoccupied(x + 1, y - 1)) {
    moves.insert({ 3, { x + 1, y - 1 } });
  }
  if (board.is_on_board(x + 1, y) && board.is_unoccupied(x + 1, y)) {
    moves.insert({ 4, { x + 1, y } });
  }
  if (board.is_on_board(x + 1, y + 1) && board.is_unoccupied(x + 1, y + 1)) {
    moves.insert({ 5, { x + 1, y + 1 } });
  }

  if (board.is_on_board(x, y - 1) && board.is_unoccupied(x, y - 1)) {
    moves.insert({ 6, { x, y - 1 } });
  }
  if (board.is_on_board(x, y + 1) && board.is_unoccupied(x, y + 1)) {
    moves.insert({ 7, { x, y + 1 } });
  }

  std::vector<int> disallowed_indices;
  for (auto next_move : last_piece_possible_moves) {
    if (next_move.second.first == x - 1 && next_move.second.second == y - 1) {
      disallowed_indices.push_back(0);
    } else if (next_move.second.first == x - 1 && next_move.second.second == y) {
      disallowed_indices.push_back(1);
    } else if (next_move.second.first == x - 1 && next_move.second.second == y + 1) {
      disallowed_indices.push_back(2);
    } else if (next_move.second.first == x && next_move.second.second == y - 1) {
      disallowed_indices.push_back(6);
    } else if (next_move.second.first == x && next_move.second.second == y + 1) {
      disallowed_indices.push_back(7);
    } else if (next_move.second.first == x + 1 && next_move.second.second == y - 1) {
      disallowed_indices.push_back(3);
    } else if (next_move.second.first == x + 1 && next_move.second.second == y) {
      disallowed_indices.push_back(4);
    } else if (next_move.second.first == x + 1 && next_move.second.second == y + 1) {
      disallowed_indices.push_back(5);
    }
  }

  if (!disallowed_indices.empty()) {
    for (int i : disallowed_indices) {
      moves.erase(i);
    }
  }
  return moves;
}

std::map<int, std::pair<int, int>> Possible_Moves::bishop_moves(Board& board, int x, int y) 
{
  std::map<int, std::pair<int, int>> moves {};
  bool piece_disruption1 { false };
  bool piece_disruption2 { false };
  bool piece_disruption3 { false };
  bool piece_disruption4 { false };
  int counter = 0;

  for (int i = 1; i < 8; ++i) {
    if (board.is_on_board(x + i, y + i) && !piece_disruption1) {
      // check if piece for capture
      if ((board.turn % 2 == 0 && board.has_black_piece(x + i, y + i)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x + i, y + i))) {
        moves.insert({ counter, { x + i, y + i } });
        ++counter;
      }

      // add unoccupied spaces diagonally if unimpeded
      if (!board.is_unoccupied(x + i, y + i)) piece_disruption1 = true;
      if (!piece_disruption1) {
        moves.insert({ counter, { x + i, y + i } });
        ++counter;
      }
    }
    if (board.is_on_board(x - i, y - i) && !piece_disruption2) {
      if ((board.turn % 2 == 0 && board.has_black_piece(x - i, y - i)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x - i, y - i))) {
        moves.insert({ counter, { x - i, y - i } });
        ++counter;
      }

      if (!board.is_unoccupied(x - i, y - i)) piece_disruption2 = true;
      if (!piece_disruption2) {
        moves.insert({ counter, { x - i, y - i } });
        ++counter;
      }
    }
    if (board.is_on_board(x - i, y + i) && !piece_disruption3) {
      if ((board.turn % 2 == 0 && board.has_black_piece(x - i, y + i)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x - i, y + i))) {
        moves.insert({ counter, { x - i, y + i } });
        ++counter;
      }

      if (!board.is_unoccupied(x - i, y + i)) piece_disruption3 = true;
      if (!piece_disruption3) {
        moves.insert({ counter, { x - i, y + i } });
        ++counter;
      }
    }
    if (board.is_on_board(x + i, y - i) && !piece_disruption4) {
      if ((board.turn % 2 == 0 && board.has_black_piece(x + i, y - i)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x + i, y - i))) {
        moves.insert({ counter, { x + i, y - i } });
        ++counter;
       }

      if (!board.is_unoccupied(x + i, y - i)) piece_disruption4 = true;
      if (!piece_disruption4) {
        moves.insert({ counter, { x + i, y - i } });
        ++counter;
      }
    }
  }
  return moves;
}

std::map<int, std::pair<int, int>> Possible_Moves::rook_moves(Board& board, int x, int y) 
{
  std::map<int, std::pair<int, int>> moves {};
  bool piece_disruption1 { false };
  bool piece_disruption2 { false };
  bool piece_disruption3 { false };
  bool piece_disruption4 { false };
  int counter = 0;

  for (int i = 1; i < 8; ++i) {
    if (board.is_on_board(x + i, y) && !piece_disruption1) {
      // check if piece for capture
      if (((board.turn % 2 == 0 && board.has_black_piece(x + i, y)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x + i, y)))) {
        moves.insert({ counter, { x + i, y } });
        ++counter;
      }

      // add spaces vertically and horizontally if unimpeded
      if (!board.is_unoccupied( x + i, y)) piece_disruption1 = true;
      if (!piece_disruption1) {
        moves.insert({ counter, { x + i, y } });
        ++counter;
      }
    }
    if (board.is_on_board(x - i, y) && !piece_disruption2) {
      if (!piece_disruption1 && ((board.turn % 2 == 0 && board.has_black_piece(x - i, y)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x - i, y)))) {
        moves.insert({ counter, { x - i, y } });
        ++counter;
      }

      if (!board.is_unoccupied(x - i, y)) piece_disruption2 = true;
      if (!piece_disruption2) {
        moves.insert({ counter, { x - i, y } });
        ++counter;
      }
    }
    if (board.is_on_board(x, y + i) && !piece_disruption3) {
      if (!piece_disruption1 && ((board.turn % 2 == 0 && board.has_black_piece(x, y + i)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x, y + i)))) {
        moves.insert({ counter, { i, y + i } });
        ++counter;
      }

      if (!board.is_unoccupied( x, y + i)) piece_disruption3 = true;
      if (!piece_disruption3) {
        moves.insert({ counter, { x, y + i } });
        ++counter;
      }
    }
    if (board.is_on_board(x, y - i) && !piece_disruption4) {
      if (!piece_disruption1 && ((board.turn % 2 == 0 && board.has_black_piece(x, y - i)) || 
      (board.turn % 2 == 1 && board.has_white_piece(x, y - i)))) {
        moves.insert({ counter, { x, y - i } });
        ++counter;
      }

      if (!board.is_unoccupied(x, y - i)) piece_disruption4 = true;
      if (!piece_disruption4) {
        moves.insert({ counter, { x, y - i } });
        ++counter;
      }
    }
  }
  return moves;
}

std::map<int, std::pair<int, int>> Possible_Moves::queen_moves(Board& board, int x, int y) 
{
  // same as both rook and bishop
  std::map<int, std::pair<int, int>> rooks = rook_moves(board, x, y);
  std::map<int, std::pair<int, int>> bishops = bishop_moves(board, x, y);
  std::map<int, std::pair<int, int>>::iterator rook_it;
  std::map<int, std::pair<int, int>>::iterator bishop_it;

  std::map<int, std::pair<int, int>> moves {};
  int counter = rooks.size();

  for (rook_it = rooks.begin(); rook_it != rooks.end(); ++rook_it) {
    moves.insert({ rook_it -> first, { rook_it -> second } });
  }

  for (bishop_it = rooks.begin(); bishop_it != bishops.end(); ++bishop_it) {
    ++counter;
    moves.insert({ counter, { bishop_it -> second } });
  }

  return moves;
}

std::map<int, std::pair<int, int>> Possible_Moves::knight_moves(Board& board, int x, int y) 
{
  std::map<int, std::pair<int, int>> moves {};

  if (board.is_on_board(x - 1, y - 2)) {
    if (board.turn == 2 && !board.has_white_piece(x - 1, y - 2)) moves.insert({ 1, { x - 1, y - 2 } });
  }
  if (board.is_on_board(x - 2, y - 1)) {
    if (board.turn == 2 && !board.has_white_piece(x - 2, y - 1)) moves.insert({ 2, { x - 2, y - 1 } });
  }
  if (board.is_on_board(x - 1, y + 2)) {
    if (board.turn == 2 && !board.has_white_piece(x - 1, y + 2)) moves.insert({ 3, { x - 1, y + 2 } });
  }
  if (board.is_on_board(x - 2, y + 1)) {
    if (board.turn == 2 && !board.has_white_piece(x - 2, y + 1)) moves.insert({ 4, { x - 2, y + 1 } });
  }
  if (board.is_on_board(x + 1, y - 2)) {
    if (board.turn == 2 && !board.has_white_piece(x + 1, y - 2)) moves.insert({ 5, { x + 1, y - 2 } });
  }
  if (board.is_on_board(x + 2, y - 1)) {
    if (board.turn == 2 && !board.has_white_piece(x + 2, y - 1)) moves.insert({ 6, { x + 2, y - 1 } });
  }
  if (board.is_on_board(x + 1, y + 2)) {
    if (board.turn == 2 && !board.has_white_piece(x + 1, y + 2)) moves.insert({ 7, { x + 1, y + 2 } });
  }
  if (board.is_on_board(x + 2, y + 1)) {
    if (board.turn == 2 && !board.has_white_piece(x + 2, y + 1)) moves.insert({ 8, { x + 2, y + 1 } });
  }
  return moves;
}