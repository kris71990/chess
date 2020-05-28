#include <vector>
#include <map>

class Game_Info {
public:
  Game_Info() : game_end { false }, help { false }, turn { 0 }, log_visible {}, last_piece {} {};

  bool game_end;
  bool help;
  int turn;
  std::vector<std::string> log_visible;

  void print_game_log();
  void print_help_menu();
  void print_initial_prompt();

  virtual std::map<std::string, std::string> print_move_prompt() = 0;
  std::map<std::string, int> parse_current_move(std::map<std::string, std::string>& current_move);

  std::pair<std::string, std::vector<std::pair<int, int>>> get_previous_piece();
  void set_previous_piece(std::pair<std::string, std::vector<std::pair<int, int>>> previous_piece);

private:
  std::pair<std::string, std::vector<std::pair<int, int>>> last_piece;
  // std::vector<std::vector<std::string, std::map<int, int>>> log_raw;
};
