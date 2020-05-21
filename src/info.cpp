#include <iostream>
#include <map>
#include <string>
#include <limits>

#include "../include/Board.hpp"
#include "../include/Game_Info.hpp"
#include "../include/Moves.hpp"

bool hasEnding (std::string const fullString, std::string const ending) {
  if (fullString.length() >= ending.length()) {
    return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
  } 
  return false;
};

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
  std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
  if (input == "n") game_state.game_end = true;
  if (input == "h") Game_Info::print_help_menu();
  std::cout << "\nGlobal Thermonuclear War might be thrilling, but chess seems a bit safer.\n";
}

std::map<std::string, std::string> Game_Info::print_move_prompt(Board& board, Game_Info::State& game_state) {
  std::string spaceFrom;
  std::string color;
  std::map<std::string, std::string> move;

  if (game_state.turn % 2 == 0) {
    color = "White";
  } else {
    color = "Black";
  }
  
  std::cout << color << " to move\n";
  std::cout << "Select space to move from: ";
  std::getline(std::cin, spaceFrom);

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

  if (game_state.help == true) {
    std::string square_substr = spaceFrom.substr(0,2);
    int row = 8 - (square_substr[1] - '0');
    int column = board.grid_translator_to_index[square_substr[0]];
    std::string moving_piece = board.get_piece_from_coordinates(square_substr);
    
    std::vector<std::array<int, 2>> moves;
    if (moving_piece == "P") {
      moves = Possible_Moves::pawn_moves(board, game_state.turn, row, column);
    } else if (moving_piece == "Kn") {
      moves = Possible_Moves::knight_moves(board, game_state.turn, row, column);
    } else if (moving_piece == "B") {
      moves = Possible_Moves::bishop_moves(board, game_state.turn, row, column);
    } else if (moving_piece == "R") {
      moves = Possible_Moves::rook_moves(board, game_state.turn, row, column);
    } else if (moving_piece == "Q") {
      moves = Possible_Moves::queen_moves(board, game_state.turn, row, column);
    } else if (moving_piece == "K") {
      moves = Possible_Moves::king_moves(board, game_state.turn, row, column);
    }
    board.print_possible_moves(moves);
  }

  std::string spaceTo;
  std::cout << "Select space to move to: ";
  std::getline(std::cin, spaceTo);

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

  if (hasEnding(spaceFrom, "-h") || hasEnding(spaceFrom, "-hx")) {
    std::string square_substr = spaceFrom.substr(0,2);
    move["spaceFrom"] = square_substr;
  } else {
    move["spaceFrom"] = spaceFrom;
  }

  if (hasEnding(spaceTo, "-hx") || hasEnding(spaceTo, "-h")) {
    std::string square_substr = spaceTo.substr(0,2);
    move["spaceTo"] = square_substr;
  } else {
    move["spaceTo"] = spaceTo;
  }

  move["color"] = color;
  return move;
}
