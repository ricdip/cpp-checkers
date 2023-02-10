#include "../lib/include/Game.hpp"

int main() {
  Board a = Board();
  std::cout << a << std::endl;

  Game g = Game();
  std::vector<Move> moves = g.getPieceMoves(a, C, 6);
  for (auto it = moves.begin(); it != moves.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  Board custom = Board(true);
  std::cout << custom << "\n\n";
  custom(G, 1) = new Pawn(WHITE);
  custom(D, 5) = new Pawn(BLACK);
  std::cout << custom << "\n\n";

  std::cout << "Hello World!" << std::endl;
  return 0;
}
