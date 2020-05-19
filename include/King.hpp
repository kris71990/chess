#include <string>

#include "Piece.hpp"

class King : public Piece {
public:
  King() : Piece(){}
  ~King(){}
  
  std::string type = "King";
  std::string board_char = "K";

  std::string get_type() { return type; }
  std::string get_board_char() { return board_char; }
  
  bool validate_move(std::array<std::array<std::string, 8>, 8> board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo);
};
