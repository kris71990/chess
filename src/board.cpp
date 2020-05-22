#include <iostream>
#include <vector>

#include "../include/Board.hpp"

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

void Board::print_possible_moves(const std::vector<std::array<int, 2>>& moves) {
  std::map<int, char>::iterator it;
  std::vector<std::array<int, 2>>::size_type length = moves.size();
  int counter { 0 };
  std::cout << "\nPossible moves: ";

  for (const std::array<int, 2>& move : moves) {
    ++counter;
    it = Board::grid_translator_to_letter.find(move[1]);
    int invertedY = 8 - move[0];
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