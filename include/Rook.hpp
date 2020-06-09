#include "Piece.hpp"

class Rook : public Piece {
public:
  Rook() : Piece(){}
  ~Rook(){}

  std::string get_type() const { return type; }
  std::string get_board_char() const { return board_char; }
  
  bool validate_move(const std::array<std::array<std::string, 8>, 8>& board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo)const;

private:
  const std::string type { "Rook" };
  const std::string board_char { "R" }; 
};
