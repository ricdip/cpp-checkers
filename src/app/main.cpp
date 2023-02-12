#include "../lib/game/Game.hpp"

int main() {
  Board board1 = Board(true);

  std::cout << board1 << '\n';
  std::cout << "turn: " << board1.getTurn() << '\n';

  board1(D, 4) = new Pawn(WHITE);
  board1(E, 5) = new Pawn(BLACK);

  std::cout << board1 << '\n';
  std::cout << "turn: " << board1.getTurn() << '\n';

  std::vector<Move> moves = board1.getMoves();

  for (auto it = moves.begin(); it != moves.end(); it++) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';

  board1.makeMove(Move("D4F6"));

  std::cout << board1 << '\n';
  std::cout << "turn: " << board1.getTurn() << '\n';

  return 0;
}
