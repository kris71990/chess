#include <iostream>
#include <map>
#include <string>

#include "../include/Board.hpp"
#include "../include/game_info.hpp"
#include "../include/Moves.hpp"

bool hasEnding (std::string const &fullString, std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
  } 
  return false;
}

void Game_Info::print_game_log(const std::vector<std::string>& game_log) 
{
  std::cout << "\nGame Log:\n";
  for (std::string move : game_log) {
    std::cout << move + "\n"; 
  }
  std::cout << "\n";
}

void Game_Info::print_help_menu() {
  std::cout << "\nChess board is a grid.\nColumns are lettered a-h, rows numbered 1-8\n";
  std::cout << "Enter a square containing a piece (ex. e2)\n";
  std::cout << "Enter a square you want to move the piece to (ex. e4; all chess rules apply)\n";
  std::cout << "Board will reprint after each move\n\n";
  std::cout << "Enable help mode with '-h' to get help with moves";
}

void Game_Info::print_initial_prompt(Game_Info::State game_state) 
{
  std::string input;
  std::cout << "\nShall we play a game?\n";
  std::cout << "y - yes, n - no, h - help\n";
  std::cin >> input;
  if (input == "n") game_state.game_end = true;
  if (input == "h") Game_Info::print_help_menu();
  std::cout << "\nGlobal Thermonuclear War might be thrilling, but chess seems a bit safer.\n";
}

std::map<std::string, std::string> Game_Info::print_move_prompt(const Board& board, Game_Info::State& game_state) {
  std::string spaceFrom;
  std::string spaceTo;
  std::string color;
  std::map<std::string, std::string> move;

  if (game_state.turn % 2 == 0) {
    color = "White";
  } else {
    color = "Black";
  }
  
  std::cout << color << " to move\n";
  std::cout << "Select space to move from: ";
  std::cin >> spaceFrom;

  if (spaceFrom == "q") {
    game_state.game_end = true;
    return move;
  }
  if (spaceFrom == "h") {
    Game_Info::print_help_menu();
    return move;
  }
  if (spaceFrom == "l") {
    Game_Info::print_game_log(game_state.log);
    return move;
  }
  if (hasEnding(spaceFrom, "-h")) game_state.help = true;
  if (hasEnding(spaceFrom, "-hx")) game_state.help = false;

  // if (game_state.help == true) {
  //   std::string piece_type = board[]
  // }

  std::cout << "Select space to move to: ";
  std::cin >> spaceTo;

  if (spaceTo == "q") {
    game_state.game_end = true;
    return move;
  }
  if (spaceFrom == "h") {
    Game_Info::print_help_menu();
    return move;
  }
  if (spaceFrom == "l") {
    Game_Info::print_game_log(game_state.log);
    return move;
  }
  if (spaceFrom.length() != 2 || spaceTo.length() != 2) return move;

  move["color"] = color;
  move["spaceFrom"] = spaceFrom;
  move["spaceTo"] = spaceTo;
  return move;
}
