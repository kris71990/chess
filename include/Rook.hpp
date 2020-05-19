#include "Piece.hpp"

class Rook : public Piece {
public:
  Rook() : Piece(){}
  ~Rook(){}
  
  std::string type = "Rook";
  std::string board_char = "R";

  std::string get_type() { return type; }
  std::string get_board_char() { return board_char; }
  
  bool validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo);
};
