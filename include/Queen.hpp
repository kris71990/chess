#include "Piece.hpp"

class Queen : public Piece {
public:
  Queen() : Piece(){}
  ~Queen(){}
  
  std::string type = "Queen";
  std::string board_char = "Q";
  
  std::string get_board_char() { return board_char; }
  std::string get_type() { return type; }

  bool validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo);
};
