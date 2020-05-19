#include <array>
#include <map>
#include <string>
#include <vector>

#ifndef BOARD_H
#define BOARD_H

#include "King.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Queen.hpp"

class Board {
public:
  std::array<std::array<std::string, 8>, 8> board;

  struct Position {
    int x,y;
    Position(const Position &p, int dx = 0, int dy = 0) { *this = p; x += dx; y += dy;}
    Position(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Position &p) const { return (x < p.x) || (x == p.x && y < p.y); }
    bool operator==(const Position &p) const { return x == p.x && y == p.y; }
  };

  std::map<Position, Piece*> white_pieces;
  std::map<Position, Piece*> black_pieces;
  std::map<int, char> grid_translator = 
    {
      { 0, 'a' },
      { 1, 'b' },
      { 2, 'c' },
      { 3, 'd' },
      { 4, 'e' },
      { 5, 'f' },
      { 6, 'g' },
      { 7, 'h' },
    };

  std::map<char, int> grid_translator_y =
    {
      { 'a', 0 },
      { 'b', 1 },
      { 'c', 2 },
      { 'd', 3 },
      { 'e', 4 },
      { 'f', 5 },
      { 'g', 6 },
      { 'h', 7 },
    };
  
  void init();
  void draw_board();
  void print_possible_moves(const std::vector<std::array<int, 2>>& moves);
  std::vector<std::vector<int>> parse_move_input(std::map<std::string, std::string>& move);

  bool is_on_board(int x, int y) { return ((x < 8 && x >= 0) && (y < 8 && y >= 0)) ? true : false; }
  bool is_unoccupied(int x, int y) { return board[x][y] == " " ? true : false; }
};

#endif