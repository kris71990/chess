#include <iostream>
#include <map>
#include <string>
#include <limits>

#include "../include/Game_Info.hpp"
#include "../include/Moves.hpp"

std::map<int, Position> Game_Info::get_last_piece_possible_moves() const { 
  return last_piece_possible_moves; 
}

void Game_Info::set_last_piece_possible_moves(const std::map<int, Position>& previous_piece) {
  last_piece_possible_moves = previous_piece;
}

void Game_Info::set_last_piece(const std::string& piece) { last_piece = piece; }
std::string Game_Info::get_last_piece() { return last_piece; }

void Game_Info::print_game_log() 
{
  std::cout << "\nGame Log:\n";
  for (std::string move : log_visible) {
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

void Game_Info::print_initial_prompt() 
{
  std::string input;
  std::cout << "\nShall we play a game?\n";
  std::cout << "y - yes, n - no, h - help\n";
  std::cin >> input;
  std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
  if (input == "n") game_end = true;
  if (input == "h") print_help_menu();
  std::cout << "\nGlobal Thermonuclear War might be thrilling, but chess seems a bit safer.\n";
}
