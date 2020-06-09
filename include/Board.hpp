#include <array>
#include <map>
#include <string>
#include <vector>

#ifndef BOARD_H
#define BOARD_H

#include "Game_Info.hpp"
#include "Position.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Queen.hpp"

class Board : public Game_Info, public Position {
public:
  Board();
  std::array<std::array<std::string, 8>, 8> board {};
  std::map<Position, Piece*> white_pieces {};
  std::map<Position, Piece*> black_pieces {};
  
  void draw_board();
  void print_possible_moves(const std::map<int, Position>& moves);

  std::string get_piece_from_coordinates(std::string coordinates);
  std::map<std::string, std::string> print_move_prompt() override;
  std::vector<std::vector<int>> parse_move_input(const std::map<std::string, std::string>& move);

  static bool is_on_board(int x, int y) { return ((x < 8 && x >= 0) && (y < 8 && y >= 0)) ? true : false; }
  bool is_unoccupied(int x, int y) const { return board[x][y] == " " ? true : false; }
  bool has_white_piece(int x, int y) const;
  bool has_black_piece(int x, int y) const;
  std::pair<int, int> find_king(char color);

  std::map<int, Position> next_possible_moves(std::string board_char, int x, int y);
  bool is_check(const std::map<int, Position>& next_moves);
  bool is_checkmate();
};

#endif