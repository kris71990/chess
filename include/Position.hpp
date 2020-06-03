struct Position {
  int x, y;

  Position(const Position& p, int dx = 0, int dy = 0) { *this = p; x += dx; y += dy; }
  Position(int _x, int _y) : x(_x), y(_y) {}

  bool operator<(const Position& p) const { return (x < p.x) || (x == p.x && y < p.y); }
  bool operator==(const Position& p) const { return x == p.x && y == p.y; }
};
