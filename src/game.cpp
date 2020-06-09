#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "../include/Board.hpp"
#include "../include/Grid_Translator.hpp"
#include "../include/Piece.hpp"
#include "../include/Moves.hpp"

std::vector<std::string> is_valid_move(Board& board, int xFrom, int yFrom, int xTo, int yTo) 
{
  std::vector<std::string> validated_move {};
  if (!Board::is_on_board(xTo, yTo)) return validated_move;

  std::map<Position, Piece*>::iterator it_from;
  bool is_occupied { false };

  if (board.turn % 2 == 0) {
    std::map<Position, Piece*>::iterator it_to_white;
    // check if white piece on destination
    it_to_white = board.white_pieces.find(Position(xTo, yTo));
    if (it_to_white != board.white_pieces.end()) { return validated_move; }

    std::map<Position, Piece*>::iterator it_to_black;
    it_to_black = board.black_pieces.find(Position(xTo, yTo));
    it_from = board.white_pieces.find(Position(xFrom, yFrom));

    if (it_from != board.white_pieces.end()) {
      std::string piece_type { it_from -> second -> get_type() };
      if (it_to_black != board.black_pieces.end()) is_occupied = true;

      if (piece_type == "King") {
        std::map<int, Position> possible_moves = Possible_Moves::king_moves(board, xFrom, yFrom);
        std::map<int, Position>::iterator it_king;
        for (it_king = possible_moves.begin(); it_king != possible_moves.end(); ++it_king) {
          if (it_king -> second.x == xTo && it_king -> second.y == yTo) {
            validated_move.push_back(piece_type);
            if (is_occupied) {
              validated_move.push_back(it_to_black -> second -> get_type());
              // piece has been captured, safely destroy pointer
              delete it_to_black -> second; 
              board.black_pieces.erase(it_to_black);
            }
            return validated_move;  
          }
        }
      } else {
        if (it_from -> second -> validate_move(board.board, board.turn, is_occupied, it_from -> first.x, it_from -> first.y, xTo, yTo)) {
          validated_move.push_back(piece_type);
          if (is_occupied) {
            validated_move.push_back(it_to_black -> second -> get_type());
            // piece has been captured, safely destroy pointer
            delete it_to_black -> second; 
            board.black_pieces.erase(it_to_black);
          }
          return validated_move;    
        }
      }
    } else {
      return validated_move;
    }
  } else {
    std::map<Position, Piece*>::iterator it_to_black;
    // check if black piece on destination
    it_to_black = board.black_pieces.find(Position(xTo, yTo));
    if (it_to_black != board.black_pieces.end()) { return validated_move; }

    // check if white piece on destination - capture
    std::map<Position, Piece*>::iterator it_to_white;
    it_to_white = board.white_pieces.find(Position(xTo, yTo));
    it_from = board.black_pieces.find(Position(xFrom, yFrom));

    if (it_from != board.black_pieces.end()) {
      std::string piece_type = it_from -> second -> get_type();
      if (it_to_white != board.white_pieces.end()) is_occupied = true;

      if (piece_type == "King") {
        std::map<int, Position> possible_moves = Possible_Moves::king_moves(board, xFrom, yFrom);
        std::map<int, Position>::iterator it_king;
        for (it_king = possible_moves.begin(); it_king != possible_moves.end(); ++it_king) {
          if (it_king -> second.x == xTo && it_king -> second.y == yTo) {
            validated_move.push_back(piece_type);
            if (is_occupied) {
              validated_move.push_back(it_to_white -> second -> get_type());
              // piece has been captured, safely destroy pointer
              delete it_to_white -> second; 
              board.white_pieces.erase(it_to_white);
            }
            return validated_move;  
          }
        }
      } else {
        if (it_from -> second -> validate_move(board.board, board.turn, is_occupied, it_from -> first.x, it_from -> first.y, xTo, yTo)) {
          validated_move.push_back(piece_type);
          if (is_occupied) {
            validated_move.push_back(it_to_white -> second -> get_type());
            // piece has been captured, safely destroy pointer
            delete it_to_white -> second; 
            board.white_pieces.erase(it_to_white);
          }
          return validated_move;    
        }
      }
    } else {
      return validated_move;
    }
  }
  return validated_move;
}

bool move_piece(Board& board) 
{
  if (board.game_end == true) return false;
  std::map<std::string, std::string> current_move {};
  while (current_move.empty()) {
    current_move = board.print_move_prompt();
    if (board.game_end == true) return false;
  }

  std::vector<std::vector<int>> move_coordinates = board.parse_move_input(current_move);
  int xFrom { move_coordinates[0][0] };
  int yFrom { move_coordinates[0][1] };
  int xTo { move_coordinates[1][0] };
  int yTo { move_coordinates[1][1] };

  std::vector<std::string> moved_piece = is_valid_move(board, xFrom, yFrom, xTo, yTo);

  if (!moved_piece.empty()) {
    std::map<Position, Piece*>::iterator it;
    std::string board_char {};

    if (board.turn % 2 == 0) {
      /* updating pointer map flow */

      // 1. find pointer to piece being moved
      it = board.white_pieces.find(Position(xFrom, yFrom));
      board_char = it -> second -> get_board_char();
      // 2. assign piece pointer to new position
      board.white_pieces[Position(xTo, yTo)] = it -> second;
      board.board[xTo][yTo] = "\x1b[1;97m" + board_char;
      // 4. Erase map entry of old position
      board.white_pieces.erase(Position(xFrom, yFrom));
    } else {
      /* updating pointer map flow */

      // 1. find pointer to piece being moved
      it = board.black_pieces.find(Position(xFrom, yFrom));
      board_char = it -> second -> get_board_char();
      // 2. assign piece pointer to new position
      board.black_pieces[Position(xTo, yTo)] = it -> second;
      board.board[xTo][yTo] = "\x1b[1;30m" + board_char;
      // 4. Erase map entry of old position
      board.black_pieces.erase(Position(xFrom, yFrom));
    }

    // call board.is_check(board_char, turn, xTo, yTo)
    // if (check) call board.is_checkmate()
    std::map<int, Position> next_moves = board.next_possible_moves(board_char, xTo, yTo);
    board.set_last_piece(board_char);
    board.set_last_piece_possible_moves(next_moves);
    std::string check_status {};

    if (board.is_check(next_moves)) {
      if (board.is_checkmate()) {
        check_status = " -- Checkmate";
        board.checkmate = true;
      } else {
        check_status = " -- Check";
      }
    }

    board.board[xFrom][yFrom] = " ";

    std::string capture_string {};
    moved_piece.size() == 2 ? capture_string = " -- " + moved_piece[1] + " captured." : "";
    std::string move_str = 
      current_move["color"] + ": " + moved_piece[0] + " from " + 
      Grid_Translator::to_letter.at(yFrom) + std::to_string(8 - xFrom) + " to " + 
      Grid_Translator::to_letter.at(yTo) + std::to_string(8 - xTo) + 
      (capture_string == "" ? "" : capture_string) +
      (check_status == "" ? "" : check_status);
    std::cout << move_str + "\n";
    
    ++board.turn;
    board.log_visible.push_back(move_str);
  } else {
    std::cout << "\nInvalid Move\n";
  }
  return true;
}

int main() 
{
  Board board;
  board.print_initial_prompt();

  while (board.game_end == false) {
    board.draw_board();
    move_piece(board);
  }
  return 0;
}