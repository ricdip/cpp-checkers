#include "../lib/game/Game.hpp"

int main() {
  Board board1 = Board();
  std::cout << board1 << std::endl;

  std::vector<Move> movesBoard1 = board1.getMoves();
  for (auto it = movesBoard1.begin(); it != movesBoard1.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  Board board2 = Board(true);
  std::cout << board2 << "\n\n";
  board2(G, 1) = new Queen(WHITE);
  board2(D, 5) = new Pawn(BLACK);
  std::cout << board2 << "\n\n";

  std::vector<Move> movesBoard2 = board2.getMoves();
  for (auto it = movesBoard2.begin(); it != movesBoard2.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  return 0;
}
