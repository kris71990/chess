#include <vector>
#include <map>

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
  std::map<std::string, int> parse_current_move(std::map<std::string, std::string>& current_move);

  std::map<int, std::pair<int, int>> get_last_piece_possible_moves();
  void set_last_piece_possible_moves(std::map<int, std::pair<int, int>> next_moves);
  void set_last_piece(std::string piece);
  std::string get_last_piece();

private:
  std::map<int, std::pair<int, int>> last_piece_possible_moves;
  std::string last_piece;
  // std::vector<std::vector<std::string, std::map<int, int>>> log_raw;
};

#endif
