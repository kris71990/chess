#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "../include/game_info.hpp"
// #include "../include/Moves.hpp"
#include "../include/Board.hpp"
#include "../include/Piece.hpp"

std::vector<std::string> is_valid_move(Board& board, int turn, int xFrom, int yFrom, int xTo, int yTo) 
{
  std::vector<std::string> validated_move;
  if (!board.is_on_board(xTo, yTo)) return validated_move;

  std::map<Board::Position, Piece*>::iterator it_from;
  std::vector<std::array<int, 2>> possible_moves;
  bool is_occupied = false;

  if (turn % 2 == 0) {
    std::map<Board::Position, Piece*>::iterator it_to_white;
    // check if white piece on destination
    it_to_white = board.white_pieces.find(Board::Position(xTo, yTo));
    if (it_to_white != board.white_pieces.end()) { return validated_move; }

    std::map<Board::Position, Piece*>::iterator it_to_black;
    it_to_black = board.black_pieces.find(Board::Position(xTo, yTo));
    it_from = board.white_pieces.find(Board::Position(xFrom, yFrom));

    if (it_from != board.white_pieces.end()) {
      std::string piece_type = it_from -> second -> get_type();
      if (it_to_black != board.black_pieces.end()) is_occupied = true;

      if (it_from -> second -> validate_move(board.board, turn, is_occupied, it_from -> first.x, it_from -> first.y, xTo, yTo)) {
        validated_move.push_back(piece_type);
        if (is_occupied) {
          validated_move.push_back(it_to_black -> second -> get_type());
          // piece has been captured, safely destroy pointer
          delete it_to_black -> second; 
          board.black_pieces.erase(it_to_black);
        }
        // possible_moves = Possible_Moves::pawn_moves(board, turn, it_from -> first.x, it_from -> first.y);
        // board.print_possible_moves(possible_moves);
        return validated_move;    
      }
    } else {
      return validated_move;
    }
  } else {
    std::map<Board::Position, Piece*>::iterator it_to_black;
    // check if black piece on destination
    it_to_black = board.black_pieces.find(Board::Position(xTo, yTo));
    if (it_to_black != board.black_pieces.end()) { return validated_move; }

    // check if white piece on destination - capture
    std::map<Board::Position, Piece*>::iterator it_to_white;
    it_to_white = board.white_pieces.find(Board::Position(xTo, yTo));
    it_from = board.black_pieces.find(Board::Position(xFrom, yFrom));

    if (it_from != board.black_pieces.end()) {
      std::string piece_type = it_from -> second -> get_type();
      if (it_to_white != board.white_pieces.end()) is_occupied = true;

      if (it_from -> second -> validate_move(board.board, turn, is_occupied, it_from -> first.x, it_from -> first.y, xTo, yTo)) {
        validated_move.push_back(piece_type);
        if (is_occupied) {
          validated_move.push_back(it_to_white -> second -> get_type());
          // piece has been captured, safely destroy pointer
          delete it_to_white -> second; 
          board.white_pieces.erase(it_to_white);
        }
        // possible_moves = king_moves(board.board, turn, it_from -> first.x, it_from -> first.y);
        // board.print_possible_moves(possible_moves);
        return validated_move;    
      }
    } else {
      return validated_move;
    }
  }
  return validated_move;
}

bool move_piece(Board& board, Game_Info::State& game_state) 
{
  std::map<std::string, std::string> current_move;
  while (current_move.empty()) {
    current_move = Game_Info::print_move_prompt(board, game_state);
    if (game_state.game_end == true) return false;
  }

  std::vector<std::vector<int>> move_coordinates = board.parse_move_input(current_move);
  int xFrom = move_coordinates[0][0];
  int yFrom = move_coordinates[0][1];
  int xTo = move_coordinates[1][0];
  int yTo = move_coordinates[1][1];

  std::vector<std::string> moved_piece = is_valid_move(board, game_state.turn, xFrom, yFrom, xTo, yTo);

  if (!moved_piece.empty()) {
    std::map<Board::Position, Piece*>::iterator it;
    if (game_state.turn % 2 == 0) {
      /* updating pointer map flow */

      // 1. find pointer to piece being moved
      it = board.white_pieces.find(Board::Position(xFrom, yFrom));
      // 2. assign piece pointer to new position
      board.white_pieces[Board::Position(xTo, yTo)] = it -> second;
      board.board[xTo][yTo] = "\x1b[1;97m" + it -> second -> get_board_char();
      // 4. Erase map entry of old position
      board.white_pieces.erase(Board::Position(xFrom, yFrom));
    } else {
      /* updating pointer map flow */

      // 1. find pointer to piece being moved
      it = board.black_pieces.find(Board::Position(xFrom, yFrom));
      // 2. assign piece pointer to new position
      board.black_pieces[Board::Position(xTo, yTo)] = it -> second;
      board.board[xTo][yTo] = "\x1b[1;30m" + it -> second -> get_board_char();
      // 4. Erase map entry of old position
      board.black_pieces.erase(Board::Position(xFrom, yFrom));
    }
    board.board[xFrom][yFrom] = " ";

    std::string capture_string;
    moved_piece.size() == 2 ? capture_string = " -- " + moved_piece[1] + " captured." : "";
    std::string move_str = 
      current_move["color"] + ": " + moved_piece[0] + " from " + 
      board.grid_translator[yFrom] + std::to_string(8 - xFrom) + " to " + 
      board.grid_translator[yTo] + std::to_string(8 - xTo) + 
      (capture_string == "" ? "" : capture_string);
    std::cout << move_str + "\n";
    
    ++game_state.turn;
    game_state.log.push_back(move_str);
  } else {
    std::cout << "\nInvalid Move\n";
  }
  return true;
}

int main() 
{
  Game_Info::State game_state = { false, 0 };
  Game_Info::print_initial_prompt(game_state);
  Board board;
  board.init();

  while (game_state.game_end == false) {
    board.draw_board();
    move_piece(board, game_state);
  }
  return 0;
}