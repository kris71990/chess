#include <vector>
#include <map>

#include "Position.hpp"

#ifndef GAME_INFO_H
#define GAME_INFO_H

class Game_Info {
public:
  Game_Info() : game_end { false }, help { false }, turn { 0 }, log_visible {}, last_piece {}, last_piece_possible_moves {} {};

  bool game_end;
  bool help;
  bool checkmate;
  int turn;
  std::vector<std::string> log_visible;

  void print_game_log();
  void print_help_menu();
  void print_initial_prompt();

  virtual std::map<std::string, std::string> print_move_prompt() = 0;

  std::map<int, Position> get_last_piece_possible_moves() const;
  void set_last_piece_possible_moves(const std::map<int, Position>& next_moves);
  void set_last_piece(const std::string& piece);
  std::string get_last_piece();

private:
  std::map<int, Position> last_piece_possible_moves;
  std::string last_piece;
};

#endif
