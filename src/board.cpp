#include <iostream>
#include <vector>

#include "../include/Board.hpp"

void Board::init()
{
  for (int i = 0; i < 8; ++i) {
    // black_pieces[Position(1, i)] = new Pawn();
    // white_pieces[Position(6, i)] = new Pawn();
    
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

  std::map<Position, Piece*>::iterator it;
  for (it = white_pieces.begin(); it != white_pieces.end(); ++it) {
    board[it -> first.x][it -> first.y] = "\x1b[1;97m" + it -> second -> get_board_char(); //"\x1b[1;97m"
  }

  for (it = black_pieces.begin(); it != black_pieces.end(); ++it) {
    board[it -> first.x][it -> first.y] = "\x1b[1;30m" + it -> second -> get_board_char(); //"\x1b[1;30m" + 
  }
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

void Board::print_possible_moves(const std::vector<std::array<int, 2>>& moves) {
  std::map<int, char>::iterator it;
  for (const std::array<int, 2>& move : moves) {
    it = Board::grid_translator.find(move[1]);
    int invertedY = 8 - move[0];
    std::cout << it -> second << invertedY << "\n";
  }
}

std::vector<std::vector<int>> Board::parse_move_input(std::map<std::string, std::string>& move) {
  char letterTo, letterFrom;
  int numberTo, numberFrom;
  int xTo, yTo;
  int xFrom, yFrom;

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