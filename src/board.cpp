#include <iostream>
#include <vector>

#include "../include/Board.hpp"
#include "../include/Moves.hpp"

Board::Board()
{
  for (int i = 0; i < 8; ++i) {
    black_pieces[Position(1, i)] = new Pawn();
    white_pieces[Position(6, i)] = new Pawn();
    
    if (i == 0 || i == 7) {
      black_pieces[Position(0, i)] = new Rook();
      white_pieces[Position(7, i)] = new Rook();
    }

    if (i == 1 || i == 6) {
      black_pieces[Position(0, i)] = new Knight();
      white_pieces[Position(7, i)] = new Knight();
    }

    if (i == 2 || i == 5) {
      black_pieces[Position(0, i)] = new Bishop();
      white_pieces[Position(7, i)] = new Bishop();
    }

    if (i == 3) {
      black_pieces[Position(0, i)] = new Queen();
      white_pieces[Position(7, i)] = new Queen();
    }

    if (i == 4) { 
      black_pieces[Position(0, i)] = new King();
      white_pieces[Position(7, i)] = new King(); 
    }
  }

  for (int i = 0; i < 8; ++i) { board[i].fill(" "); }

  std::for_each(white_pieces.begin(), white_pieces.end(), [this](const auto entry) {
    board[entry.first.x][entry.first.y] = "\x1b[1;97m" + entry.second -> get_board_char();
  });

  std::for_each(black_pieces.begin(), black_pieces.end(), [this](const auto entry) {
    board[entry.first.x][entry.first.y] = "\x1b[1;30m" + entry.second -> get_board_char();
  });
}

void Board::draw_board() 
{
  std::cout << "\n  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  | \n";

  for (int x = 0; x < 8; ++x) {
    std::cout << "\n------------------------------------------------\n";
    for (int y = 0; y < 8; ++y) {
      if (board[x][y] == "\x1b[1;97mKn" || board[x][y] == "\x1b[1;30mKn") {
        if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
          std::cout << "\x1b[100m  " << board[x][y] << " \x1b[0m\x1b[0m|";
        } else {
          std::cout << "\x1b[46m  " << board[x][y] << " \x1b[0m\x1b[0m|";
        }
      } else {
        if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
          std::cout << "\x1b[100m  " << board[x][y] << "  \x1b[0m\x1b[0m|";
        } else {
          std::cout << "\x1b[46m  " << board[x][y] << "  \x1b[0m\x1b[0m|";
        }
      }
    }
    std::cout << "  " << std::abs(x - 8);
  }
  std::cout << "\n------------------------------------------------\n\n";

  if (checkmate) {
    char exit;
    std::cout << (turn % 2 ? "White" : "Black") << " won in " << turn << " moves.\n";
    std::cout << "Good game.\n\nHit any key to exit.\n";
    print_game_log();
    std::cin >> exit;
    if (exit) game_end = true;
  }
}

bool hasEnding (std::string const fullString, std::string const ending) {
  if (fullString.length() >= ending.length()) {
    return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
  } 
  return false;
};

std::map<std::string, std::string> Board::print_move_prompt() {
  std::string spaceFrom {};
  std::string color {};
  std::map<std::string, std::string> move {};

  if (turn % 2 == 0) {
    color = "White";
  } else {
    color = "Black";
  }
  
  std::cout << color << " to move\n";
  std::cout << "Select space to move from: ";
  std::getline(std::cin, spaceFrom);

  if (spaceFrom == "q") {
    game_end = true;
    return move;
  }
  if (spaceFrom == "h") {
    print_help_menu();
    return move;
  }
  if (spaceFrom == "l") {
    print_game_log();
    return move;
  }

  if (hasEnding(spaceFrom, "-h")) help = true;
  if (hasEnding(spaceFrom, "-hx")) help = false;

  if (help == true) {
    std::string square_substr { spaceFrom.substr(0,2) };
    int row { 8 - (square_substr[1] - '0') };
    int column { grid_translator_to_index[square_substr[0]] };
    std::string moving_piece { get_piece_from_coordinates(square_substr) };
    
    std::map<int, std::pair<int, int>> moves;
    if (moving_piece == "P") {
      moves = Possible_Moves::pawn_moves(*this, row, column);
    } else if (moving_piece == "Kn") {
      moves = Possible_Moves::knight_moves(*this, row, column);
    } else if (moving_piece == "B") {
      moves = Possible_Moves::bishop_moves(*this, row, column);
    } else if (moving_piece == "R") {
      moves = Possible_Moves::rook_moves(*this, row, column);
    } else if (moving_piece == "Q") {
      moves = Possible_Moves::queen_moves(*this, row, column);
    } else if (moving_piece == "K") {
      moves = Possible_Moves::king_moves(*this, row, column);
    }
    print_possible_moves(moves);
  }

  std::string spaceTo;
  std::cout << "Select space to move to: ";
  std::getline(std::cin, spaceTo);

  if (spaceTo == "q") {
    game_end = true;
    return move;
  }
  if (spaceFrom == "h") {
    print_help_menu();
    return move;
  }
  if (spaceFrom == "l") {
    print_game_log();
    return move;
  }

  if (hasEnding(spaceFrom, "-h") || hasEnding(spaceFrom, "-hx")) {
    std::string square_substr = spaceFrom.substr(0,2);
    move.insert(std::pair<std::string, std::string>("spaceFrom", square_substr));
  } else {
    move.insert(std::pair<std::string, std::string>("spaceFrom", spaceFrom));
  }

  if (hasEnding(spaceTo, "-hx") || hasEnding(spaceTo, "-h")) {
    std::string square_substr = spaceTo.substr(0,2);
    move.insert(std::pair<std::string, std::string>("spaceTo", square_substr));
  } else {
    move.insert(std::pair<std::string, std::string>("spaceTo", spaceTo));
  }

  move.insert(std::pair<std::string, std::string>("color", color));
  return move;
}

bool Board::has_black_piece(int x, int y)
{
  std::map<Position, Piece*>::iterator it = black_pieces.find(Position(x, y));
  if (it != black_pieces.end()) return true;
  return false;
}

bool Board::has_white_piece(int x, int y)
{
  std::map<Position, Piece*>::iterator it = white_pieces.find(Position(x, y));
  if (it != white_pieces.end()) return true;
  return false;
}

std::pair<int, int> Board::find_king(char color)
{
  std::pair<int, int> king_location {};
  if (color == 'b') {
    std::for_each(black_pieces.begin(), black_pieces.end(), [&king_location](const auto entry) {
      if (entry.second -> get_board_char() == "K") king_location = { entry.first.x, entry.first.y };
    });
  } else {
    std::for_each(white_pieces.begin(), white_pieces.end(), [&king_location](const auto entry) {
      if (entry.second -> get_board_char() == "K") king_location = { entry.first.x, entry.first.y };
    });
  }
  return king_location;
}

void Board::print_possible_moves(std::map<int, std::pair<int, int>> moves) 
{
  std::map<int, char>::iterator it;
  std::map<int, std::pair<int, int>>::size_type length = moves.size();
  int counter { 0 };
  std::cout << "\nPossible moves: ";

  for (auto move : moves) {
    ++counter;
    it = grid_translator_to_letter.find(move.second.second);
    int invertedY = 8 - move.second.first;
    std::cout << it -> second << invertedY << (length == counter ? "\n" : ", ");
  }
  std::cout << "\n";
}

std::string Board::get_piece_from_coordinates(std::string square) {
  char letterFrom { square[0] };
  int numberFrom { square[1] - '0' };
  std::string piece { board[8 - numberFrom][grid_translator_to_index[letterFrom]] };
  std::size_t pos { piece.find('m') };
  return piece.substr(pos + 1);
}

std::vector<std::vector<int>> Board::parse_move_input(std::map<std::string, std::string>& move) {
  char letterTo, letterFrom;
  int numberTo, numberFrom;
  int xTo, yTo, xFrom, yFrom;

  for (int i = 0; i < move["spaceFrom"].length(); ++i) {
    if (i == 0) {
      letterFrom = move["spaceFrom"][i];
      letterTo = move["spaceTo"][i];
    } else {
      numberFrom = move["spaceFrom"][i] - '0';
      numberTo = move["spaceTo"][i] - '0';
    }
  }

  xTo = std::abs(numberTo - 8);
  yTo = int(letterTo) - '0' - 49;
  xFrom = std::abs(numberFrom - 8);
  yFrom = int(letterFrom) - '0' - 49;

  std::vector<std::vector<int>> parsed_move = 
    {
      { xFrom, yFrom },
      { xTo, yTo },
    };
  return parsed_move;
}

std::map<int, std::pair<int, int>> Board::next_possible_moves(std::string board_char, int x, int y) {
  // call possible_moves function for piece type (board_char) from x,y
  std::map<int, std::pair<int, int>> moves;
  if (board_char == "P") {
    moves = Possible_Moves::pawn_moves(*this, x, y);
  } else if (board_char == "Kn") {
    moves = Possible_Moves::knight_moves(*this, x, y);
  } else if (board_char == "B") {
    moves = Possible_Moves::bishop_moves(*this, x, y);
  } else if (board_char == "R") {
    moves = Possible_Moves::rook_moves(*this, x, y);
  } else if (board_char == "Q") {
    moves = Possible_Moves::queen_moves(*this, x, y);
  }
  return moves;
}

bool Board::is_check(std::map<int, std::pair<int, int>> next_moves) 
{
  // find where location of king is in opposing piece map
  std::map<int, std::pair<int, int>> moves;
  std::pair<int, int> king_location = find_king(turn % 2 == 0 ? 'b' : 'w');
  int xKing { king_location.first };
  int yKing { king_location.second };

  // if location of king is in possible_moves vector, return location of king and possible moves vector
  for (auto move : next_moves) {
    if (xKing == move.second.first && yKing == move.second.second) {
      return true;
    }
  }
  return false;
}

bool Board::is_checkmate() {
  // opposing king's position
  std::pair<int, int> king_location = find_king(turn % 2 == 0 ? 'b' : 'w');

  // possible moves of opposing king
  std::map<int, std::pair<int, int>> king_moves = Possible_Moves::king_moves(*this, king_location.first, king_location.second);

  if (king_moves.empty()) return true;
  return false;
}