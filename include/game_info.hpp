#include <vector>
#include <map>

#include "Board.hpp"

namespace Game_Info {
  struct State {
    bool game_end;
    bool help;
    int turn;
    std::vector<std::string> log;
  };

  void print_game_log(const std::vector<std::string>& game_log);
  void print_help_menu();
  void print_initial_prompt(State game_state);

  std::map<std::string, std::string> print_move_prompt(const Board& board, State& game_state);
  std::map<std::string, int> parse_current_move(std::map<std::string, std::string>& current_move);
};
