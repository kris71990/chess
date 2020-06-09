#include "Piece.hpp"

class Queen : public Piece {
public:
  Queen() : Piece(){}
  ~Queen(){}
  
  std::string get_board_char() const { return board_char; }
  std::string get_type() const { return type; }

  bool validate_move(const std::array<std::array<std::string, 8>, 8>& board, int turn, bool is_occupied, int xFrom, int yFrom, int xTo, int yTo)const;

private:
  const std::string type { "Queen" };
  const std::string board_char { "Q" }; 
};
