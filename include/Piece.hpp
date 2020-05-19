#include <string>

#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
  Piece(){}
  virtual ~Piece(){}

  virtual std::string get_board_char() = 0;
  virtual std::string get_type() = 0;
  
  virtual bool validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo) = 0;
};

#endif